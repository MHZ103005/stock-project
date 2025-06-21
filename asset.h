#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <string>
#include <vector>

class Asset
{
protected:
    std::string ticker;
    int quantity;
    double price;

public:
    Asset();
    Asset(const std::string &t, int q, double p);

    virtual ~Asset();

    const std::string &getTicker() const;
    int getQuantity() const;
    double getPrice() const;

    void setTicker(const std::string &newTicker);
    void setQuantity(int newQuantity);
    void setPrice(double newPrice);
};

#endif