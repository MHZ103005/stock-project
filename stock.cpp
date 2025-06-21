#include "stock.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// Constructor and Destructor
Stock::Stock(const std::string &t, int q, double p)
    : Asset(t, q, p) {}
Stock::~Stock() = default;

// print stock information
void Stock::printInfo() const { std::cout << Stock::ticker << std::endl; }
