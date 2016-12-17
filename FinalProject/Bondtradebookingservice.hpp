#pragma once
/**
 * Bondtradebookingservice.hpp
 * Derive BondtradeserviceListener, Bondtradeservice, Bondtradeconnector class
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
		cout << "In the BondtradeserviceListener" << endl;
		cout << "ProcessAdd tradedata..." << endl;
		// Get the product ID
		string product_type = tradedata.GetProduct().GetProductId();
		// Set the quantity based on the side
		// If BUY, then positive; if SELL, then negative
		long quantity = ((tradedata.GetSide() == BUY) ? tradedata.GetQuantity() : -tradedata.GetQuantity());
		// Sum up the position based on the product type
		bond_position_map[product_type].position_sum(tradedata.GetBook(), quantity);
		bond_service->OnMessage(bond_position_map[product_type]);
		cout << "Finish processing add trade data..." << endl;
	}

	// override the virtual function
	void ProcessRemove(Trade<Bond> &data) override {};

	// override the virtual function
	void ProcessUpdate(Trade<Bond> &data) override {};

	// return the BondtradeserviceListener object as a pointer
	static BondtradeserviceListener* Add_example() 
	{
		static BondtradeserviceListener example;
		return &example;
	}

private:
	// BondPositionService object pointer
	BondPositionService * bond_service;

	// ctor : intialize the bond_service as object pointer of BondPositionService
	BondtradeserviceListener()
	{
		bond_service = BondPositionService::Add_example();
	};
	
};


class Bondtradeservice : public Service<string, Trade<Bond>>
{
public:
	// override the virtual function
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

	// return the Bondtradeservice object as a pointer
	static Bondtradeservice* Add_example()
	{
		static Bondtradeservice example;
		return &example;
	}

private:
	// ctor: add listener to the trade service
	Bondtradeservice()
	{
		AddListener(*(BondtradeserviceListener::Add_example()));
	}
};


class Bondtradeconnector : public Connector<Trade<Bond>>
{
public:
	// override the virtual function
	void Publish(Trade<Bond> &data) override {};

	// Read the trade data from the txt file
	void Readtradedata()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading trade data" << endl;
		ifstream myfile("trade.txt");
		// define the string attributes
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
			// initialize a string vector to store the result from reading the txt
			vector<string> data = readbyline(row);
			// pass the element in the vector to the string attributes
			tie(product_type, tradeId, book, quantity, side)
				= make_tuple(data[0], data[1], data[2], data[3], data[4]);
			// Initialize a Bond object based on the product type
			Bond& bond = bond_map[product_type];
			Side side_result;
			if (side == "BUY")  side_result = BUY;
			else side_result = SELL;
			// Review of Trade ctor:
			// Trade(const T &_product, string _tradeId, string _book, long _quantity, Side _side);
			Trade<Bond> bond_trade(bond, tradeId, book, stol(quantity), side_result);
			bond_service->OnMessage(bond_trade);
		}
		cout << "Finish Reading..." << endl << endl;
	}

	// return the Bondtradeservice object as a pointer
	static Bondtradeconnector* Add_example()
	{
		static Bondtradeconnector example;
		return &example;
	}

private:
	// Bondtradeservice object pointer
	Bondtradeservice *bond_service;

	// ctor: initialzie the bond_service as object pointer of Bondtradeservice
	Bondtradeconnector()
	{
		bond_service = Bondtradeservice::Add_example();
	}
};


#endif
