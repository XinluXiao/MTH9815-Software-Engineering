/**
 * priceFileGenerator.hpp
 * Generate price.txt we would use in the program
 * @ Created by Xinlu Xiao
 */

#ifndef PRICEFILEGENERATOR_HPP
#define PRICEFILEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "tradeFileGenerator.hpp"

using namespace std;

// price file generator
void price_generate()
{
	cout << "Generating the price data" << endl;
	
        ofstream myfile;
        myfile.open("price.txt");
        myfile << "product, mid, bid_offer_spread" << endl;
	
	for(int i = 0; i < 6; ++i)
	{
	   string product_T = product_type[i];
	   for(int j = 0; j < 10; ++j)  // In the true test, change 10 to 1000000
	   {
		int num0 = rand() % 2 + 99; // Generate a number between 99 and 100
                int num1 = rand() % 32; // Generate a number between 0 and 31
                int num2 = rand() % 8;  // Generate a number between 0 and 7
                string num0_s = to_string(num0) + "-";
                string num1_s;
                if (num1 < 10) num1_s = "0" + to_string(num1);
                else num1_s = to_string(num1);
                string num2_s;
                if (num2 == 4)  num2_s = "+";  // If the random number is 4, represent it by "+"
                else num2_s = to_string(num2);
                // Price
                string priceNum = num0_s + num1_s + num2_s;
	   	int spreadBase = rand() % 3 + 2;  // spreadBase should between 2 and 4 since oscillation is between 1/128 and 1/64
		// Bid/offer spread
		string spreadNum;
		if(spreadBase == 4) spreadNum = "0-00+";
		else spreadNum = "0-00" + to_string(spreadBase);
		// result
		myfile << product_T << "," << priceNum << "," << spreadNum << endl;
		
	}
}	
	cout << "Finishing generating the price data" << endl;
}
#endif
