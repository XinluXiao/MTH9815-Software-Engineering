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
	// Get data on our service given a key
	//virtual ExecutionOrder<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(ExecutionOrder<Bond> &data) override {};

	// Execute an order on a market
	void ExecuteOrder(const ExecutionOrder<Bond>& order, Market market)
	{
		cout << "order executing..." << endl;
		string product_type = order.GetProduct().GetProductId();
		bond_service = BondHistoricalDataService::Add_example();
		string s = product_type + order.GetOrderId();
		bond_service->Persist_Execution(s);
	}

	// Add example
	static BondExecutionService *Add_example()
	{
		static BondExecutionService example;
		return &example;
	};

private:
	BondHistoricalDataService *bond_service;
	BondExecutionService() {};
};


#endif
