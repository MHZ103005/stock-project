#include <sqlite3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#ifndef SQLFUNC_H
#define SQLFUNC_H

// Function Prototypes
bool tickerExists(const std::string &ticker); // Checks if Ticker is a real stock
// insert functions
void insertUser(sqlite3 *db, const std::string &username, double balance = 10000.0); // inserts into users table
void insertAsset(sqlite3 *db, int userId, const std::string &ticker, double quantity);
void insertTrade(sqlite3 *db, int userId, const std::string &ticker, const std::string &action, double quantity, double price);
// query functions
bool checkUsername(sqlite3 *db, const std::string &username); // reads username from database

int callback(void *data, int argc, char **argv, char **azColName); // used for reading from database
void retrieveAsset(sqlite3 *db, const std::string &ticker);        // retrieves asset from database
void initializeDatabase(sqlite3 *db);                              // initializes the database and creates the assets table if it doesn't exist

#endif