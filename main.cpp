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

bool tickerExists(const std::string &ticker);

int main()
{
    sqlite3 *db;
    int exit = sqlite3_open("portfolio.db", &db);

    if (exit)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }
    else
    {
        std::cout << "Database opened successfully!" << std::endl;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS assets ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "ticker TEXT NOT NULL, "
                      "quantity REAL NOT NULL, "
                      "price REAL NOT NULL);";

    char *errMsg;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Table created successfully!" << std::endl;
    }

    sqlite3_close(db);
    return 0;

    std::string input;
    bool portfolioCreated = false;
    Portfolio portfolio;
    std::cout << "Portfolio tracker created by Michael Zheng" << std::endl;
    while (1)
    {
        std::cout << "Enter a command (create, add, remove, list, price, exit, help): " << std::endl;
        std::getline(std::cin, input);
        // Convert input to lowercase for case-insensitive comparison
        for (auto &c : input)
        {
            c = tolower(c);
        }
        if (input == "add")
        {
            std::string ticker;
            float quantity;
            double price;

            std::cout << "Enter ticker: ";
            std::getline(std::cin, ticker);
            // Check if ticker exists
            if (!tickerExists(ticker))
            {
                std::cout << "Ticker does not exist. Please try again." << std::endl;
                continue;
            }
            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            std::cout << "Enter price: ";
            std::cin >> price;
            portfolioCreated = true;
            std::cin.ignore(); // clear the newline character from the input buffer
            Asset newAsset(ticker, quantity, price);
            portfolio.addAsset(newAsset);
            std::cout << "Asset added." << std::endl;
        }
        // Remove asset from portfolio
        else if (input == "remove")
        {
            std::string ticker;
            std::cout << "Enter ticker to remove: ";
            std::getline(std::cin, ticker);
            if (portfolio.removeAsset(ticker))
            {
                std::cout << "Asset removed." << std::endl;
            }
            else
            {
                std::cout << "Asset not found." << std::endl;
            }
        }
        else if (input == "list")
        { // list all assets in portfolio, and current worth
            if (!portfolioCreated)
            {
                std::cout << "No portfolio created yet. Please create a portfolio first." << std::endl;
            }
            else
            {
                portfolio.printList();
                portfolio.getPrice();
            }
        }
        else if (input == "exit") // exit from program
        {
            break;
        }
        else if (input == "help") // list all available commands
        {
            std::cout << "Available commands:" << std::endl;
            std::cout << "add - Add an asset to the portfolio. If no portfolio exists create a new portfolio." << std::endl;
            std::cout << "remove - Remove an asset from the portfolio." << std::endl;
            std::cout << "list - List all assets in the portfolio." << std::endl;
            std::cout << "price - Get the current price of all assets in the portfolio." << std::endl;
            std::cout << "exit - Exit the program." << std::endl;
        }
        else
        {
            std::cout << "Please enter a valid command, or type help for a list of commands." << std::endl;
        }
    }
    std::cout << "THanks for using my portfolio service" << std::endl;
    return 0;
}

bool tickerExists(const std::string &ticker)
{
    std::fstream file("tickers.txt");
    file << ticker << std::endl;
    file.close();

    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate waiting for API response
    file.open("prices.txt");
    std::string line;
    std::getline(file, line);
    file.close();
    if (line == "F")
    {
        return false;
    }

    return true;
}

#endif