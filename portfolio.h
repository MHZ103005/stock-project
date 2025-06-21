#pragma once
#include <stdio.h>
#include <vector>
#include <string.h>
#include "asset.h"

class Portfolio
{
private:
    std::vector<Asset *> assets;

public:
    Portfolio();
    ~Portfolio();

    void addAsset(Asset *a);
    bool removeAsset(const std::string &a);
    float getValue() const;
    void printList() const;
};