#pragma once
/**
* marketdataFileGenerator.hpp
* Generate marketdata.txt 
* Relevant market data attributes: product, price, quantity, side, state
* @ Create by Xinlu Xiao
*/

#ifndef INQUIRYFILEGENERATOR_HPP
#define INQUIRYFILEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "tradeFileGenerator.hpp"  // Use the string array product_type 

using namespace std;

void inquiry_generate()
{
	cout << "Generating the inquiry data" << endl;
	ofstream myfile;
	myfile.open("inquiries.txt");
	myfile << "product, price, quantity, side, state" << endl;

	// 6 products
	for (int i = 0; i < 6; ++i)
	{
		string product_T = product_type[i];
		// 10 for each product
		for (int j = 0; j < 10; ++j)
		{
			// Set the price as 100;
			string priceNum = to_string(100);
			int quantity = 10000 * (rand() % 9 + 1);
			string side;
			// if the random number is even, then "BUY"
			if (rand() % 2 == 0)
			{
				side = "BUY";
			}
			else
			{
				side = "SELL";
			}
			// each inquiry should be with state "RECEIVED"
			string state = "RECEIVED"; 
			// Result
			myfile << product_T << "," << priceNum << "," <<quantity<<","<< side << "," << state << endl;
		}
	}
	cout << "Finishing generating the inquiry data" << endl;
	
}


#endif
