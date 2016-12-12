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
	// Get data on our service given a key
	virtual OrderBook<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond> &data) override
	{
		for each(auto _listener in bond_listeners)
		{
			_listener->ProcessAdd(data);
		}
	}

	static BondMarketDataService* Add_example()
	{
		static BondMarketDataService example;
		return &example;
	}
private:
	BondMarketDataService()
	{
		// BondAlgoExecutionService should register a ServiceListener on the BondMarketDataService
		AddListener(BondAlgoExecutionListener::Add_example());
		AddListener(BondHistoricalDataListerner::Add_example());
	}
};

class BondMarketDataConnector : public Connector<OrderBook<Bond>>
{
public:
	// Publish data to the Connector
	virtual void Publish(OrderBook<Bond> &data) override {};

	void ReadMarketData()
	{
		ifstream myfile("marketdata.txt");
		string l;
		PricingSide _bidpricingSide = BID;
		PricingSide _offerpricingSide = OFFER;
		vector<Order> bidOrder;
		vector<Order> offerOrder;
		while (getline(myfile, l))
		{
			string product_type;
			double bid_price;
			double offer_price;
			long bid_quantity;
			long offer_quantity;
			int bidpivot = 1;
			int offerpivot = 1;
			vector<string> data = readbyline(l);
			product_type = data[0];
			for (int i = 0; i < 5; ++i)
			{
				// bidOrder
				bid_price = price_translate(data[bidpivot++]);
				bid_quantity = stol(data[bidpivot++]);
				Order bid_order(bid_price, bid_quantity, _bidpricingSide);
				bidOrder.push_back(bid_order);

				// offerOrder
				offer_price = price_translate(data[offerpivot++]);
				offer_quantity = stol(data[offerpivot++]);
				Order offer_order(offer_price, offer_quantity, _offerpricingSide);
				offerOrder.push_back(offer_order);
			}
			Bond &bond = bond_map[product_type];
			OrderBook<Bond> bond_order_book(bond, bidOrder, offerOrder);
			bond_service->OnMessage(bond_order_book);
		}
	}

	// Add instance
	static BondMarketDataConnector* Add_example()
	{
		static BondMarketDataConnector example;
		return &example;
	}

private:
	BondMarketDataService *bond_service = nullptr;
	// ctor
	BondMarketDataConnector()
	{
		bond_service = BondMarketDataService::Add_example();
	}
};

#endif
