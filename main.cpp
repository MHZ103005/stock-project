#ifndef MAIN
#define MAIN
#include "portfolio.h"
#include "sqlfunc.h"
#include "sqlite3.h"
#include "stock.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <thread>

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

    // insertUser(db, "testuser", 10000.0); // insert a test user into the database
    std::cout << "D" << std::endl;
    if (checkUsername(db, "testuser")) // check if the user exists
    {
        std::cout << "User exists in the database." << std::endl;
    }
    else
    {
        std::cout << "User does not exist in the database." << std::endl;
    }

    insertTrade(db, 1, "GOOG", "buy", 10, 150.0); // insert a test trade into the database
    std::cout << "H" << std::endl;
    printPurchaseLog(db, 1); // print the purchase log for the user
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