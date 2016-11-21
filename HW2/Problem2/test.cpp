/**
* test program 
*/

#include "products.hpp"
#include "productservices.hpp"
#include "soa.hpp"
#include <string>

using namespace std;

int main()
{
        /*Test the future class*/
        //Create a commodity future product
	date maturityDate(2026, Nov, 16);
	string commodity = "65002";
	Future commodityFuture(commodity, COMMODITIES, NOTTHATTYPE, CME, X, 0.01, 1000, 0.06, 100, maturityDate);
        
        //Create a future product service
	FutureProductService *futureProductService = new FutureProductService();

        //Add the commodity future to the FutureProductService and retrieve it from the service
	futureProductService->Add(commodityFuture);
	Future future = futureProductService->GetData(commodity);
	cout << "Future: " << future.GetProductId() << "==>" << future << endl;
        
        return 0;
}

