#pragma once
/**
 * BondAlgoExecutionService.hpp
 * Define BondAlgoExecutionService and BondAlgoExecutionListener class
 * @Create by Xinlu Xiao
 */

#ifndef BONDALGOEXECUTIONSERVICE_HPP
#define BONDALGOEXECUTIONSERVICE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "soa.hpp"
#include "products.hpp"
#include "globalfunctions.hpp"
#include "executionservice.hpp"
#include "BondExecutionService.hpp"

using namespace std;

class BondAlgoExecutionService : public Service<string, OrderBook<Bond>>
{
public:
	// Get data on our service given a key
	//virtual OrderBook<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond> &data) override
	{
		string product_type = data.GetProduct().GetProductId();
		Bond bond = data.GetProduct();
		string order_Id;
		double bid_price;
		double offer_price;
		double bidvisibleQuantity;
		double offervisibleQuantity;
		OrderType order_type = FOK;
		Market market_type = CME;
		// OrderId accumulate
		static int orderId = 1;
		order_Id = to_string(orderId++);
		// isOdd accumulate
		static int isOdd = 1;
		isOdd++;
		if (isOdd % 2 == 0)
		{
			const Order &bidOrder = data.GetBidStack()[0];
			bid_price = bidOrder.GetPrice();
			bidvisibleQuantity = bidOrder.GetQuantity();
			ExecutionOrder<Bond> finalOrder(bond, BID, order_Id, order_type, bid_price, bidvisibleQuantity, 0.0, " ", false);
			bond_service->ExecuteOrder(finalOrder, market_type);
		}
		else
		{
			const Order &offerOrder = data.GetOfferStack()[0];
			offer_price = offerOrder.GetPrice();
			offervisibleQuantity = offerOrder.GetQuantity();
			ExecutionOrder<Bond> finalOrder(bond, OFFER, order_Id, order_type, offer_price, offervisibleQuantity, 0.0, " ", false);
			bond_service->ExecuteOrder(finalOrder, market_type);
		}
	}

	// Add instance
	static BondAlgoExecutionService* Add_example()
	{
		static BondAlgoExecutionService example;
		return &example;
	}

private:
	BondExecutionService *bond_service = nullptr;
	BondAlgoExecutionService()
	{
		bond_service = BondExecutionService::Add_example();
	}
};

class BondAlgoExecutionListener : public ServiceListener<OrderBook<Bond>>
{
public:
	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(OrderBook<Bond> &data) override {};

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(OrderBook<Bond> &data) override {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(OrderBook<Bond> &data) override
	{
		bond_service->OnMessage(data);
	}

	// Add example
	static BondAlgoExecutionListener* Add_example()
	{
		static BondAlgoExecutionListener example;
		return &example;
	}

private:
	BondAlgoExecutionListener()
	{
		bond_service = BondAlgoExecutionService::Add_example();
	}

	BondAlgoExecutionService *bond_service;
};

#endif
