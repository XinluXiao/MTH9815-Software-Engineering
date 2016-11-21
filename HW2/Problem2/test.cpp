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
        //Create a Commodity Future Product
	date maturityDate(2026, Nov, 16);
	string commodity = "BO335";
	Future commodityFutureContract(commodity, COMMODITIES, NOTTHATTYPE, CBOT, X, 0.01, 600, 0.06, 99.75, maturityDate);
        
        //Create a Eurodollar Future Product
	date maturityDate2(2018, Oct, 11);
	string eurodollar = "EDM6";
	Future eurodollarFutureContract(eurodollar, INTEREST_RATES, EURODOLLARF, CME, V, 0.005, 2500, 0.06, 98.84, maturityDate2);        
        
	//Create a Bond Future Product
	date maturityDate3(2023, Dec, 29);
	string bond = "CU235";
	Future bondFutureContract(bond, INTEREST_RATES, BONDF, CBOT, Z, 0.015625, 1000, 0.06, 96.78, maturityDate3);

	//Create a future product service
	FutureProductService *futureProductService = new FutureProductService();

        //Add the commodity future to the FutureProductService and retrieve it from the service
	futureProductService->Add(commodityFutureContract);
	Future future = futureProductService->GetData(commodity);
	cout << "Future: " << future.GetProductId() << "==>" << future << endl;
        
	//Add the eurodollar future to the FutureProductService and retrieve it from the service
	futureProductService->Add(eurodollarFutureContract);
	future = futureProductService->GetData(eurodollar);
	cout<< "Future: " << future.GetProductId() << "==>" << future << endl;

        //Add the bond future to the FutureProductService and retrieve it from the service
	futureProductService->Add(bondFutureContract);
	future = futureProductService->GetData(bond);
	cout<< "Future: " << future.GetProductId() << "==>" << future << endl;
	
        return 0;
}

