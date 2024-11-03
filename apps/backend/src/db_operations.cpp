#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
#include <hiddenframe_headers.h>
#include <stdexcept>
#include <string>

using namespace std;

sqlite3* createDB(){
    sqlite3 *db;
    char *errMsg=0;
    int rc;
    rc=sqlite3_open_v2("database/userdatabase.db",&db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if(rc) {
      throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(db)));
    } 

    const char* sql="CREATE TABLE IF NOT EXISTS Users(" \
    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
    "USERNAME TEXT NOT NULL,"\
    "TOKENID TEXT,"\
    "INVITESREMAINING INTEGER DEFAULT 5,"\
    "PASSWORD TEXT NOT NULL);";

    const char* sql2="CREATE TABLE IF NOT EXISTS Invites(" \
    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
    "INVITEID INTEGER,"\
    "USERNAME TEXT NOT NULL,"\
    "FOREIGN KEY (INVITEID) REFERENCES Users(ID) ON DELETE CASCADE);";

    rc=sqlite3_exec(db,sql, 0,0, &errMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(db)));
        sqlite3_free(errMsg);
    } 

    rc=sqlite3_exec(db,sql2, 0,0, &errMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(db)));
        sqlite3_free(errMsg);
    } 

    return db;
}



void createNewAdmin(sqlite3 *database, const string& username,const string& password){
  //check if DB is opened correctly
  if (!database){
    throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(database)));
  }
  //create a new sql statement
  sqlite3_stmt *insstmt;

  //setup the SQL statement
  const char *sql="INSERT INTO Users (username, password) VALUES(?,?);";
  //prepare statement
  int rc=sqlite3_prepare_v2(database, sql, -1, &insstmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  //bind arguments to SQL statement
  sqlite3_bind_text(insstmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(insstmt, 2, password.c_str(), -1, SQLITE_STATIC);
  //Query the DB
  rc=sqlite3_step(insstmt);
  if(rc != SQLITE_DONE) {
        throw std::runtime_error("Query execution failed - "+string(sqlite3_errmsg(database)));
  }
  //finalize the statement
  sqlite3_finalize(insstmt);
  return;
}





void createNewUser(sqlite3 *database, const string& username,const string& password, const int inviteID){
  //check if DB is opened correctly
  if (!database){
    throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(database)));
  }
  sqlite3_exec(database, "BEGIN TRANSACTION;", NULL,NULL,NULL);
  int invitesRemaining;
  //create a new sql statement
  sqlite3_stmt *stmt;

  //Prepare statement 1
  const char *sql1="SELECT invitesremaining FROM Users WHERE id = ?;";
  int rc=sqlite3_prepare_v2(database, sql1, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  //bind the argument to the statement
  sqlite3_bind_int(stmt, 1, inviteID);
  //run the query
  if (sqlite3_step(stmt) == SQLITE_ROW) {
        invitesRemaining = sqlite3_column_int(stmt, 0);
  } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("No such user with that ID or failed to check invites: " + std::string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);

  if (invitesRemaining <=0){
    throw std::runtime_error("The inviting user does not have enough invites remaining.");
  }


  //prepare statement 2
  const char *sql2="INSERT INTO Users (username, password) VALUES(?,?);";
  rc=sqlite3_prepare_v2(database, sql2, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  //bind arguments to SQL statement
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  //Query the DB
  rc=sqlite3_step(stmt);
  if(rc != SQLITE_DONE) {
        throw std::runtime_error("Query execution failed - "+string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);

  //prepare statement 3
  const char *sql3="INSERT INTO invites (inviteID, username) VALUES(?,?)";
  rc=sqlite3_prepare_v2(database,sql3, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, inviteID);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute insert invite statement: " + std::string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);

  //prepare statement 4
  const char *sql4="UPDATE Users SET invitesremaining = invitesremaining-1 WHERE ID = ?;";
  rc=sqlite3_prepare_v2(database,sql4, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  sqlite3_bind_int(stmt, 1, inviteID);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute insert invite statement: " + std::string(sqlite3_errmsg(database)));
  }
  sqlite3_finalize(stmt);
  sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
  return;
}




bool authenticateUser(sqlite3 *database,const string& username,const string& password){
  //check if DB is opened correctly
  if (!database){
    throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(database)));
  }
  //make a new sql statement
  sqlite3_stmt *authstmt;
  //setup sql statement
  const char *sql="SELECT password FROM Users WHERE username = ?;";
  //prepare sql statement
  int rc=sqlite3_prepare_v2(database, sql, -1, &authstmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  //bind arguments to SQL statment
  sqlite3_bind_text(authstmt, 1, username.c_str(), -1, SQLITE_STATIC);

  //Query the DB
  rc=sqlite3_step(authstmt);
  if (rc== SQLITE_ROW){
    const unsigned char* dbPassword=sqlite3_column_text(authstmt,0);
    //passwords match
    if (password==reinterpret_cast<const char*>(dbPassword)){
      sqlite3_finalize(authstmt);
      return true;
    }
  }
  return false;
}



