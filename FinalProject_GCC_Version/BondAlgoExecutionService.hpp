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
	// Override virtual function
	//virtual OrderBook<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond> &data) override
	{
		// get the product type
		string product_type = data.GetProduct().GetProductId();

		// get the Bond object
		Bond bond = data.GetProduct();
		string order_Id;
		double bid_price;
		double offer_price;
		double bidvisibleQuantity;
		double offervisibleQuantity;
		OrderType order_type = FOK;  // FOK as the example
		Market market_type = CME;  // CME as the example

		// static member : OrderId accumulate
		static int orderId = 1;
		order_Id = to_string(orderId++);

		// static member : isOdd accumulate
		static int isOdd = 1;
		isOdd++;
		if (isOdd % 2 == 0)
		{
			// get the bidOrder object from the bidStack
			const Order &bidOrder = data.GetBidStack()[0];
			// get the object price
			bid_price = bidOrder.GetPrice();
			// get the quantity
			bidvisibleQuantity = bidOrder.GetQuantity();
			// Review of Execution ctor:
			// ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, double _visibleQuantity, double _hiddenQuantity, string _parentOrderId, bool _isChildOrder);
			ExecutionOrder<Bond> finalOrder(bond, BID, order_Id, order_type, bid_price, bidvisibleQuantity, 0.0, " ", false);
			bond_service->ExecuteOrder(finalOrder, market_type);
		}
		else
		{
			// get the offerOrder object from the offerStack
			const Order &offerOrder = data.GetOfferStack()[0];
			// get the object price
			offer_price = offerOrder.GetPrice();
			// get the quantity
			offervisibleQuantity = offerOrder.GetQuantity();
			// Review of Execution ctor:
			// ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, double _visibleQuantity, double _hiddenQuantity, string _parentOrderId, bool _isChildOrder);
			ExecutionOrder<Bond> finalOrder(bond, OFFER, order_Id, order_type, offer_price, offervisibleQuantity, 0.0, " ", false);
			bond_service->ExecuteOrder(finalOrder, market_type);
		}
	}

	// Initialize the BondAlgoExecutionService object as a pointer
	static BondAlgoExecutionService* Add_example()
	{
		static BondAlgoExecutionService example;
		return &example;
	}

private:
	// BondExecutionService object pointer
	BondExecutionService *bond_service = nullptr;

	// ctor : initialize bond_service as object pointer of BondExecutionService
	BondAlgoExecutionService()
	{
		bond_service = BondExecutionService::Add_example();
	}
};

class BondAlgoExecutionListener : public ServiceListener<OrderBook<Bond>>
{
public:
	// Override virtual function
	virtual void ProcessAdd(OrderBook<Bond> &data) override {};

	// Override virtual function
	virtual void ProcessRemove(OrderBook<Bond> &data) override {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(OrderBook<Bond> &data) override
	{
		bond_service->OnMessage(data);
	}

	// Initialize the BondAlgoExecutionListener object as a pointer
	static BondAlgoExecutionListener* Add_example()
	{
		static BondAlgoExecutionListener example;
		return &example;
	}

private:
	// BondExecutionService object pointer
	BondAlgoExecutionService *bond_service;

	// ctor : initialize bond_service as object pointer of BondExecutionService
	BondAlgoExecutionListener()
	{
		bond_service = BondAlgoExecutionService::Add_example();
	}

	
};

#endif
