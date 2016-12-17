#pragma once
/**
 * BondExecutionService.hpp
 * Define BondExecutionService class
 * @Create by Xinlu Xiao
 */

#ifndef BONDEXECUTIONSERVICE_HPP
#define BONDEXECUTIONSERVICE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "executionservice.hpp"
#include "globalfunctions.hpp"
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"

using namespace std;

class BondExecutionService : public Service<string, ExecutionOrder<Bond>>
{
public:
	// Override virtual function
	//virtual ExecutionOrder<Bond>& GetData(string key) override {};

	// Override virtual function
	virtual void OnMessage(ExecutionOrder<Bond> &data) override {};

	// Execute an order on a market
	void ExecuteOrder(const ExecutionOrder<Bond>& order, Market market)
	{
		cout << "order executing..." << endl;

		// get the product ID
		string product_type = order.GetProduct().GetProductId();

		// initalize a BondHistoricalDataService object pointer
		bond_service = BondHistoricalDataService::Add_example();
		string s = product_type + order.GetOrderId();

		// publish data through execution connector
		bond_service->Persist_Execution(s);
	}

	// Initialize the BondHistoricalDataListener object as a pointer
	static BondExecutionService *Add_example()
	{
		static BondExecutionService example;
		return &example;
	};

private:
	// BondHistoricalDataService object pointer
	BondHistoricalDataService *bond_service;

	// ctor
	BondExecutionService() {};
};


#endif
