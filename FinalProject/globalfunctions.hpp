#pragma once
/**
 * globalfunctions.hpp
 * Contain 3 funcitons:
 * (1) Define two maps by "maps_initial" 
 * (2) Define the "readbyline" function to read the data
 * (3) Define the function that can translate price from "100-xyz" to double type
 * @Create by Xinlu Xiao
 */

#ifndef GLOBALFUNCTIONS_HPP
#define GLOBALFUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include "products.hpp"
#include "tradeFileGenerator.hpp"
#include "positionservice.hpp"

using namespace std;

// Define two global variables - maps
map<string, Bond> bond_map;
map<string, Position<Bond>> bond_position_map;

void maps_initial()
{
	cout << "*************Message****************" << endl;
	cout << "Initializing the two maps" << endl;
	// Initialize the two maps
	if (bond_map.size() == 0 && bond_position_map.size() == 0)
	{
		// Initialize the Bond type vector
		// Review: Bond constructor 
		// Bond(string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate);
		// For each product, initialize one Bond object
		Bond temp[] = {
			Bond(product_type[0], CUSIP, "T", 0.0018, date(2018,12,10)),
			Bond(product_type[1], CUSIP, "T", 0.0021, date(2019,12,10)),
			Bond(product_type[2], CUSIP, "T", 0.0025, date(2021,12,10)),
			Bond(product_type[3], CUSIP, "T", 0.0027, date(2023,12,10)),
			Bond(product_type[4], CUSIP, "T", 0.0031, date(2026,12,10)),
			Bond(product_type[5], CUSIP, "T", 0.0040, date(2046,12,10))
		};
		for (int i = 0; i < 6; i++)
		{
			// For each product type, assign the elements in the temp vector to the type
			bond_map[product_type[i]] = temp[i];
			// Initialize the value for the bond_position_map
			Position<Bond> b_position(temp[i]); 
			b_position.position_begin();
			// For each product type, assign the elements in the temp vector to the type
			bond_position_map[product_type[i]] = b_position;
		}
	}
	cout << "Finishing the initializing..." << endl<<endl;
	
}

// Read data from the txt file
vector<string> readbyline(string row)
{
	stringstream myfile(row);
	vector<string> mystring;
	string a;
	while (getline(myfile, a, ','))
	{
		mystring.push_back(a);
	}
	return mystring;
}

// Initialize one static variable to count the price translating
static int count_num = 1; // Count the number of the price translating
// Translate price from "100-xyz" to double type
double price_translate(string price)
{
	
	cout << "In the price translating...for order:"<< count_num++ << endl;
	// translate the last digit
	int n = price.size(); // get the size of string
	char last_digit = price[n - 1]; // get the last digit
	double last_digit_double, last_digit_translate;
	if (last_digit == '+') last_digit_double = 4.0;
	else last_digit_double = last_digit - '0';
	last_digit_translate = last_digit_double / 256.0; // translate it into real price

	// translate the integer part
	size_t pivot = price.find_first_of('-'); // find the '-' as the pivot
	double int_part = stoi(price.substr(0, pivot));  // get the integer part

	// translate the middle part
	double mid_digit = stoi(price.substr(pivot + 1, 2)); //get the part between the integer part and last digit
	double mid_digit_translate;
	mid_digit_translate = mid_digit / 32.0;  // translate it into real price

	// the whole number
	double price_result = int_part + mid_digit_translate + last_digit_translate;
	cout << "Finishing the price translating" << endl;
	return price_result;
}

#endif
