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
    p.getPrice();

    return 0;
}

#endif