#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "stock.h"
#include "portfolio.h"
#include "sqlite3.h"
#include "sqlfunc.h"

int main()
{
    // Initialize SQLite database
    sqlite3 *db;
    int exit = sqlite3_open("portfolio.db", &db); // create database file

    if (exit)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }
    else
    {
        std::cout << "Database opened successfully!" << std::endl;
    }
    // create table inside database
    initializeDatabase(db);

    // example of selecting
    char *errMsg = 0;
    const char *selectSql = "SELECT * FROM assets;";
    if (sqlite3_exec(db, selectSql, callback, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Data selected successfully!" << std::endl;
    }

    insertUser(db, "testuser", 10000.0); // insert a test user into the database
    std::cout << "D" << std::endl;
    if (checkUsername(db, "testuser")) // check if the user exists
    {
        std::cout << "User exists in the database." << std::endl;
    }
    else
    {
        std::cout << "User does not exist in the database." << std::endl;
    }
    std::cout << "H" << std::endl;
    return 0;
    // Game variables

    // Game loop
    while (true)
    {
        // Ask for username, if already exists load data
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;
        // check database for username
        std::string sql = "SELECT * FROM users WHERE username = '" + username + "';";
        char *errMsg = 0;
        retrieveAsset(db, username); // retrieve user data from database
    }

    sqlite3_close(db); // close database connection
    return 0;
}

#endif