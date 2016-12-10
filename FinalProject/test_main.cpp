/**
 * test_main.cpp
 * Test files
 * @ Create by Xinlu Xiao
 */

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "tradeFileGenerator.hpp"
#include "priceFileGenerator.hpp"
#include "marketdataFileGenerator.hpp"

using namespace std;

int main()
{
   trade_generate();
   price_generate();
   marketdata_generate();
   return 0;
}
