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

    void addAsset(const Asset &a);
    bool removeAsset(const std::string &a);

    void printList() const;
    void getPrice() const;
};