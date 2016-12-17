#pragma once
/**
 * Bondriskservice.hpp
 * Define 
 * @Create by Xinlu Xiao
 */

#ifndef BONDRISKSERVICE_HPP
#define BONDRISKSERVICE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "globalfunctions.hpp"
#include "positionservice.hpp"
#include "riskservice.hpp"
#include "tradeFileGenerator.hpp"
#include "BondHistoricalDataService.hpp"
#include "soa.hpp"

using namespace std;

class BondRiskService : public Service<string, PV01 <Bond> >
{
public:
	// Get data on our service given a key
	//virtual PV01<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PV01<Bond> &data) override {};

	// Add new position
	void AddPosition(Position<Bond> &bondposition)
	{
		cout << "You are now adding the position...loading..." << endl;
		/* Review of product type: 
		string product_type[] = { 
		"912828U40", // 2Y
		"912828U32", // 3Y
		"912828U65", // 5Y
		"912828U57", // 7Y
		"912828U24", // 10Y
		"912828U40" };// 30Y
		*/
		int n = myRiskMap.size();
		if (n == 0)
		{
			myRiskMap["912828U40"] = 0.0185;
			myRiskMap["912828U32"] = 0.01034;
			myRiskMap["912828U65"] = 0.0176;
			myRiskMap["912828U57"] = 0.02215;
			myRiskMap["912828U24"] = 0.0202;
			myRiskMap["912828U40"] = 0.0275;
		}
		double pv01_risk = myRiskMap[bondposition.GetProduct().GetProductId()];
		long pv01_amount = bondposition.GetAggregatePosition();
		double pv01 = pv01_amount*pv01_risk;
		_products.push_back(bondposition.GetProduct());
		PV01<Bond> pv01_instance(_products, pv01, pv01_amount);
		BondHistoricalDataService::Add_example()->Persist_Risk(pv01_instance);
	}

	// Get the bucketed risk for the bucket sector
	const PV01<Bond>& GetBucketedRisk(const BucketedSector<Bond> &sector) const {};

	// Add instance
	static BondRiskService* Add_example()
	{
		static BondRiskService example;
		return &example;
	}
private:
	map<string, double> myRiskMap;
	vector<Bond> _products;
	BondRiskService() {};
};


#endif
