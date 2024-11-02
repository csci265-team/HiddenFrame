#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
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
    //DELETE FOR PRODUCTION
    else {
      fprintf(stderr, "Opened database successfully\n");
    }

    const char* sql="CREATE TABLE IF NOT EXISTS Users(" \
    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
    "USERNAME TEXT NOT NULL,"\
    "TOKENID TEXT,"\
    "PASSWORD TEXT NOT NULL);";

    rc=sqlite3_exec(db,sql, 0,0, &errMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(db)));
        sqlite3_free(errMsg);
    } 
    //DELETE FOR PRODUCTION
    else {
        printf("Table created successfully\n");
    }
    return db;
}

void createNewUser(sqlite3 *database, const string& username,const string& password){
  //check if DB is opened correctly
  if (!database){
    throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(database)));
  }
  //create a new sql statement
  sqlite3_stmt *stmt;

  //setup the SQL statement
  const char *sql="INSERT INTO Users (username, password) VALUES(?,?);";
  //prepare statement
  int rc=sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
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
  //finalize the statement
  sqlite3_finalize(stmt);
  return;
}

bool authenticateUser(sqlite3 *database,const string& username,const string& password){
  //check if DB is opened correctly
  if (!database){
    throw std::runtime_error("Database not opened correctly - "+string(sqlite3_errmsg(database)));
  }
  //make a new sql statement
  sqlite3_stmt *stmt;
  //setup sql statement
  const char *sql="SELECT password FROM Users WHERE username = ?;";
  //prepare sql statement
  int rc=sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
      throw std::runtime_error("Failed to Prepare Statement - "+string(sqlite3_errmsg(database)));
  }
  //bind arguments to SQL statment
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

  //Query the DB
  rc=sqlite3_step(stmt);
  if (rc== SQLITE_ROW){
    const unsigned char* dbPassword=sqlite3_column_text(stmt,0);
    //passwords match
    if (password==reinterpret_cast<const char*>(dbPassword)){
      sqlite3_finalize(stmt);
      return true;
    }
  }
  return false;
}

