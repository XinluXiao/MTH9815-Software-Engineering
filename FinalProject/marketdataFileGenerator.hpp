/**
 * marketdataFileGenerator.hpp
 * Generate marketdata.txt we would use in the project
 * @ Create by Xinlu Xiao
 */

#ifndef MARKETDATAFILEGENERATOR_HPP
#define MARKETDATAFILEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

void marketdata_generate()
{
   ofstream myfile;
   myfile.open("marketdata.txt");
   myfile << "product,"
	  << "bidprice1,"
	  << "position1,"
	  << "bidprice2,"
	  << "position2,"
	  << "bidprice3,"
	  << "position3,"
	  << "bidprice4,"
	  << "position4,"
	  << "bidprice5,"
	  << "position5,"
	  << "offerprice1,"
	  << "position1,"
	  << "offerprice2,"
	  << "position2,"
	  << "offerprice3,"
  	  << "position3,"
	  << "offerprice4,"
	  << "position4,"
	  << "offerprice5,"
	  << "position5"
	  << endl;
        for(int i = 0; i < 6; ++i)
        {
           string product_T = product_type[i];
           for(int j = 0; j < 10; ++j)  // In the true test, change 10 to 1000000
           {
                int spread = rand() % 513;
		// Bid price and positions
		int bid_spread = spread - 1;
		for(int k = 0; k < 5; ++k)
		{
		   int bid_spread_base = bid_spread / 256;
		   int num0_b = bid_spread_base + 99; // Generate the base number
                   int num1_b = rand() % 32; // Generate a number between 0 and 31
                   int num2_b = rand() % 8;  // Generate a number between 0 and 7
                   string num0_s_b = to_string(num0_b) + "-";
                   string num1_s_b;
                   if (num1_b < 10) num1_s_b = "0" + to_string(num1_b);
                   else num1_s_b = to_string(num1_b);
                   string num2_s_b;
                   if (num2_b == 4)  num2_s_b = "+";  // If the random number is 4, represent it by "+"
                   else num2_s_b = to_string(num2_b);
		   // Bid Price
                   string bid_price = num0_s_b + num1_s_b + num2_s_b;
		   int position_bid = 1000000 * (k + 1);
		   myfile << bid_price << "," << position_bid << ",";
		   bid_spread--;
		}
	        // Offer price and positions
		int offer_spread = spread + 1;
		for(int k = 0; k < 5; ++k)
		{
		   int offer_spread_base = offer_spread / 256;
		   int num0_o = offer_spread_base + 99;
		   int num1_o = rand() % 32;
		   int num2_o = rand() % 8;
		   string num0_s_o = to_string(num0_o) + "-";
		   string num1_s_o;
		   if(num1_o < 10) num1_s_o = "0" + to_string(num1_o);
		   else num1_s_o = to_string(num1_o);
		   string num2_s_o;
		   if(num2_o == 4) num2_s_o = "+";
		   else num2_s_o = to_string(num2_o);
		   // Offer Price
		   string offer_price = num0_s_o + num1_s_o + num2_s_o;
		   int position_offer = 1000000 * k;
		   myfile << offer_price << "," << position_offer << ",";
		   offer_spread++;
		 }
		 myfile << endl;
	   }
	}
}
#endif
