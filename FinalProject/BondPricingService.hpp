#pragma once
/**
 * BondPricingService.hpp
 * Define BondPricingService and BondPricingConnector class
 * @Create by Xinlu Xiao
 */

#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "globalfunctions.hpp"
#include "soa.hpp"
#include "pricingservice.hpp"
#include "streamingservice.hpp"
#include "BondStreamingService.hpp"

using namespace std;

class BondPricingService : public Service<string, Price<Bond>>
{
public:
	// Get data on our service given a key
	//virtual Price<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Price<Bond> &data) override
	{
		double price_spread = data.GetBidOfferSpread();
		double mid_price = data.GetMid();
		double offerPrice = mid_price + price_spread / 2;
		double bidPrice = mid_price - price_spread / 2;
		PriceStreamOrder Offer(offerPrice, 0, 0, PricingSide::OFFER);
		PriceStreamOrder Bid(bidPrice, 0, 0, PricingSide::BID);
		PriceStream<Bond> price_stream(data.GetProduct(), Bid, Offer);
		BondStreamingService::Add_example()->PublishPrice(price_stream);
		// BondStreamingService need to be defined
	}

	// Add instance
	static BondPricingService* Add_example()
	{
		static BondPricingService example;
		return &example;
	}

private:
	BondPricingService() {};
};


class BondPricingConnector : public Connector<Price<Bond>>
{
public:
	// Publish data to the Connector
	virtual void Publish(Price<Bond> &data) override {};

	void ReadPriceData()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading pricing data" << endl;
		ifstream myfile("price.txt");
		string product_type, mid_price, bid_offer_spread, l;
		getline(myfile, l);
		while (getline(myfile, l))
		{
			vector<string> data = readbyline(l);
			tie(product_type, mid_price, bid_offer_spread) = make_tuple(data[0], data[1], data[2]);
			double mid = price_translate(mid_price);
			double spread = price_translate(bid_offer_spread);
			Bond& bond = bond_map[product_type];
			Price<Bond> bond_price_instance(bond, mid, spread);
			bond_service->OnMessage(bond_price_instance);
		}
		cout << "Finish Reading..." << endl << endl;
	}


	static BondPricingConnector* Add_example()
	{
		static BondPricingConnector example;
		return &example;
	}

private:
	BondPricingService *bond_service;
	// ctor
	BondPricingConnector()
	{
		bond_service = BondPricingService::Add_example();
	}
	
};

#endif
