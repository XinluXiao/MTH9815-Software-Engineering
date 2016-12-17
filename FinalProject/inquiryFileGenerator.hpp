#pragma once
/**
* marketdataFileGenerator.hpp
* Generate marketdata.txt we would use in the project
* @ Create by Xinlu Xiao
*/

#ifndef INQUIRYFILEGENERATOR_HPP
#define INQUIRYFILEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "tradeFileGenerator.hpp"

using namespace std;

void inquiry_generate()
{
	cout << "Generating the inquiry data" << endl;
	ofstream myfile;
	myfile.open("inquiries.txt");
	myfile << "product, price, quantity, side, state" << endl;

	for (int i = 0; i < 6; ++i)
	{
		string product_T = product_type[i];
		for (int j = 0; j < 10; ++j)
		{
			/*
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
			*/

			string priceNum = to_string(100);
			int quantity = 10000 * (rand() % 9 + 1);
			string side;
			if (rand() % 2 == 0)
			{
				side = "BUY";
			}
			else
			{
				side = "SELL";
			}
			string state = "RECEIVED";  // each inquiry should be with state "RECEIVED"
			myfile << product_T << "," << priceNum << "," <<quantity<<","<< side << "," << state << endl;
		}
	}
	cout << "Finishing generating the inquiry data" << endl;
	
}


#endif
