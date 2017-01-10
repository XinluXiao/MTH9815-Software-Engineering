#pragma once
/**
 * BondMarketDataService.hpp
 * Define BondMarketDataService and BondMarketDataConnector class
 * @Create by Xinlu Xiao
 */

#ifndef BONDMARKETDATASERVICE_HPP
#define BONDMARKETDATASERVICE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"
#include "globalfunctions.hpp"
#include "BondAlgoExecutionService.hpp"
#include "BondHistoricalDataService.hpp"

using namespace std;

class BondMarketDataService : public Service<string, OrderBook<Bond>>
{
public:
	// override the virtual function
	//virtual OrderBook<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond> &data) override
	{
		for(auto _listener: bond_listeners)
		{
			_listener->ProcessUpdate(data);
		}
	}

	// Initialize the BondMarketDataService object as a pointer
	static BondMarketDataService* Add_example()
	{
		static BondMarketDataService example;
		return &example;
	}
private:
	BondMarketDataService()
	{
		// BondAlgoExecutionService should register a ServiceListener on the BondMarketDataService
		AddListener(*(BondAlgoExecutionListener::Add_example()));

		// BondHistoricalDataListener should register a ServiceListener on the BondMarketDataService
		AddListener(*(BondHistoricalDataListener::Add_example()));
	}
};

class BondMarketDataConnector : public Connector<OrderBook<Bond>>
{
public:
	// override the virtual function
	virtual void Publish(OrderBook<Bond> &data) override {};

	// Read the data from marketdata.txt
	void ReadMarketData()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading market data" << endl;
		ifstream myfile("marketdata.txt");
		string row;
		PricingSide _bidpricingSide = BID; //initialize the bid price side
		PricingSide _offerpricingSide = OFFER; //initialize the offer price side
		vector<Order> bidOrder; //initialize the bid order vector
		vector<Order> offerOrder; //initialize the offer order vector
		getline(myfile, row);
		while (getline(myfile, row))
		{
			string product_type;
			double bid_price;
			double offer_price;
			long bid_quantity;
			long offer_quantity;
			int bidpivot = 1;
			int offerpivot = 1;

			// initialzie the string vector to store the data read from the txt file
			vector<string> data = readbyline(row);
			product_type = data[0];
			for (int i = 0; i < 5; ++i)
			{
				// bidOrder
				// translate the price 
				bid_price = price_translate(data[bidpivot++]); 
				bid_quantity = stol(data[bidpivot++]);  //convert string to long
				
				// Review of Order ctor:
				// Order(double _price, long _quantity, PricingSide _side);
				Order bid_order(bid_price, bid_quantity, _bidpricingSide);
				// push back the Order object to the vector
				bidOrder.push_back(bid_order);

				// offerOrder
				// translate the price 
				offer_price = price_translate(data[offerpivot++]);
				offer_quantity = stol(data[offerpivot++]); //convert string to long
				Order offer_order(offer_price, offer_quantity, _offerpricingSide);
				// push back the Order object to the vector
				offerOrder.push_back(offer_order);
			}
			// Initialize the Bond object based on the product type
			Bond &bond = bond_map[product_type];
			// Review of OrderBook ctor:
			// OrderBook(const T &_product, const vector<Order> &_bidStack, const vector<Order> &_offerStack);
			OrderBook<Bond> bond_order_book(bond, bidOrder, offerOrder);
			bond_service->OnMessage(bond_order_book);
		}

		cout << "Finish Reading..." << endl << endl;
	}

	// Initialize the BondMarketDataConnector object as a pointer
	static BondMarketDataConnector* Add_example()
	{
		static BondMarketDataConnector example;
		return &example;
	}

private:
	// define the bond_service
	BondMarketDataService *bond_service;

	// ctor : initialize the bond_service as the BondMarketDataService as object pointer
	BondMarketDataConnector()
	{
		bond_service = BondMarketDataService::Add_example();
	}
};

#endif
