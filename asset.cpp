#include "asset.h"
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

// Constructor and Destructor
Asset::Asset()
{
}
Asset::Asset(const std::string &t, double q) : ticker(t), quantity(q)
{
} // constructor for loading from portfolio
Asset::Asset(const std::string &t, double q, double p) : ticker(t), quantity(q), price(p), buyValue(q * p)
{
}

Asset::~Asset() = default;

// Getters
const std::string &Asset::getTicker() const
{
    return ticker;
}
double Asset::getQuantity() const
{
    return quantity;
}
double Asset::getPrice() const
{
    return price;
}
// Setters
void Asset::setTicker(const std::string &newTicker)
{
    ticker = newTicker;
}
void Asset::setQuantity(double newQuantity)
{
    quantity = newQuantity;
}
void Asset::setPrice(double newPrice)
{ // maybe remove denpending on api
    price = newPrice;
}

double Asset::findPrice()
{
    std::fstream Myfile("tickers.txt");
    Myfile << ticker;
    Myfile.close();
    // pause while waiting for API
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Myfile.open("prices.txt");
    std::string priceStr;
    std::getline(Myfile, priceStr);
    Myfile.close();
    if (priceStr == "F")
    {
        std::cerr << "Error: Invalid ticker or price not found." << std::endl;
        return 0.0;
    }
    price = std::stod(priceStr);
    return price;
}