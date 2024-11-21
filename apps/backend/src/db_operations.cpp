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
#include <utils.h>

using namespace std;
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
  if (!isValidEmailFormat(username)){
    throw std::runtime_error("The provided username is not valid");
  }
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  if (usernameExists(database,username)){
      throw std::runtime_error("User Already Exists "); 
  }
  // create a new sql statement
  sqlite3_stmt *insstmt;

  // setup the SQL statement
  const char *sql = "INSERT INTO Users (username, password) VALUES(?,?);";
  // prepare statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &insstmt, NULL);
  if (rc != SQLITE_OK)
  {
    sqlite3_finalize(insstmt);
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statement
  sqlite3_bind_text(insstmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(insstmt, 2, password.c_str(), -1, SQLITE_STATIC);
  // Query the DB
  rc = sqlite3_step(insstmt);
  if (rc != SQLITE_DONE)
  {
    sqlite3_finalize(insstmt);
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  // finalize the statement
  sqlite3_finalize(insstmt);
  return;
}

void createNewUser(sqlite3 *database, const string &username, const string &password, const int inviteID)
{
  if (!isValidEmailFormat(username)){
    throw std::runtime_error("The provided username is not valid");
  }
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }
  if (usernameExists(database,username)){
      throw std::runtime_error("User Already Exists"); 
  }
  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
  // create a new sql statement
  sqlite3_stmt *stmt;
  // check if inviteid is valid
  const char *sql0 = "SELECT is_valid FROM Invites WHERE id = ?;";
  int rc = sqlite3_prepare_v2(database, sql0, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    sqlite3_finalize(stmt);
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
    sqlite3_finalize(stmt);
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

  // get the new user's ID
  int newUserID = sqlite3_last_insert_rowid(database);

  // update the invite to set is_valid to false and used_by to the new user ID
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
    rc = sqlite3_step(stmt);
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
    sqlite3_finalize(stmt);
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    int invitesCreated = sqlite3_column_int(stmt, 1);
    cout << "Invites created: " << invitesCreated << endl;
    sqlite3_finalize(stmt);
    // check if user has invites remaining, they can make max 5
    if (invitesCreated < 5)
    {
      // create new invite and set is valid to true
      const char *sql = "INSERT INTO Invites (is_valid, created_by, used_by) VALUES(1, ?, NULL);";
      rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_finalize(stmt);
      // increment invites_created
      const char *sql2 = "UPDATE Users SET invites_created = invites_created + 1 WHERE id = ?;";
      rc = sqlite3_prepare_v2(database, sql2, -1, &stmt, NULL);
      if (rc != SQLITE_OK)
      {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
      }
      sqlite3_bind_int(stmt, 1, userID);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE)
      {
        sqlite3_finalize(stmt);
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
      return -1; // No invites remaining
    }
  }
  else
  {
    throw std::runtime_error("User not found.");
  }
}

vector<crow::json::wvalue> listInvites(sqlite3 *database, const int &userId)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  // create a new sql statement
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

  sqlite3_finalize(stmt);

  return invites;
}

bool changePassword(sqlite3 *database, const string &username, const string &newPassword)
{
  // check if DB is opened correctly
  if (!database)
  {
    throw std::runtime_error("Database not opened correctly - " + string(sqlite3_errmsg(database)));
  }

  // create a new sql statement
  sqlite3_stmt *stmt;
  const char *sql = "UPDATE Users SET password = ?, token_id = NULL WHERE username = ?;";

  // prepare sql statement
  int rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
  {
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }

  // bind arguments to SQL statement
  sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

  // execute the SQL statement
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }

  // finalize the statement
  sqlite3_finalize(stmt);
  return true;
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
    sqlite3_finalize(authstmt);
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
  sqlite3_finalize(authstmt);
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
    sqlite3_finalize(stmt);
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statement
  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);

  // Query the DB
  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    int userID = sqlite3_column_int(stmt, 0);
    const unsigned char *username = sqlite3_column_text(stmt, 1);
    std::string usernameStr(reinterpret_cast<const char *>(username));
    sqlite3_finalize(stmt);
    return make_pair(userID, usernameStr);
  }
  sqlite3_finalize(stmt);
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
    sqlite3_finalize(stmt);
    throw std::runtime_error("Failed to Prepare Statement - " + string(sqlite3_errmsg(database)));
  }
  // bind arguments to SQL statment
  sqlite3_bind_text(stmt, 1, tokenId.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

  // Query the DB
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Query execution failed - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);
  return;
}

// Function to safely close the database
void closeDB(sqlite3* db) {
    if (db) {
        sqlite3_db_cacheflush(db);
        sqlite3_close(db);
    }
}

/*
* @brief - checks if a username already exists in the DB
*
*/
bool usernameExists(sqlite3* database, const string& username){
  sqlite3_stmt *checkStmt;
  const char *checkSql = "SELECT COUNT(*) FROM Users WHERE username = ?;";
    
  // Prepare the SQL statement
  int rc = sqlite3_prepare_v2(database, checkSql, -1, &checkStmt, NULL);
  if (rc != SQLITE_OK)
  {
    sqlite3_finalize(checkStmt); // Finalize the statement if preparation fails
    throw std::runtime_error("Failed to Prepare Statement for checking duplicate username - " + string(sqlite3_errmsg(database)));
  }

  // Bind the username to the statement
  sqlite3_bind_text(checkStmt, 1, username.c_str(), -1, SQLITE_STATIC);

  // Execute the query
  rc = sqlite3_step(checkStmt);
  if (rc == SQLITE_ROW){
    int count = sqlite3_column_int(checkStmt, 0);
    if (count > 0){
      sqlite3_finalize(checkStmt); // Finalize the statement after use
      return true;
    }
  }else{
    sqlite3_finalize(checkStmt); // Finalize the statement if the query fails
    throw std::runtime_error("Error checking for duplicate username - " + string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(checkStmt);
  return false;
}
