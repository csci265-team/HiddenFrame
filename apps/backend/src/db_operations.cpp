#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
#include <hiddenframe_headers.h>
#include <stdexcept>
#include <string>

using namespace std;

sqlite3 *createDB()
{
  sqlite3 *db;
  char *errMsg = 0;
  int rc;
  rc = sqlite3_open_v2("database/userdatabase.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (rc)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
  }

  const char *sql = "CREATE TABLE IF NOT EXISTS Users("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "username TEXT NOT NULL,"
                    "token_id TEXT,"
                    "invites_created INTEGER DEFAULT 5,"
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
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
    sqlite3_free(errMsg);
  }

  rc = sqlite3_exec(db, sql2, 0, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(db)));
    sqlite3_free(errMsg);
  }

  return db;
}

void createNewAdmin(sqlite3 *database, const string &username, const string &password)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  // create a new sql statement
  sqlite3_stmt *insstmt;

  // setup the SQL statement
  const char *sql = "INSERT INTO Users (username, password) VALUES(?,?);";
  // prepare statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &insstmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statement
  sqlite3_bind_text(insstmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(insstmt, 2, password.c_str(), -1, SQLITE_STATIC);
  // Query the DB
  rc = sqlite3_step(insstmt);
  if (rc != SQLITE_DONE)
  {
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  // finalize the statement
  sqlite3_finalize(insstmt);
  return;
}

void createNewUser(sqlite3 *database, const string &username, const string &password, const int inviteID)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
  // create a new sql statement
  sqlite3_stmt *stmt;

  // check if inviteid is valid
  const char *sql0 = "SELECT is_valid FROM Invites WHERE id = ?;";
  int rc = sqlite3_prepare_v2(database, sql0, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, inviteID);
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    if (sqlite3_column_int(stmt, 0) == 0)
    {
      sqlite3_finalize(stmt);
      throw std::runtime_error("Invite ID is not valid.");
    }
  }
  else
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("No such invite ID exists.");
  }
  sqlite3_finalize(stmt);

  // if invite is valid create new user
  const char *sql = "INSERT INTO Users (username, password) VALUES(?, ?);";
  rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);
  sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
  return;
}

int createInvite(sqlite3 *database, const string &username)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
  // create a new sql statement
  sqlite3_stmt *stmt;
  // check if user exists and get invites_created and id
  const char *sql0 = "SELECT id, invites_created FROM Users WHERE username = ?;";
  int rc = sqlite3_prepare_v2(database, sql0, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    int invitesCreated = sqlite3_column_int(stmt, 1);
    sqlite3_finalize(stmt);
    // check if user has invites remaining, they can make max 5
    if (invitesCreated < 5)
    {
      // create new invite and set is valid to true
      const char *sql = "INSERT INTO Invites (is_valid, created_by, used_by) VALUES(1, ?, NULL);";
      rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_finalize(stmt);
      // increment invites_created
      const char *sql2 = "UPDATE Users SET invites_created = invites_created + 1 WHERE id = ?;";
      rc = sqlite3_prepare_v2(database, sql2, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_finalize(stmt);
      sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
      // return created invite id
      return sqlite3_last_insert_rowid(database);
    }
    else
    {
      sqlite3_finalize(stmt);
      return -1;
    }
  }
  return -1;
}

bool authenticateUser(sqlite3 *database, const string &username, const string &password)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  // make a new sql statement
  sqlite3_stmt *authstmt;
  // setup sql statement
  const char *sql = "SELECT password FROM Users WHERE username = ?;";
  // prepare sql statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &authstmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statment
  sqlite3_bind_text(authstmt, 1, username.c_str(), -1, SQLITE_STATIC);

  // Query the DB
  rc = sqlite3_step(authstmt);
  if (rc == SQLITE_ROW)
  {
    const unsigned char *dbPassword = sqlite3_column_text(authstmt, 0);
    // passwords match
    if (password == reinterpret_cast<const char *>(dbPassword))
    {
      sqlite3_finalize(authstmt);
      return true;
    }
  }
  return false;
}

// verify token fucntion that returns user id and username if token is valid
pair<int, string> verifyTokenWithDb(sqlite3 *database, const string &tokenId)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  // make a new sql statement
  sqlite3_stmt *stmt;
  // setup sql statement
  const char *sql = "SELECT id, username FROM Users WHERE token_id = ?;";
  // prepare sql statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statment
  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);

  // Query the DB
  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    const unsigned char *username = sqlite3_column_text(stmt, 1);
    sqlite3_finalize(stmt);
    return make_pair(userID, reinterpret_cast<const char *>(username));
  }

  throw std::runtime_error("Token not found.");
}

void saveToken(sqlite3 *database, const string &username, const string &tokenId)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  // make a new sql statement
  sqlite3_stmt *stmt;
  // setup sql statement
  const char *sql = "UPDATE Users SET token_id = ? WHERE username = ?;";
  // prepare sql statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statment
  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

  // Query the DB
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);
  return;
}
