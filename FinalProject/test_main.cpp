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
#include "inquiryFileGenerator.hpp"
#include "marketdataFileGenerator.hpp"
#include "globalfunctions.hpp"
#include "Bondtradebookingservice.hpp"
//#include "Bondpositionservice.hpp"
#include "BondPricingService.hpp"
#include "BondInquiryService.hpp"
//#include "BondMarketDataService.hpp"

using namespace std;

int main()
{
   //trade_generate();
   //price_generate();
   //marketdata_generate();
   //inquiry_generate();

	maps_initial();
	BondInquiryConnector::Add_example()->ReadInquiryData();
	BondPricingConnector::Add_example()->ReadPriceData();
	Bondtradeconnector::Add_example()->Readtradedata();
	BondMarketDataConnector::Add_example()->ReadMarketData();

	return 0;
}
