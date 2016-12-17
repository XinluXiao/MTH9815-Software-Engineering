#pragma once
/**
 * BondInquiryService.hpp
 * Define BondInquiryService class and BondInquiryConnector class
 * @Create by Xinlu Xiao
 */

#ifndef BONDINQUIRYSERVICE_HPP
#define BONDINQUIRYSERVICE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include "inquiryservice.hpp"
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
#include "BondMarketDataService.hpp"
#include "globalfunctions.hpp"

using namespace std;

class BondInquiryService : public Service<string, Inquiry<Bond>>
{
public:
	// override the virtual function
	//virtual Inquiry<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<Bond> &data) override
	{
		cout << "You are now in the inquiry service, sending an inquiry object with QUOTED state" << endl;
		data.StateDecide(InquiryState::QUOTED);

		// Initialzie a BondHistoricalDataService object pointer and use inquiry connector to publish data
		BondHistoricalDataService::Add_example()->Persist_Inquiry(data);
	}

	// override the virtual function
	void SendQuote(const string &inquiryId, double price) {};

	// Reject an inquiry from the client
	void RejectInquiry(const string &inquiryId) {};

	// Initialize the BondInquiryService object as a pointer
	static BondInquiryService *Add_example()
	{
		static BondInquiryService example;
		return &example;
	}

private:
	// ctor
	BondInquiryService() {};
};



class BondInquiryConnector : public Connector<OrderBook <Bond>>
{
public:
	// override the virtual function
	virtual void Publish(OrderBook<Bond> &data) override {};

	// Read the inquiries.txt
	void ReadInquiryData()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading the inquiry data" << endl;
		static int inquiry_index = 1;
		ifstream myfile("inquiries.txt");
		string row;
		getline(myfile, row);
		while (getline(myfile, row))
		{
			string product_type, price, quantity, side, state;

			// create a string vector to store the data read from the txt file
			vector<string> result = readbyline(row);

			// assign the elements in the vector to the attributes
			tie(product_type, price, quantity, side, state) = make_tuple(result[0], result[1],
				result[2], result[3], result[4]);

			// convert to string
			string _inquiryId = to_string(inquiry_index);

			// Initialize a Bond object based on the product type
			// Review of Bond ctor:
			// Bond(string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate);
			Bond &bond_object = bond_map[product_type];
			Side _side;
			if (side == "BUY")
			{
				_side = BUY;
			}
			else
			{
				_side = SELL;
			}
			long _quantity = stod(quantity);  //convert to the long type
			double _price = stod(price);  //convert to the long type
			InquiryState _state;
			if (state == "RECEIVED")
			{
				_state = InquiryState::RECEIVED;
			}
			else
			{
				assert(false);
			}

			// initialize the Inquiry object based on the attributes
			// Review of Inquiry ctor
			// Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state);
			Inquiry<Bond> inquiry_object(_inquiryId, bond_object, _side, _quantity, _price, _state);
			bond_service->OnMessage(inquiry_object);
		}
		inquiry_index++;
		cout << "Finish Reading......" << endl << endl;
	}

	// Initialize the BondInquiryConnector object as a pointer
	static BondInquiryConnector *Add_example()
	{
		static BondInquiryConnector example;
		return &example;
	}

private:
	// BondInquiryService object pointer
	BondInquiryService *bond_service;

	// Initialize the bond_service as object pointer of BondInquiryService
	BondInquiryConnector()
	{
		bond_service = BondInquiryService::Add_example();
	}
};

#endif
