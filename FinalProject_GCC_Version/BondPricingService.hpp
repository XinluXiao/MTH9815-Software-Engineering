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
	// override the virtual function
	//virtual Price<Bond>& GetData(string key) override {};

	// Review Price<T> ctor:
	// Price(const T &_product, double _mid, double _bidOfferSpread);
	virtual void OnMessage(Price<Bond> &data) override
	{
		// get the bid offer spread
		double price_spread = data.GetBidOfferSpread();
		// get the mid price
		double mid_price = data.GetMid();
		// calculate the bid price and offer price
		double offerPrice = mid_price + price_spread / 2;
		double bidPrice = mid_price - price_spread / 2;

		// Initialize two PriceStreamOrder object
		// Review PriceStreamOrder ctor:
		// PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side);
		PriceStreamOrder Offer(offerPrice, 0, 0, PricingSide::OFFER);
		PriceStreamOrder Bid(bidPrice, 0, 0, PricingSide::BID);

		// Initialize one PriceStream object
		// Review PriceStream ctor:
		// PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder);
		PriceStream<Bond> price_stream(data.GetProduct(), Bid, Offer);

		// Initialize one BondStreamService object pointer and use stream connector to publish data
		BondStreamingService::Add_example()->PublishPrice(price_stream);
	}

	// Initialize the BondPricingService object as a pointer
	static BondPricingService* Add_example()
	{
		static BondPricingService example;
		return &example;
	}

private:
	// ctor
	BondPricingService() {};
};


class BondPricingConnector : public Connector<Price<Bond>>
{
public:
	// override the virtual function
	virtual void Publish(Price<Bond> &data) override {};

	// Read data from price.txt file
	void ReadPriceData()
	{
		cout << "*************Message****************" << endl;
		cout << "You are reading pricing data" << endl;
		ifstream myfile("prices.txt");
		string product_type, mid_price, bid_offer_spread, row;
		getline(myfile, row);
		while (getline(myfile, row))
		{
			// Initialize a vector to store the string it reads from price.txt
			vector<string> data = readbyline(row);

			// Assign elements to the string attributes
			tie(product_type, mid_price, bid_offer_spread) = make_tuple(data[0], data[1], data[2]);
			
			// translate the price 
			double mid = price_translate(mid_price);
			double spread = price_translate(bid_offer_spread);

			// Initialize one Bond object based on the product type
			Bond& bond = bond_map[product_type];

			// Review Price ctor:
			// Price(const T &_product, double _mid, double _bidOfferSpread);
			Price<Bond> bond_price_instance(bond, mid, spread);

			// Publish data
			bond_service->OnMessage(bond_price_instance);
		}
		cout << "Finish Reading..." << endl << endl;
	}

	// Initialize the BondPricingConnector object as a pointer
	static BondPricingConnector* Add_example()
	{
		static BondPricingConnector example;
		return &example;
	}

private:
	// BondPricingService object pointer
	BondPricingService *bond_service;

	// ctor : initialize bond_service as object pointer of BondPricingService
	BondPricingConnector()
	{
		bond_service = BondPricingService::Add_example();
	}
	
};

#endif
