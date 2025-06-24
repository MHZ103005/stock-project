#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "stock.h"
#include "portfolio.h"

int main()
{
    Portfolio p;
    Stock s("GOOG", 10, 150);
    p.addAsset(s);
    Stock s2("AAPL", 10, 160);
    p.addAsset(s2);
    p.getPrice();

    return 0;
}

#endif