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

    // Game variables
    Portfolio portfolio; // create portfolio object

    // Ask for username, if already exists load data
    std::string username;
    int userid = -1;
    std::cout << "Enter your username: ";
    std::cin >> username;
    // check database for username
    std::string sql = "SELECT * FROM users WHERE username = '" + username + "';";
    char *errMsg = 0;
    // Check if user exists, if user doesn't exist create new user
    if (checkUsername(db, username))
    {
        userid = retrieveUserID(db, username); // retrieve user ID
        std::cout << "Welcome back, " << username << "!" << std::endl;
        // Load portfolio assets
        std::vector<std::string> tickers;
        std::vector<double> quantities;
        loadPortfolio(db, userid, tickers, quantities);
        for (int i = 0; i < tickers.size(); i++)
        {
            portfolio.addAsset(Asset(tickers[i], quantities[i])); // add assets to portfolio
        }
    }
    else
    {
        std::cout << "Username not found. Creating new user..." << std::endl;
        insertUser(db, username);              // insert new user into database
        userid = retrieveUserID(db, username); // retrieve user ID
        std::cout << "New user created!" << std::endl;
    }

    // Main game loop
    while (true)
    {
        std::cout << "1. Buy Asset\n2. Sell Asset\n3. View Portfolio\n4. Get Prices\n5. View Purchase Log\n6. Help\n7. Exit\n";
        std::cout << std::endl
                  << std::endl;
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1: // Add Asset
        {
            std::string ticker;
            double quantity;
            std::cout << "Enter asset ticker: ";
            std::cin >> ticker;
            while (!tickerExists(ticker)) // check if ticker is valid
            {
                std::cout << "Invalid ticker! Please enter a valid ticker: ";
                std::cin >> ticker;
            }
            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            std::cout << "Enter price (enter 0 to use current price): ";
            double price;
            std::cin >> price;
            if (price <= 0)
            {
                Asset asset(ticker, quantity);
                asset.findPrice();
                // if Asset already exists, update quantity
                if (portfolio.updateAmount(ticker, quantity)) // update quantity if asset already exists
                {
                    std::cout << "Updated quantity of " << ticker << "." << std::endl;
                }
                else
                {
                    portfolio.addAsset(asset); // add new asset to portfolio
                    std::cout << "Asset added to portfolio!" << std::endl;
                }
                price = asset.getPrice(); // get current price of asset
            }
            else
            {
                Asset asset(ticker, quantity, price);
                portfolio.addAsset(asset);
            }

            insertTrade(db, userid, ticker, "buy", quantity, price); // insert trade into database
            std::cout << std::endl;
            break;
        }
        case 2:
        {
            std::string ticker;
            double quantity;
            std::cout << "Enter asset ticker to sell: ";
            std::cin >> ticker;
            std::cout << "Enter quantity to sell: ";
            std::cin >> quantity;
            // create new asset to get current price
            Asset *a = new Asset(ticker, 0);
            a->findPrice();                                    // find price of asset
            if (portfolio.updateAmount(ticker, -1 * quantity)) // remove asset from portfolio
            {
                insertTrade(db, userid, ticker, "sell", quantity, a->getPrice());
                std::cout << "Succesfully sold " << quantity << " of " << ticker << std::endl;
                delete a;
                a = nullptr;
            }
            else
            {
                std::cout << "Asset not found in portfolio!" << std::endl
                          << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 3: // View Portfolio
        {
            portfolio.printList(); // print portfolio assets
            std::cout << std::endl;
            break;
        }
        case 4: // Get Prices
        {
            portfolio.getPrice(); // get prices of assets
            std::cout << std::endl;
            break;
        }
        case 5: // View Purchase Log
        {
            printPurchaseLog(db, userid); // print purchase log
            std::cout << std::endl;
            break;
        }
        case 6: // help
        {
            // implement
        }
        case 7: // exit
        {
            // update assets table with portfolio assets
            deleteAssets(db, userid); // delete existing assets
            for (const auto &asset : portfolio.getAssets())
            {
                insertAsset(db, userid, asset.getTicker(), asset.getQuantity()); // insert assets into database
            }
            sqlite3_close(db); // close database connection
            return 0;
        }
        default:
        {
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
        }
    }
}

#endif