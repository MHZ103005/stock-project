#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <string>
#include <vector>

class Asset
{
  protected:
    std::string ticker;
    double quantity;
    double price;
    double buyValue;

  public:
    Asset();
    Asset(const std::string &t, double q);
    Asset(const std::string &t, double q, double p);

    virtual ~Asset();

    const std::string &getTicker() const;
    double getQuantity() const;
    double getPrice() const;

    void setTicker(const std::string &newTicker);
    void setQuantity(double newQuantity);
    void setPrice(double newPrice);
};

#endif