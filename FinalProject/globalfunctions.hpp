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
#include "positionservice.hpp"
#include "products.hpp"
#include "tradeFileGenerator.hpp"

using namespace std;

// Define two maps
map<string, Bond> bond_map;
map<string, Position<Bond>> bond_position_map;

void maps_initial()
{
	// Initialize the two maps
	if (bond_map.size() == 0 && bond_position_map.size() == 0)
	{
		Bond temp[] = {
			Bond(product_type[0], CUSIP, "T", 0.0185, date(2018,12,10)),
			Bond(product_type[1], CUSIP, "T", 0.01034, date(2019,12,10)),
			Bond(product_type[2], CUSIP, "T", 0.0176, date(2021,12,10)),
			Bond(product_type[3], CUSIP, "T", 0.02215, date(2023,12,10)),
			Bond(product_type[4], CUSIP, "T", 0.0202, date(2026,12,10)),
			Bond(product_type[5], CUSIP, "T", 0.0275, date(2046,12,10))
		};
		for (int i = 0; i < 6; ++i)
		{
			bond_map[product_type[i]] = temp[i];
			Position<Bond> b_position(temp[i]);
			b_position.position_begin();
			bond_position_map[product_type[i]] = b_position;
		}
	}
}

// Read data from the txt file
vector<string> readbyline(string l)
{
	stringstream myfile(l);
	vector<string> mystring;
	string a;
	while (getline(myfile, a, ','))
	{
		mystring.push_back(a);
	}
	return mystring;
}

// Translate price from "100-xyz" to double type
double price_translate(string price)
{
	// translate the last digit
	int n = price.size();
	char last_digit = price[n - 1];
	double last_digit_double, last_digit_translate;
	if (last_digit == '+') last_digit_double = 4.0;
	else last_digit_double = last_digit - '0';
	last_digit_translate = last_digit_double / 256.0;

	// translate the integer part
	size_t pivot = price.find_first_of('-');
	double int_part = stoi(price.substr(0, pivot));

	// translate the middle part
	double mid_digit = stoi(price.substr(pivot + 1, 2));
	double mid_digit_translate;
	mid_digit_translate = mid_digit / 32.0;

	// the whole number
	double price_result = int_part + mid_digit_translate + last_digit_translate;
	return price_result;
}

#endif
