#pragma once
/**
 * step_one.hpp
 * The first step in the main.cpp
 * @Create by Xinlu Xiao
 */

#ifndef STEP_ONE_HPP
#define STEP_ONE_HPP

#include <iostream>
#include "tradeFileGenerator.hpp"
#include "priceFileGenerator.hpp"
#include "marketdataFileGenerator.hpp"
#include "inquiryFileGenerator.hpp"

using namespace std;

void step_one_function()
{
	cout << "/*****************************Part 1***************************/" << endl;
	cout << "/*****************Generate the required files******************/" << endl;
	cout << "/**************************************************************/" << endl;
	trade_generate();   // For trades.txt
	price_generate();   // For prices.txt
	marketdata_generate();   // For marketdata.txt
	inquiry_generate();    // For inquiries.txt
}

#endif
