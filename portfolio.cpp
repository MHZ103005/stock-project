#ifndef PORTFOLIO_H
#define PORTFIOLIO_H
#include <iostream> // libraries
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <thread>
#include <chrono>

#include "stock.h" // files
#include "portfolio.h"
#include "asset.h"

Portfolio::Portfolio() {}; // only default constructor

Portfolio::~Portfolio() = default;

std::vector<Asset> &Portfolio::getAssets()
{
    return this->assets;
}

void Portfolio::addAsset(const Asset &a)
{
    assets.push_back(a);
}

void Portfolio::removeAsset(const std::string &ticker)
{
    for (size_t i = 0; i < assets.size(); i++)
    {
        if (assets[i].getTicker() == ticker) // remove if ticker matches
        {
            assets.erase(assets.begin() + i);
            return;
        }
    }
    return;
}

bool Portfolio::updateAmount(const std::string &ticker, double quantity)
{
    for (auto &asset : assets)
    {
        if (asset.getTicker() == ticker) // update quantity if ticker matches
        {
            if (asset.getQuantity() + quantity < 0) // check if quantity is negative
            {
                std::cout << "You do not own this much!" << std::endl;
                return false;
            }
            else if (asset.getQuantity() + quantity == 0) // if quantity is 0, remove asset
            {
                removeAsset(ticker);
                return true;
            }
            else // update quantity
            {
                asset.setQuantity(asset.getQuantity() + quantity);
                return true;
            }
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
    for (const Asset &asset : this->assets)
    {
        tick += asset.getTicker();
        tick += " ";
    }
    Myfile << tick;
    // std::cout << tick << std::endl;
    Myfile.close();

    // pause while waiting for API
    std::this_thread::sleep_for(std::chrono::seconds(3));

    Myfile.open("prices.txt");
    std::string priceStr;
    float totalValue = 0;
    for (const Asset &asset : this->assets)
    {
        std::getline(Myfile, priceStr);
        float price = std::stof(priceStr);
        std::cout << asset.getTicker() << " is currently at " << price << std::endl;
        totalValue += price * asset.getQuantity();
    }
    std::cout << "Your portfolio is currently worth $" << totalValue << std::endl;
    Myfile.close();
}

#endif
