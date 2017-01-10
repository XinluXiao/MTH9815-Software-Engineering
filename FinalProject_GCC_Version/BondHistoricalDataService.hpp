#pragma once
/**
 * BondHistoricalDataService.hpp
 * Define two parts:
 * (1) Connectors: Risk, Execution, Streaming, Inquiry
 * (2) BondHistoricalDataService and BondHistoricalDataListener class
 * @Create by Xinlu Xiao
 */

#ifndef BONDHISTORICALDATASERVICE_HPP
#define BONDHISTORICALDATASERVICE_HPP

#include <iostream>
#include <fstream>
#include "soa.hpp"
#include "products.hpp"
#include "historicaldataservice.hpp"
#include "globalfunctions.hpp"
#include "riskservice.hpp"
#include "inquiryservice.hpp"
#include "streamingservice.hpp"


using namespace std;

/**************** Part 1 ********************/
/**************** Connectors ****************/

//ios_base::app is to open an output file
class RiskConnector : public Connector<string>
{
public:
	// ctor for RiskConnector
	RiskConnector() {};

	// Publish data into "risk.txt" file
	virtual void Publish(string &data) override
	{
		ofstream myfile("risk.txt", ios_base::app);  
		myfile << data << endl;
	}

	// Initialize the RiskConnector object as a pointer
	static RiskConnector *Add_example()
	{
		static RiskConnector example;
		return &example;
	}
};


class ExecutionConnector : public Connector<string>
{
public:
	// ctor for ExecutionConnector
	ExecutionConnector() {};

	// Publish data into "execution.txt" file
	virtual void Publish(string &data) override
	{
		ofstream myfile("execution.txt", ios_base::app);
		myfile << data << endl;
	}
	
	// Initialize the ExecutionConnector object as a pointer
	static ExecutionConnector *Add_example()
	{
		static ExecutionConnector example;
		return &example;
	}
};


class StreamingConnector : public Connector<string>
{
public:
	// ctor for StreamingConnector
	StreamingConnector() {};

	// Publish data into "execution.txt" file
	virtual void Publish(string &data) override
	{
		ofstream myfile("streaming.txt", ios_base::app);
		myfile << data << endl;
	}

	// Initialize the StreamingConnector object as a pointer
	static StreamingConnector *Add_example()
	{
		static StreamingConnector example;
		return &example;
	}	
};


class InquiryConnector : public Connector<string>
{
public:
	// ctor for InquiryConnector
	InquiryConnector() {};

	// Publish data into "allinquiries.txt" file
	virtual void Publish(string &data) override
	{
		ofstream myfile("allinquiries.txt", ios_base::app);
		myfile << data << endl;
	}

	// Initialize the InquiryConnector object as a pointer
	static InquiryConnector *Add_example()
	{
		static InquiryConnector example;
		return &example;
	}
};

/****************************** Part 2 ***************************/
/********************* BondHistoricalDataService******************/
/********************* BondHistoricalDataListener*****************/

class BondHistoricalDataService : public Service<string, Bond>
{
public:
	// Override virtual function
	//virtual Bond& GetData(string key) override {};
	virtual void OnMessage(Bond &data) override {};

	// Override virtual function
	void PersistData(string persistKey, const Bond& data) {};

	// Override virtual function
	void Persist_Position() {};
	
	// Persist object it receive from the BondRiskService into "risk.txt"
	RiskConnector *riskconnector;
	void Persist_Risk(PV01<Bond> &data)
	{
		cout << "Persisting Risk data" << endl;
		string pv01_data = to_string(data.GetPV01());
		string input = "PV01+" + pv01_data;
		riskconnector->Publish(input);
	}

	// Persist object it receive from the BondExecutionService into "execution.txt"
	ExecutionConnector *executionconnector;
	void Persist_Execution(string data)
	{
		cout << "Persisting Execution data" << endl;
		executionconnector->Publish(data);
	}

	// Persist object it receive from the BondStreamingService into "streaming.txt"
	StreamingConnector *streamingconnector;
	void Persist_Streaming(PriceStream<Bond> &data)
	{
		cout << "Persisting Streaming data" << endl;
		string productId = data.GetProduct().GetProductId();
		string offer_price = to_string(data.GetOfferOrder().GetPrice());
		string bid_price = to_string(data.GetBidOrder().GetPrice());
		string input = "Product Id," + productId + "," +"Bid price is:"+ bid_price + "," +"Offer price is:"+ offer_price + ";";
		streamingconnector->Publish(input);
	}

	// Persist object it receive from the BondInquiryService into "allinquiries.txt"
	InquiryConnector *inquiryconnector;
	void Persist_Inquiry(Inquiry<Bond> &data)
	{
		cout << "Persisting Inquiry data" << endl;
		string productId = data.GetProduct().GetProductId();
		string inquiryId = data.GetInquiryId();
		string price = to_string(data.GetPrice());
		string quantity = to_string(data.GetQuantity());
		string side;
		if (data.GetSide() == Side::BUY)
		{
			side = "BUY";
		}
		else
		{
			side = "SELL";
		}
		string state;
		if (data.GetState() == InquiryState::RECEIVED)
		{
			state = "RECEIVED";
		}
		else
		{
			state = "OTHERS";
		}
		string input = "Product Id: " + productId + "," + "Inquiry Id: " + inquiryId + "," + "Price: " + price + "," + "Quantity: " + quantity + ";";
		inquiryconnector->Publish(input);
	}

	// Initialize the BondHistoricalDataService object as a pointer
	static BondHistoricalDataService *Add_example()
	{
		static BondHistoricalDataService example;
		return &example;
	}

	// ctor for BondHistoricalDataService : initialize 4 object pointer of connectors
	BondHistoricalDataService()
	{
		riskconnector = RiskConnector::Add_example();
		executionconnector = ExecutionConnector::Add_example();
		streamingconnector = StreamingConnector::Add_example();
		inquiryconnector = InquiryConnector::Add_example();
	}
};


class BondHistoricalDataListener : public ServiceListener<OrderBook<Bond>>
{
public:
	// ctor : initialize bond_service as BondHistoricalDataService object pointer
	BondHistoricalDataListener()
	{
		bond_service = BondHistoricalDataService::Add_example();
	}
	
	// Override virtual function
	virtual void ProcessAdd(OrderBook<Bond> &data) override {};

	// Override virtual function
	virtual void ProcessRemove(OrderBook<Bond> &data) override {};

	// Override virtual function
	virtual void ProcessUpdate(OrderBook<Bond> &data) override {};

	// Initialize the BondHistoricalDataListener object as a pointer
	static BondHistoricalDataListener *Add_example()
	{
		static BondHistoricalDataListener example;
		return &example;
	}

private:
	// BondHistoricalDataService object pointer
	BondHistoricalDataService *bond_service;
};

#endif





//BondHistoricalDataListerner
