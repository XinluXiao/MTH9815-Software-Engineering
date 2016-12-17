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
	// Get data on our service given a key
	virtual Inquiry<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<Bond> &data) override
	{
		cout << "You are now in the inquiry service, sending an inquiry object with DONE state" << endl;
		data.StateDecide(InquiryState::QUOTED);
		BondHistoricalDataService::Add_example()->Persist_Inquiry(data);
	}

	// Send a quote back to the client
	void SendQuote(const string &inquiryId, double price) {};

	// Reject an inquiry from the client
	void RejectInquiry(const string &inquiryId) {};

	static BondInquiryService *Add_example()
	{
		static BondInquiryService example;
		return &example;
	}

private:
	BondInquiryService() {};
};



class BondInquiryConnector : public Connector<OrderBook <Bond>>
{
public:
	virtual void Publish(OrderBook<Bond> &data) override {};

	// Read the inquiry data
	void ReadInquiryData()
	{
		cout << "You are reading the inquiry data" << endl;
		static int inquiry_index = 1;
		ifstream myfile("inquirydata.txt");
		string row;
		getline(myfile, row);
		while (getline(myfile, row))
		{
			string product_type, price, quantity, side, state;
			vector<string> result = readbyline(row);
			tie(product_type, price, quantity, side, state) = make_tuple(result[0], result[1],
				result[2], result[3], result[4]);
			//(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state) :
			string _inquiryId = to_string(inquiry_index);
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
			long _quantity = stod(quantity);
			double _price = stod(price);
			InquiryState _state;
			if (state == "RECEIVED")
			{
				_state = InquiryState::RECEIVED;
			}
			else
			{
				assert(false);
			}
			Inquiry<Bond> inquiry_object(_inquiryId, bond_object, _side, _quantity, _price, _state);
			bond_service->OnMessage(inquiry_object);
		}
		inquiry_index++;
	}

	static BondInquiryConnector *Add_example()
	{
		static BondInquiryConnector example;
		return &example;
	}

private:
	BondInquiryService *bond_service = nullptr;

	BondInquiryConnector()
	{
		bond_service = BondInquiryService::Add_example();
	}
};

#endif
