#pragma once
/**
 * Bondriskservice.hpp
 * Define BondRiskService class
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
	// override the virtual function
	//virtual PV01<Bond>& GetData(string key) override {};

	// override the virtual function
	virtual void OnMessage(PV01<Bond> &data) override {};

	// Add new position
	void AddPosition(Position<Bond> &bondposition)
	{
		cout << "You are now adding the position...loading..." << endl;
		int n = myRiskMap.size();
		// Initialize the "myRiskMap" 
		if (n == 0)
		{
			myRiskMap["912828U40"] = 0.0185;
			myRiskMap["912828U32"] = 0.01034;
			myRiskMap["912828U65"] = 0.0176;
			myRiskMap["912828U57"] = 0.02215;
			myRiskMap["912828U24"] = 0.0202;
			myRiskMap["912828U40"] = 0.0275;
		}
		// get the pv01 risk based on the productID it retrieve
		double pv01_risk = myRiskMap[bondposition.GetProduct().GetProductId()];
		// get the position it holds
		long pv01_amount = bondposition.GetAggregatePosition();
		// get the total pv01 risk 
		double pv01 = pv01_amount*pv01_risk;
		_products.push_back(bondposition.GetProduct());
		// Review of PV01 ctor:
		// PV01(const vector<T> &_products, double _pv01, long _quantity);
		PV01<Bond> pv01_instance(_products, pv01, pv01_amount);
		// Initialize a BondHistoricalDataService object pointer and use risk connector to publish the data
		BondHistoricalDataService::Add_example()->Persist_Risk(pv01_instance);
	}

	// Get the bucketed risk for the bucket sector
	const PV01<Bond>& GetBucketedRisk(const BucketedSector<Bond> &sector) const {};

	// Initialize the BondRiskService object as a pointer
	static BondRiskService* Add_example()
	{
		static BondRiskService example;
		return &example;
	}
private:
	// attributes
	map<string, double> myRiskMap;
	vector<Bond> _products;

	// ctor
	BondRiskService() {};
};


#endif
