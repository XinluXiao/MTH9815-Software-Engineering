#pragma once
/**
* step_three.hpp
* The second step in the main.cpp
* @Create by Xinlu Xiao
*/

#ifndef STEP_THREE_HPP
#define STEP_THREE_HPP

#include <iostream>
#include "Bondtradebookingservice.hpp"
#include "Bondpositionservice.hpp"
#include "BondPricingService.hpp"
#include "BondInquiryService.hpp"
#include "BondMarketDataService.hpp"
#include "BondAlgoExecutionService.hpp"
#include "BondAlgoStreamingService.hpp"

using namespace std;

void step_three_function()
{
	cout << "/*****************************Part 3*******************************/" << endl;
	cout << "/***********************Test the connectors************************/" << endl;
	cout << "/******************************************************************/" << endl;
	Bondtradeconnector::Add_example()->Readtradedata();
	BondMarketDataConnector::Add_example()->ReadMarketData();
	BondPricingConnector::Add_example()->ReadPriceData();
	BondInquiryConnector::Add_example()->ReadInquiryData();
}

#endif