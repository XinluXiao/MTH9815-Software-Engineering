#pragma once
/**
 * BondStreamingService.hpp
 * Define BondStreamingService class
 * @Create by Xinlu Xiao
 */

#ifndef BONDSTREAMINGSERVICE_HPP
#define BONDSTREAMINGSERVICE_HPP

#include <iostream>
#include <fstream>
#include "products.hpp"
#include "soa.hpp"
#include "streamingservice.hpp"
#include "BondHistoricalDataService.hpp"

using namespace std;

class BondStreamingService : public Service<string, PriceStream<Bond>>
{
public:
	// Get data on our service given a key
	//virtual PriceStream<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PriceStream<Bond> &data) override {};

	// Publish two-way prices
	void PublishPrice(PriceStream<Bond> &priceStream)
	{
		BondHistoricalDataService::Add_example()-> Persist_Streaming(priceStream);
	}

	// Add instance
	static BondStreamingService* Add_example()
	{
		static BondStreamingService example;
		return &example;
	}

private:
	BondStreamingService() {};
};

#endif

