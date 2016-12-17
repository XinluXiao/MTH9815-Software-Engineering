#pragma once
/**
 * Bondtradebookingservice.hpp
 * Derive BondtradeserviceListener, Bondtradeservice, Bondtradeconnector from base class
 * @Create by Xinlu Xiao
 */

#ifndef BONDTRADEBOOKINGSERVICE_HPP
#define BONDTRADEBOOKINGSERVICE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "tradebookingservice.hpp"
#include "Bondpositionservice.hpp"
#include "positionservice.hpp"
#include "products.hpp"
#include "globalfunctions.hpp"
#include "soa.hpp"

using namespace std;

class BondtradeserviceListener : public ServiceListener<Trade<Bond>>
{
public:
	
	// Listener callback to process an add event to the Service
	void ProcessAdd(Trade<Bond>& tradedata) override
	{
		string product_type = tradedata.GetProduct().GetProductId();
		//int quantity = (tradedata.GetSide() == BUY ? tradedata.GetQuantity() : -tradedata.GetQuantity());
		long quantity = 0;
		if (tradedata.GetSide() == BUY)
		{
			quantity = tradedata.GetQuantity();
		}
		else
		{
			quantity = -tradedata.GetQuantity();
		}
		bond_position_map[product_type].position_sum(tradedata.GetBook(), quantity);
		bond_service->OnMessage(bond_position_map[product_type]);
	}

	// Listener callback to process a remove event to the Service
	void ProcessRemove(Trade<Bond> &data) override {};

	// Listener callback to process an update event to the Service
	void ProcessUpdate(Trade<Bond> &data) override {};

	
	static BondtradeserviceListener* Add_example() 
	{
		static BondtradeserviceListener example;
		return &example;
	}

private:
	BondtradeserviceListener()
	{
		bond_service = BondPositionService::Add_example();
	};
	BondPositionService * bond_service;
};


class Bondtradeservice : public Service<string, Trade<Bond>>
{
public:
	// Get data on our service given a key
	//Trade<Bond>& GetData(string key) override {};

	// Process add the book data
	void booktrade(Trade<Bond> &tradedata)
	{
		for each (auto _bond_listener in bond_listeners)
		{
			_bond_listener->ProcessAdd(tradedata);
		}
	}

	// The callback that a Connector should invoke for any new or updated data
	void OnMessage(Trade<Bond> &tradedata) override
	{
		booktrade(tradedata);
	}

	static Bondtradeservice* Add_example()
	{
		static Bondtradeservice example;
		return &example;
	}

private:
	Bondtradeservice()
	{
		AddListener(*(BondtradeserviceListener::Add_example()));
	}
};


class Bondtradeconnector : public Connector<Trade<Bond>>
{
public:
	// Publish data to the Connector
	void Publish(Trade<Bond> &data) override {};

	void Readtradedata()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading trade data" << endl;
		ifstream myfile("trade.txt");
		string product_type,
			tradeId,
			book,
			quantity,
			side;
		string row;
		double bond_price;
		getline(myfile, row);
		while (getline(myfile, row))
		{
			vector<string> data = readbyline(row);
			tie(product_type, tradeId, book, quantity, side)
				= make_tuple(data[0], data[1], data[2], data[3], data[4]);
			Bond& bond = bond_map[product_type];
			Side side_result;
			if (side == "BUY")  side_result = BUY;
			else side_result = SELL;
			Trade<Bond> bond_trade(bond, tradeId, book, stol(quantity), side_result);
			bond_service->OnMessage(bond_trade);
		}
		cout << "Finish Reading..." << endl << endl;
	}

	static Bondtradeconnector* Add_example()
	{
		static Bondtradeconnector example;
		return &example;
	}

private:
	Bondtradeservice *bond_service;
	Bondtradeconnector()
	{
		bond_service = Bondtradeservice::Add_example();
	}
};


#endif
