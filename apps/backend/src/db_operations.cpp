#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
#include <hiddenframe_headers.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <crow/json.h>
#include <mutex>

using namespace std;

std::mutex db_mutex;

sqlite3 *createDB(string filepath)
{
  sqlite3 *db;
  char *errMsg = 0;
  int rc;
  rc = sqlite3_open_v2(filepath.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (rc)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
  }

  const char *sql = "CREATE TABLE IF NOT EXISTS Users("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "username TEXT NOT NULL,"
                    "token_id TEXT,"
                    "invites_created INTEGER DEFAULT 0,"
                    "password TEXT NOT NULL);";

  const char *sql2 = "CREATE TABLE IF NOT EXISTS Invites("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                     "is_valid BOOLEAN,"
                     "created_by INTEGER,"
                     "used_by INTEGER,"
                     "FOREIGN KEY (created_by) REFERENCES Users(id) ON DELETE CASCADE,"
                     "FOREIGN KEY (used_by) REFERENCES Users(id) ON DELETE CASCADE);";

  rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    sqlite3_free(errMsg);
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
  }
  sqlite3_free(errMsg);
  rc = sqlite3_exec(db, sql2, 0, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    sqlite3_free(errMsg);
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
  }
  sqlite3_free(errMsg);
  return db;
}

void createNewAdmin(sqlite3 *database, const string &username, const string &password)
{
  if (username.empty() || password.empty())
  {
    throw std::runtime_error("Password and/or username cannot be empty");
  }

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  // Temporarily release the lock before calling usernameExists

  db_mutex.unlock();
  if (usernameExists(database, username))
  {
    throw std::runtime_error("User Already Exists");
  }

  std::lock_guard<std::mutex> lock(db_mutex);

  sqlite3_stmt *insstmt;
  const char *sql = "INSERT INTO Users (username, password) VALUES(?,?);";
  int rc = sqlite3_prepare_v2(database, sql, -1, &insstmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (insstmt != NULL)
    {
      sqlite3_finalize(insstmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(insstmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(insstmt, 2, password.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(insstmt);
  if (rc != SQLITE_DONE)
  {
    if (insstmt != NULL)
    {
      sqlite3_finalize(insstmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  // finalize the statement
  if (insstmt != NULL)
  {
    sqlite3_finalize(insstmt); // Finalize the statement if preparation fails
  }
  return;
}

void createNewUser(sqlite3 *database, const string &username, const string &password, const int inviteID)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (username.empty() || password.empty())
  {
    throw std::runtime_error("Password and/or username cannot be empty");
  }
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  if (usernameExists(database, username))
  {
    throw std::runtime_error("User Already Exists");
  }

  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
  sqlite3_stmt *stmt;

  const char *sql0 = "SELECT is_valid FROM Invites WHERE id = ?;";
  int rc = sqlite3_prepare_v2(database, sql0, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, inviteID);
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    if (sqlite3_column_int(stmt, 0) == 0)
    {
      if (stmt != NULL)
      {
        sqlite3_finalize(stmt); // Finalize the statement if preparation fails
      }
      throw std::runtime_error("Invite ID is not valid.");
    }
  }
  else
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("No such invite ID exists.");
  }
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }

  const char *sql = "INSERT INTO Users (username, password) VALUES(?, ?);";
  rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }

  int newUserID = sqlite3_last_insert_rowid(database);

  const char *sql2 = "UPDATE Invites SET is_valid = 0, used_by = ? WHERE id = ?;";
  rc = sqlite3_prepare_v2(database, sql2, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, newUserID);
  sqlite3_bind_int(stmt, 2, inviteID);
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }
  sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
}

int createInvite(sqlite3 *database, const string &username)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
  sqlite3_stmt *stmt;

  const char *sql0 = "SELECT id, invites_created FROM Users WHERE username = ?;";
  int rc = sqlite3_prepare_v2(database, sql0, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    int invitesCreated = sqlite3_column_int(stmt, 1);
    cout << "Invites created: " << invitesCreated << endl;
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    // check if user has invites remaining, they can make max 5
    if (invitesCreated < 5)
    {
      const char *sql = "INSERT INTO Invites (is_valid, created_by, used_by) VALUES(1, ?, NULL);";
      rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        if (stmt != NULL)
        {
          sqlite3_finalize(stmt); // Finalize the statement if preparation fails
        }
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        if (stmt != NULL)
        {
          sqlite3_finalize(stmt); // Finalize the statement if preparation fails
        }
        throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
      }
      if (stmt != NULL)
      {
        sqlite3_finalize(stmt); // Finalize the statement if preparation fails
      }
      // increment invites_created
      const char *sql2 = "UPDATE Users SET invites_created = invites_created + 1 WHERE id = ?;";
      rc = sqlite3_prepare_v2(database, sql2, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        if (stmt != NULL)
        {
          sqlite3_finalize(stmt); // Finalize the statement if preparation fails
        }
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        if (stmt != NULL)
        {
          sqlite3_finalize(stmt); // Finalize the statement if preparation fails
        }
        throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
      }
      if (stmt != NULL)
      {
        sqlite3_finalize(stmt); // Finalize the statement if preparation fails
      }
      sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
      return sqlite3_last_insert_rowid(database);
    }
    else
    {
      if (stmt != NULL)
      {
        sqlite3_finalize(stmt); // Finalize the statement if preparation fails
      }
      return -1; // No invites remaining
    }
  }
  else
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("User not found.");
  }
}

