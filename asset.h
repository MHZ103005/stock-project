#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <string>
#include <vector>

class Asset
{
protected:
    std::string ticker;
    float quantity;
    double price;
    float buyValue;

public:
    Asset();
    Asset(const std::string &t, float q, double p);

    virtual ~Asset();

    const std::string &getTicker() const;
    float getQuantity() const;
    double getPrice() const;

    void setTicker(const std::string &newTicker);
    void setQuantity(float newQuantity);
    void setPrice(double newPrice);
};

#endif