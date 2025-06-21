#ifndef PORTFOLIO_H
#define PORTFIOLIO_H
#include "portfolio.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

Portfolio::Portfolio() {}; // only default constructor

Portfolio::~Portfolio() = default;

void Portfolio::addAsset(Asset *a)
{
    assets.push_back(a);
}

bool Portfolio::removeAsset(const std::string &ticker)
{
    for (size_t i = 0; i < assets.size(); i++)
    {
        if (assets[i]->getTicker() == ticker) // remove if ticker matches
        {
            assets.erase(assets.begin() + i);
            return true;
        }
    }
    return false;
}

float Portfolio::getValue() const
{
    // placeholder for now. Use API calls found in STOCK function
}

void Portfolio::printList() const
{
    for (const auto &asset : this->assets)
    {
        std::cout << asset->getTicker()
                  << std::endl;
    }
}

#endif
