#pragma once
#include <stdio.h>
#include <vector>
#include <string.h>
#include "asset.h"

class Portfolio
{
private:
    std::vector<Asset> assets;

public:
    Portfolio();
    ~Portfolio();

    std::vector<Asset> &getAssets();
    void addAsset(const Asset &a);
    void removeAsset(const std::string &a);
    bool updateAmount(const std::string &ticker, double quantity);

    void printList() const;
    void getPrice() const;
};