vector<crow::json::wvalue> listInvites(sqlite3 *database, const int &userId)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_stmt *stmt;
  const char *sql = "SELECT id, is_valid, created_by, used_by FROM Invites WHERE created_by = ?;";
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, userId);

  vector<crow::json::wvalue> invites;

  while (sqlite3_step(stmt) == SQLITE_ROW)
  {
    crow::json::wvalue invite;
    invite["id"] = sqlite3_column_int(stmt, 0);
    invite["is_valid"] = sqlite3_column_int(stmt, 1);
    invite["created_by"] = sqlite3_column_int(stmt, 2);
    invite["used_by"] = sqlite3_column_int(stmt, 3);

    invites.push_back(invite);
  }

  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }

  return invites;
}

bool changePassword(sqlite3 *database, const string &username, const string &newPassword)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_stmt *stmt;
  const char *sql = "UPDATE Users SET password = ?, token_id = NULL WHERE username = ?;";

  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }

  // finalize the statement
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }
  return true;
}

bool authenticateUser(sqlite3 *database, const string &username, const string &password)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_stmt *authstmt;
  const char *sql = "SELECT password FROM Users WHERE username = ?;";
  int rc = sqlite3_prepare_v2(database, sql, -1, &authstmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (authstmt != NULL)
    {
      sqlite3_finalize(authstmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(authstmt, 1, username.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(authstmt);
  if (rc == SQLITE_ROW)
  {
    const unsigned char *dbPassword = sqlite3_column_text(authstmt, 0);
    if (password == reinterpret_cast<const char *>(dbPassword))
    {
      if (authstmt != NULL)
      {
        sqlite3_finalize(authstmt); // Finalize the statement if preparation fails
      }
      return true;
    }
  }
  if (authstmt != NULL)
  {
    sqlite3_finalize(authstmt); // Finalize the statement if preparation fails
  }
  return false;
}

pair<int, string> verifyTokenWithDb(sqlite3 *database, const string &tokenId)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_stmt *stmt;
  const char *sql = "SELECT id, username FROM Users WHERE token_id = ?;";
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    const unsigned char *username = sqlite3_column_text(stmt, 1);
    std::string usernameStr(reinterpret_cast<const char *>(username));
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    return make_pair(userID, usernameStr);
  }
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }
  throw std::runtime_error("Token not found.");
}

void saveToken(sqlite3 *database, const string &username, const string &tokenId)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_stmt *stmt;
  const char *sql = "UPDATE Users SET token_id = ? WHERE username = ?;";
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    if (stmt != NULL)
    {
      sqlite3_finalize(stmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  if (stmt != NULL)
  {
    sqlite3_finalize(stmt); // Finalize the statement if preparation fails
  }
  return;
}

void closeDB(sqlite3 *db)
{
  if (db)
  {
    sqlite3_db_cacheflush(db);
    sqlite3_close(db);
  }
}

bool usernameExists(sqlite3 *database, const string &username)
{
  std::lock_guard<std::mutex> lock(db_mutex);

  sqlite3_stmt *checkStmt;
  const char *checkSql = "SELECT COUNT(*) FROM Users WHERE username = ?;";

  int rc = sqlite3_prepare_v2(database, checkSql, -1, &checkStmt, NULL);
  if (rc != SQLITE_OK)
  {
    if (checkStmt != NULL)
    {
      sqlite3_finalize(checkStmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Failed to Prepare Statement for checking duplicate username - " + string(sqlite3_errmsg(database)));
  }

  sqlite3_bind_text(checkStmt, 1, username.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(checkStmt);
  if (rc == SQLITE_ROW)
  {
    int count = sqlite3_column_int(checkStmt, 0);
    if (count > 0)
    {
      sqlite3_finalize(checkStmt); // Finalize the statement after use
      return true;
    }
  }
  else
  {
    if (checkStmt != NULL)
    {
      sqlite3_finalize(checkStmt); // Finalize the statement if preparation fails
    }
    throw std::runtime_error("Error checking for duplicate username - " + string(sqlite3_errmsg(database)));
  }
}