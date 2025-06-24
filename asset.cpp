#include "asset.h"
#include <iostream>
#include <string>

// Constructor and Destructor
Asset::Asset() {}
Asset::Asset(const std::string &t, float q, double p)
    : ticker(t), quantity(q), price(p) {}

Asset::~Asset() = default;

// Getters
const std::string &Asset::getTicker() const
{
    return ticker;
}
float Asset::getQuantity() const
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
void Asset::setQuantity(float newQuantity)
{
    quantity = newQuantity;
}
void Asset::setPrice(double newPrice)
{ // maybe remove denpending on api
    price = newPrice;
}