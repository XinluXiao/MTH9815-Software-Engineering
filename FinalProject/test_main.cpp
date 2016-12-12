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
#include "globalfunctions.hpp"

using namespace std;

int main()
{
   //trade_generate();
   //price_generate();
   //marketdata_generate();
	string p = "100-25+";
	double result = price_translate(p);
	cout << result;
   return 0;
}
