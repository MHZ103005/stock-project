#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "stock.h"
#include "portfolio.h"

int main()
{
    Stock *stock = new Stock("AAPL", 10, 150);
    Stock *s = new Stock("GOOG", 10, 150);
    stock->setTicker("Goo");

    system("API.py");
}

#endif