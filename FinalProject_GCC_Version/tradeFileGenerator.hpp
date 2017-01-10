/**
* tradeFileGenerator.hpp
* Generate trade.txt file 
* Relevant trade attributes in the trade class: product, tradeId, book, quantity, side
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

	// 6 product type
	for (int i = 0; i < 6; ++i)
	{
		string product_T = product_type[i];
		//10 trades for each product
		for (int j = 0; j < 10; ++j)
		{
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
