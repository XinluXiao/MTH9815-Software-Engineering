#pragma once
#ifndef PRODUCTSERVICES_HPP
#define PRODUCTSERVICES_HPP

#include <iostream>
#include <map>
#include "products.hpp"
#include "soa.hpp"

class FutureProductService : public Service<string, Future>
{
public:
	//FutureProductService ctor
	FutureProductService();

	//Return the future data for a particular future product id
	Future& GetData(string productId);

	//Add a future to the service
	void Add(Future &future);

private:
	map<string, Future> futureMap; //cache of future products
};

FutureProductService::FutureProductService()
{
	futureMap = map<string, Future>();
}

Future& FutureProductService::GetData(string productId)
{
	return futureMap[productId];
}

void FutureProductService::Add(Future &future)
{
	futureMap.insert(pair<string, Future>(future.GetProductId(), future));
}
#endif