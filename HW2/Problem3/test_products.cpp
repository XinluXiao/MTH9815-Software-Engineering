/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"
#include "soa.hpp"

using namespace std;

int main()
{
  // Create the 10Y treasury note
  date maturityDate(2026, Nov, 16);
  string cusip = "912828M56";
  Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

  // Create the 2Y treasury note
  date maturityDate2(2018, Nov, 5);
  string cusip2 = "912828TW0";
  Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

  // Create a BondProductService
  BondProductService *bondProductService = new BondProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond);
  Bond bond = bondProductService->GetData(cusip);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 2Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond2);
  bond = bondProductService->GetData(cusip2);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;
  cout<<endl;

  // Test the "GetBonds" function
  string cTicker = "T";
  vector<Bond> result = bondProductService->GetBonds(cTicker);
  cout<<"The bonds with specified ticker are as follows: "<<endl;
  for(vector<Bond>::iterator it = result.begin();it!= result.end();++it)
  {
    cout<<it->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;  

  // Create the Spot 10Y Outright Swap
  date effectiveDate(2016, Nov, 16);
  date terminationDate(2026, Nov, 16);
  string outright10Y = "Spot-Outright-10Y";
  IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

  // Create the IMM 2Y Outright Swap
  date effectiveDate2(2016, Dec, 20);
  date terminationDate2(2018, Dec, 20);
  string imm2Y = "IMM-Outright-2Y";
  IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

  // Create a IRSwapProductService
  IRSwapProductService *swapProductService = new IRSwapProductService();

  // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(outright10YSwap);
  IRSwap swap = swapProductService->GetData(outright10Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  swap = swapProductService->GetData(imm2Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;
  cout<<endl;

  // Test the "GetSwaps(DayCountConvention _fixedLegDayCountConvention)" function
  vector<IRSwap> result2 = swapProductService->GetSwaps(THIRTY_THREE_SIXTY);
  cout<<"The swaps with specified day count convention are as follows: "<<endl;
  for(vector<IRSwap>::iterator it2 = result2.begin();it2!= result2.end();++it2)
  {
    cout<<it2->GetProductId()<<" ";
  }
  cout<<endl;   
  cout<<endl;

  // Test the "GetSwaps(PaymentFrequency _fixedLegPaymentFrequency)" function
  vector<IRSwap> result3 = swapProductService->GetSwaps(SEMI_ANNUAL);
  cout<<"The swaps with specified fixed leg payment frequency are as follows: "<<endl;
  for(vector<IRSwap>::iterator it3 = result3.begin();it3!= result3.end();++it3)
  {
    cout<<it3->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;

  // Test the "GetSwaps(FloatingIndex _floatingIndex)" function
  vector<IRSwap> result4 = swapProductService->GetSwaps(LIBOR);
  cout<<"The swaps with specified floaring index are as follows: "<<endl;
  for(vector<IRSwap>::iterator it4 = result4.begin();it4!= result4.end();++it4)
  {
    cout<<it4->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;

  // Test the "GetSwapsGreaterThan(int _termYears)" function
  int gYear = 4;
  vector<IRSwap> result5 = swapProductService->GetSwapsGreaterThan(gYear);
  cout<<"The swaps that are greater than the specified years are as follows: "<<endl;
  for(vector<IRSwap>::iterator it5 = result5.begin();it5!= result5.end();++it5)
  {
    cout<<it5->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;  

  // Test the "GetSwapsLessThan(int _termYears)" function
  int lYear = 5;
  vector<IRSwap> result6 = swapProductService->GetSwapsLessThan(lYear);
  cout<<"The swaps that are less than the specified years are as follows: "<<endl;
  for(vector<IRSwap>::iterator it6 = result6.begin();it6!= result6.end();++it6)
  {
    cout<<it6->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;

  // Test the "GetSwaps(SwapType _swapType)" function
  vector<IRSwap> result7 = swapProductService->GetSwaps(IMM);
  cout<<"The swaps with specified swap type are as follows: "<<endl;
  for(vector<IRSwap>::iterator it7 = result7.begin();it7!= result7.end();++it7)
  {
    cout<<it7->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;

  // Test the "GetSwaps(SwapLegType _swapLegType)" function
  vector<IRSwap> result8 = swapProductService->GetSwaps(OUTRIGHT);
  cout<<"The swaps with specified swap leg type are as follows: "<<endl;
  for(vector<IRSwap>::iterator it8 = result8.begin();it8!= result8.end();++it8)
  {
    cout<<it8->GetProductId()<<" ";
  }
  cout<<endl;
  cout<<endl;

  return 0;
}
