#pragma once
/**
 * BondAlgoStreamingService.hpp
 * Define BondAlgoStreamingService class
 * @Create by Xinlu Xiao
 */

#ifndef BONDALGOSTREAMINGSERVICE_HPP
#define BONDALGOSTREAMINGSERVICE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "soa.hpp"
#include "products.hpp"
#include "streamingservice.hpp"
#include "globalfunctions.hpp"
#include "BondPricingService.hpp"
#include "BondHistoricalDataService.hpp"

using namespace std;

class BondAlgoStreamingService : public Service<string, PriceStream<Bond>>
{
public:
	// Initialize BondHistoricalDataService object pointer and use stream connector to publish data
	void PublishPrice(PriceStream<Bond>& priceStream)
	{
		BondHistoricalDataService::Add_example()->Persist_Streaming(priceStream);
	}

	// Override virtual function
	// virtual PriceStream<Bond>& GetData(string key) override {};

	// Override virtual function
	virtual void OnMessage(PriceStream<Bond> &data) override {};

	// Initialize the BondHistoricalDataListener object as a pointer
	static BondAlgoStreamingService* Add_example()
	{
		static BondAlgoStreamingService example;
		return &example;
	}

private:
	// BondPricingService object pointer
	BondPricingService* bond_service;

	// ctor : initialize bond_service as object pointer of BondPricingService
	BondAlgoStreamingService()
	{
		bond_service = BondPricingService::Add_example();
	}
};

#endif
