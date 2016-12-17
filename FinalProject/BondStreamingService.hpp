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
	// override the virtual function
	//virtual PriceStream<Bond>& GetData(string key) override {};

	// override the virtual function
	virtual void OnMessage(PriceStream<Bond> &data) override {};

	// Initialize a BondHistoricalDataService object pointer and use connector to publish a price 
	void PublishPrice(PriceStream<Bond> &priceStream)
	{
		BondHistoricalDataService::Add_example()-> Persist_Streaming(priceStream);
	}

	// Initialize the BondStreamingService object as a pointer
	static BondStreamingService* Add_example()
	{
		static BondStreamingService example;
		return &example;
	}

private:
	// ctor
	BondStreamingService() {};
};

#endif

