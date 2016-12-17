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
	// Publish two-way prices
	void PublishPrice(PriceStream<Bond>& priceStream)
	{
		BondHistoricalDataService::Add_example()->Persist_Streaming(priceStream);
	}

	// Get data on our service given a key
	virtual PriceStream<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PriceStream<Bond> &data) override {};

	// Add example
	static BondAlgoStreamingService* Add_example()
	{
		static BondAlgoStreamingService example;
		return &example;
	}

private:
	BondPricingService* bond_service;
	BondAlgoStreamingService()
	{
		bond_service = BondPricingService::Add_example();
	}
};

#endif
