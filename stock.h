#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "asset.h"

class Stock : public Asset
{
private:
    std::string exchange;
    std::string companyName;

public:
    Stock(const std::string &t, float q, double p);
    ~Stock();

    void printInfo() const; // debugging
};