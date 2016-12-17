/**
* tradeFileGenerator.hpp
* Generate trade.txt file we would use in the project
* @Create by Xinlu Xiao
*/

#ifndef TRADEFILEGENERATOR_HPP
#define TRADEFILEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

// CUSIPS root:912828
string product_type[] = { "912828U40", // 2Y
			  "912828U32", // 3Y
			  "912828U65", // 5Y
			  "912828U57", // 7Y
			  "912828U24", // 10Y
			  "912828U40" };// 30Y
			 
 // trade file generator
void trade_generate()
{
	cout << "Generating the trade data" << endl;
	ofstream myfile;
	myfile.open("trades.txt");
	myfile << "product, tradeId, book, quantity, side" << endl;

	for (int i = 0; i < 6; ++i)
	{
		string product_T = product_type[i];
		//Then for each product, we create 10 trades
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
			// Position
			int positionNum = 100000 * (rand() % 9 + 1);
			// Side
			string SideNum;
			if (rand() % 2 == 1) SideNum = "BUY";
			else SideNum = "SELL";
			// Result
			myfile << product_T << ",T" << 250 * i + 20 * j << ",TRSY" << rand() % 3 + 1 << "," << positionNum << "," << SideNum << endl;
		}
	}
	cout << "Finishing generating the trade data" << endl;
}

#endif
