#pragma once
/**
 * Bondpositionservice.hpp
 * Define the BondpositionserviceListener, BondPositionService class
 * @Create by Xinlu Xiao
 */
#ifndef BONDPOSITIONSERVICE_HPP
#define BONDPOSITIONSERVICE_HPP

#include <iostream>
#include <string>
#include <map>
#include "globalfunctions.hpp"
#include "positionservice.hpp"
#include "Bondriskservice.hpp"
#include "soa.hpp"

using namespace std;

class BondpositionserviceListener : public ServiceListener<Position<Bond>>
{
public:
	// Add data to the RiskService
	virtual void ProcessAdd(Position<Bond> &data) override
	{
		bond_service->AddPosition(data);
	}

	// override the virtual function
	virtual void ProcessRemove(Position<Bond> &data) override {};

	// override the virtual function
	virtual void ProcessUpdate(Position<Bond> &data) override {};

	// Initialize the BondpositionserviceListener object as a pointer
	static BondpositionserviceListener* Add_example()
	{
		static BondpositionserviceListener example;
		return &example;
	}

private:
	// BondRiskService object pointer
	BondRiskService *bond_service = nullptr;

	// ctor : initialzie bond_service as object pointer of BondRiskService
	BondpositionserviceListener()
	{
		bond_service = BondRiskService::Add_example();
	}	
};

class BondPositionService : public Service<string, Position<Bond>>
{
public:
	// override the virtual function
	//virtual Position<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Position<Bond> &data) override
	{
		for(auto listener_instance :  bond_listeners)
		{
			listener_instance->ProcessAdd(data);
		}
	}

	// Initialize the BondPositionService object as a pointer
	static BondPositionService* Add_example()
	{
		static BondPositionService example;
		return &example;
	}

private:
	// ctor : Add listener
	BondPositionService()
	{
		AddListener(*(BondpositionserviceListener::Add_example()));
	}

};

#endif
