#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "stock.h"
#include "portfolio.h"

int main()
{
    Stock *stock = new Stock("AAPL", 10, 150);
    Stock *s = new Stock("GOOG", 10, 150);
    stock->setTicker("Goo");

    Portfolio p;
    p.addAsset(stock);
    p.addAsset(s);
    p.printList();
    p.removeAsset("Goo");
    p.printList();
    std::cout << "PENIS" << std::endl;
    delete stock;
    delete s;
}

#endif