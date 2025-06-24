#ifndef PORTFOLIO_H
#define PORTFIOLIO_H
#include <iostream> // libraries
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>

#include "stock.h" // files
#include "portfolio.h"

Portfolio::Portfolio() {}; // only default constructor

Portfolio::~Portfolio() = default;

void Portfolio::addAsset(const Asset &a)
{
    assets.push_back(a);
}

bool Portfolio::removeAsset(const std::string &ticker)
{
    for (size_t i = 0; i < assets.size(); i++)
    {
        if (assets[i].getTicker() == ticker) // remove if ticker matches
        {
            assets.erase(assets.begin() + i);
            return true;
        }
    }
    return false;
}

void Portfolio::printList() const
{
    for (const auto &asset : this->assets)
    {
        std::cout << asset.getTicker()
                  << std::endl;
    }
}

void Portfolio::getPrice() const
{
    std::fstream Myfile("tickers.txt");
    std::string tick = ""; // add all tickers into one big string before updating file
    for (const auto &asset : this->assets)
    {
        tick += asset.getTicker();
        tick += " ";
    }
    Myfile << tick;
    std::cout << tick << std::endl;
    Myfile.close();

    Myfile.open("prices.txt");
    std::string priceStr;
    for (const auto &asset : this->assets)
    {
        std::getline(Myfile, priceStr);
        float price = std::stof(priceStr);
        std::cout << asset.getTicker() << " is currently at " << price << std::endl;
    }
    Myfile.close();
}

#endif
