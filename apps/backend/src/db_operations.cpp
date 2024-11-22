bool usernameExists(sqlite3 *database, const string &username)
{
  std::cout << "usernameExists: Starting function" << std::endl;

  std::lock_guard<std::mutex> lock(db_mutex);

  sqlite3_stmt *checkStmt;
  const char *checkSql = "SELECT COUNT(*) FROM Users WHERE username = ?;";
  std::cout << "usernameExists: Preparing statement" << std::endl;

  int rc = sqlite3_prepare_v2(database, checkSql, -1, &checkStmt, NULL);
  if (rc != SQLITE_OK)
  {
    std::cout << "usernameExists: Failed to prepare statement" << std::endl;
    sqlite3_finalize(checkStmt);
    throw std::runtime_error("Failed to Prepare Statement for checking duplicate username - " + string(sqlite3_errmsg(database)));
  }
  std::cout << "usernameExists: Prepared statement" << std::endl;

  sqlite3_bind_text(checkStmt, 1, username.c_str(), -1, SQLITE_STATIC);
  std::cout << "usernameExists: Bound username" << std::endl;

  rc = sqlite3_step(checkStmt);
  if (rc == SQLITE_ROW)
  {
    int count = sqlite3_column_int(checkStmt, 0);
    std::cout << "usernameExists: Retrieved count: " << count << std::endl;
    sqlite3_finalize(checkStmt);
    std::cout << "usernameExists: Finalized statement" << std::endl;
    return count > 0;
  }
  else
  {
    std::cout << "usernameExists: Error checking for duplicate username" << std::endl;
    sqlite3_finalize(checkStmt);
    throw std::runtime_error("Error checking for duplicate username - " + string(sqlite3_errmsg(database)));
  }
}