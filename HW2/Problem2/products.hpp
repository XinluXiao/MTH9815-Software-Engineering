#pragma once
#ifndef PRODUCTS_HPP
#define PRODUCTS_HPP

#include <iostream>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;

//Product Types
enum ProductType { IRSWAP, BOND, FUTURE };

/**
* Definition of a base Product class
*/
class Product
{

public:
	// Product ctor
	Product(string _productId, ProductType _productType);

	// Retrurn the product identifier
	string GetProductId() const;

	// Return the Product Type for this Product
	ProductType GetProductType() const;

private:
	string productId; // product id variab;e
	ProductType productType; // product type variable
};

//Future Type
enum FutureType { STOCK_INDICES, COMMODITIES, CURRENCIES, INTEREST_RATES };

//Interest Rate Future Type
enum RateFutureType { NOTTHATTYPE, EURODOLLARF, BONDF };

//Exchange Type
enum ExchangeType { CBOT, CME, CMX, NYBOT, KCBT, MGE, MATIE, SFE, NYM, LIFFE, EUREX, ICE };

//Delivery Months
enum DeliveryMonths { F, G, H, J, K, M, N, Q, U, V, X, Z };

/**
*Modeling of a Future Product 
*/
class Future : public Product
{
public:
	//Future ctor
	Future(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove, float _intRate, float _spotPrice, date _maturityDate);
	Future();

	//Return the future id type
	FutureType GetFutureType() const;

	//Return the interest rate future type
	RateFutureType GetRateFutureType() const;

	//Return the exchange type
	ExchangeType GetExchangeType() const;

	//Return the delivery month
	DeliveryMonths GetDeliveryMonths() const;

	//Return the min tick
	float GetMinTick() const;

	//Return the unit move
	float GetUnitMove() const;

	//Return the interest rate of the future
	float GetInterestRate() const;

	//Return the spot price of the future
	float GetSpotPrice() const;

	//Return the maturity date of the future
	date GetMaturityDate() const;

	//overload the << operator to print out the future
	friend ostream& operator<<(ostream &output, const Future &future);

private:
	string productId;   //product id variable
	FutureType futureType;  //future id type variable
	RateFutureType rateFutureType;  //interest rate future type variable
	ExchangeType exchangeType;  //future exchange type
	DeliveryMonths deliveryMonths;  //future delivery months
	float minTick;  //future min tick variable
	float unitMove;  //future unit move variable
	float intRate;  //interest rate variable
	float spotPrice;  //spot price variable
	date maturityDate;  //maturity date variable

	//return a string representation for the future type
	string ToString(FutureType futureType) const;

	//return a string representation for the interest rate future type
	string ToString(RateFutureType rateFutureType) const;

	//return a string representation for the exchange type
	string ToString(ExchangeType exchangeType) const;

	//return a string representation for the delivery months
	string ToString(DeliveryMonths deliveryMonths) const;
};

Product::Product(string _productId, ProductType _productType)
{
	productId = _productId;
	productType = _productType;
}

string Product::GetProductId() const
{
	return productId;
}

ProductType Product::GetProductType() const
{
	return productType;
}

Future::Future(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove, float _intRate, float _spotPrice, date _maturityDate) : Product(_productId, FUTURE)
{
	futureType = _futureType;
	rateFutureType = _rateFutureType;
	exchangeType = _exchangeType;
	deliveryMonths = _deliveryMonths;
	minTick = _minTick;
	unitMove = _unitMove;
	intRate = _intRate;
	spotPrice = _spotPrice;
	maturityDate = _maturityDate;
}
Future::Future() : Product(0, FUTURE)
{
}

FutureType Future::GetFutureType() const
{
	return futureType;
}

RateFutureType Future::GetRateFutureType() const
{
	return rateFutureType;
}

ExchangeType Future::GetExchangeType() const
{
	return exchangeType;
}

DeliveryMonths Future::GetDeliveryMonths() const
{
	return deliveryMonths;
}


float Future::GetMinTick() const
{
	return minTick;
}

float Future::GetUnitMove() const
{
	return unitMove;
}

float Future::GetInterestRate() const
{
	return intRate;
}

float Future::GetSpotPrice() const
{
	return spotPrice;
}

date Future::GetMaturityDate() const
{
	return maturityDate;
}

ostream& operator<<(ostream &output, const Future &future)
{
	output << future.ToString(future.GetFutureType())<<" "<< future.ToString(future.GetExchangeType())<<" "<<future.ToString(future.GetDeliveryMonths())<<" "<<future.GetMinTick()<<" "<<future.GetUnitMove()<< " " << future.GetInterestRate() << " " << future.GetMaturityDate();
	return output;
}

string Future::ToString(FutureType futureType) const
{
	switch(futureType) {
	case STOCK_INDICES: return "stock indices";
	case COMMODITIES: return "commodities";
	case CURRENCIES: return "currencies";
	case INTEREST_RATES: return "interest rates";
	default: return "";
	}
}

string Future::ToString(RateFutureType rateFutureType) const
{
	switch (rateFutureType) {
	case NOTTHATTYPE: return "not a interest rate type future";
	case EURODOLLARF: return "EuroDollar";
	case BONDF: return "Bond";
	default: return " ";
	}
}

string Future::ToString(ExchangeType exchangeType) const
{
	switch (exchangeType) {
	case CBOT: return "CBOT";
	case CME: return "CME";
	case CMX: return "CMX";
	case NYBOT: return "NYBOT";
	case KCBT: return "KCBT";
	case MGE: return "MGE";
	case MATIE: return "MATIE";
	case SFE: return "SFE";
	case NYM: return "NYM";
	case LIFFE: return "LIFFE";
	case EUREX: return "EUREX";
	case ICE: return "ICE";
	default: return " ";
	}
}

string Future::ToString(DeliveryMonths deliveryMonths) const
{
	switch (deliveryMonths) {
	case F: return "January";
	case G: return "February";
	case H: return "March";
	case J: return "April";
	case K: return "May";
	case M: return "June";
	case N: return "July";
	case Q: return "August";
	case U: return "September";
	case V: return "October";
	case X: return "November";
	case Z: return "December";
	default: return " ";
	}
}

//Bond Futures Type
enum BondFutureType { UT_BOND, THIRTY_BOND, TEN_BOND, FIVE_BOND, TWO_BOND };


class BondFuture : public Future
{
public:
	//BondFuture ctor
	BondFuture(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove,float _intRate, float _spotPrice, date _maturityDate, BondFutureType _bondFutureType, float _nominal, float _referenceYield);
	BondFuture();

        //Return the Bond Future Type
	BondFutureType GetBondFutureType() const;

	//Return the nominal
	float GetNominal() const;

	//Return the reference yield
	float GetReferenceYield() const;

	//Overload the << operator to print out the bond future
	friend ostream& operator<<(ostream &output, const BondFuture &bondFuture);

private:
	string productId;   //product id variable
	FutureType futureType;  //future id type variable
	RateFutureType rateFutureType;  //interest rate future type variable
	ExchangeType exchangeType;  //future exchange type
	DeliveryMonths deliveryMonths;  //future delivery months
	float minTick;  //future min tick variable
	float unitMove;  //future unit move variable
	float intRate;  //interest rate variable
	float spotPrice;  //spot price variable
	date maturityDate;  //maturity date variable
	BondFutureType bondFutureType;  //bond future type variable
	float nominal;  //nominal variable
	float referenceYield;  //reference yield variable

	//return a string representation for the future type
	string ToString(FutureType futureType) const;

	//return a string representation for the interest rate future type
	string ToString(RateFutureType rateFutureType) const;

	//return a string representation for the exchange type
	string ToString(ExchangeType exchangeType) const;

	//return a string representation for the delivery months
	string ToString(DeliveryMonths deliveryMonths) const;

	//return a string representation for the bond future type
	string ToString(BondFutureType bondFutureType) const;
};

BondFuture::BondFuture(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove, float _intRate, float _spotPrice, date _maturityDate, BondFutureType _bondFutureType, float _nominal, float _referenceYield) : Future(_productId, INTEREST_RATES, BONDF, _exchangeType, _deliveryMonths, _minTick, _unitMove, _intRate, _spotPrice, _maturityDate)
{
	bondFutureType = _bondFutureType;
	nominal = _nominal;
	referenceYield = _referenceYield;
}

BondFuture::BondFuture() : Future()
{
}

BondFutureType BondFuture::GetBondFutureType() const
{
	return bondFutureType;
}

float BondFuture::GetNominal() const
{
	return nominal;
}

float BondFuture::GetReferenceYield() const
{
	return referenceYield;
}


ostream& operator<<(ostream &output, const BondFuture &bondFuture)
{
	output << bondFuture.ToString(bondFuture.GetExchangeType()) << " " << bondFuture.ToString(bondFuture.GetDeliveryMonths()) << " " << bondFuture.GetMinTick() << " " << bondFuture.GetUnitMove() << " " << bondFuture.ToString(bondFuture.GetBondFutureType()) << " " << bondFuture.GetReferenceYield() << " " << bondFuture.GetNominal() << endl;
	return output;
}

string BondFuture::ToString(FutureType futureType) const
{
	switch (futureType) {
	case STOCK_INDICES: return "stock indices";
	case COMMODITIES: return "commodities";
	case CURRENCIES: return "currencies";
	case INTEREST_RATES: return "interest rates";
	default: return "";
	}
}

string BondFuture::ToString(RateFutureType rateFutureType) const
{
	switch (rateFutureType) {
	case NOTTHATTYPE: return "not a interest rate type future";
	case EURODOLLARF: return "EuroDollar";
	case BONDF: return "Bond";
	default: return " ";
	}
}

string BondFuture::ToString(ExchangeType exchangeType) const
{
	switch (exchangeType) {
	case CBOT: return "CBOT";
	case CME: return "CME";
	case CMX: return "CMX";
	case NYBOT: return "NYBOT";
	case KCBT: return "KCBT";
	case MGE: return "MGE";
	case MATIE: return "MATIE";
	case SFE: return "SFE";
	case NYM: return "NYM";
	case LIFFE: return "LIFFE";
	case EUREX: return "EUREX";
	case ICE: return "ICE";
	default: return " ";
	}
}

string BondFuture::ToString(DeliveryMonths deliveryMonths) const
{
	switch (deliveryMonths) {
	case F: return "January";
	case G: return "February";
	case H: return "March";
	case J: return "April";
	case K: return "May";
	case M: return "June";
	case N: return "July";
	case Q: return "August";
	case U: return "September";
	case V: return "October";
	case X: return "November";
	case Z: return "December";
	default: return " ";
	}
}

string BondFuture::ToString(BondFutureType bondFutureType) const
{
	switch (bondFutureType) {
	case UT_BOND: return "Ultra T Bond";
	case THIRTY_BOND: return "30 Year Bond";
	case TEN_BOND: return "10 Year Bond";
	case FIVE_BOND: return "5 Year Bond";
	case TWO_BOND: return "2 Year Bond";
	default: return " ";
	}
}

/**
*Modeling a Eurodollar Future Product
*/
class EurodollarFuture : public Future
{
public:
       //EurodollarFuture ctor
       EurodollarFuture(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove, float _intRate, float _spotPrice, date _maturityDate, date _cashSettlement, float _settlePrice);
       EurodollarFuture();
       
       //Return the cash settlement date
       date GetCashSettlement() const;

       //Return the settle price
       float GetSettlePrice() const;

       //Overload the << operator to print out the eurodollar future
       friend ostream& operator<<(ostream &output, const EurodollarFuture &eurodollarFuture);

private:
        string productId;   //product id variable
        FutureType futureType;  //future id type variable
        RateFutureType rateFutureType;  //interest rate future type variable
        ExchangeType exchangeType;  //future exchange type
        DeliveryMonths deliveryMonths;  //future delivery months
        float minTick;  //future min tick variable
        float unitMove;  //future unit move variable
        float intRate;  //interest rate variable
        float spotPrice;  //spot price variable
        date maturityDate;  //maturity date variable
        date cashSettlement;  //cash settlement date variable
        float settlePrice;   //settlement price variable

        //return a string representation for the future type
        string ToString(FutureType futureType) const;

        //return a string representation for the interest rate future type
        string ToString(RateFutureType rateFutureType) const;

        //return a string representation for the exchange type
        string ToString(ExchangeType exchangeType) const;

        //return a string representation for the delivery months
        string ToString(DeliveryMonths deliveryMonths) const;
};
 
EurodollarFuture::EurodollarFuture(string _productId, FutureType _futureType, RateFutureType _rateFutureType, ExchangeType _exchangeType, DeliveryMonths _deliveryMonths, float _minTick, float _unitMove, float _intRate, float _spotPrice, date _maturityDate, date _cashSettlement, float _settlePrice) : Future(_productId, INTEREST_RATES, EURODOLLARF, _exchangeType, _deliveryMonths, _minTick, _unitMove, _intRate, _spotPrice, _maturityDate)
{
        cashSettlement = _cashSettlement;
	settlePrice = _settlePrice;
}

EurodollarFuture::EurodollarFuture() : Future()
{
}

date EurodollarFuture:: GetCashSettlement() const
{
	return cashSettlement;
}

float EurodollarFuture:: GetSettlePrice() const
{
	return settlePrice;
}

ostream& operator<<(ostream &output, const EurodollarFuture &eurodollarFuture)
{
	output<<eurodollarFuture.ToString(eurodollarFuture.GetExchangeType())<<" "<<eurodollarFuture.GetDeliveryMonths()<<" " <<eurodollarFuture.GetMinTick()<<" " <<eurodollarFuture.GetUnitMove()<<" "<<eurodollarFuture.GetCashSettlement()<<" "<<eurodollarFuture.GetSettlePrice()<<endl;
}

string EurodollarFuture::ToString(FutureType futureType) const
{
        switch (futureType) {
        case STOCK_INDICES: return "stock indices";
        case COMMODITIES: return "commodities";
        case CURRENCIES: return "currencies";
        case INTEREST_RATES: return "interest rates";
        default: return "";
        }
}

string EurodollarFuture::ToString(RateFutureType rateFutureType) const
{
        switch (rateFutureType) {
        case NOTTHATTYPE: return "not a interest rate type future";
        case EURODOLLARF: return "EuroDollar";
        case BONDF: return "Bond";
        default: return " ";
        }
}

string EurodollarFuture::ToString(ExchangeType exchangeType) const
{
        switch (exchangeType) {
        case CBOT: return "CBOT";
        case CME: return "CME";
        case CMX: return "CMX";
        case NYBOT: return "NYBOT";
        case KCBT: return "KCBT";
        case MGE: return "MGE";
        case MATIE: return "MATIE";
        case SFE: return "SFE";
        case NYM: return "NYM";
        case LIFFE: return "LIFFE";
        case EUREX: return "EUREX";
        case ICE: return "ICE";
        default: return " ";
        }
}

string EurodollarFuture::ToString(DeliveryMonths deliveryMonths) const
{
        switch (deliveryMonths) {
        case F: return "January";
        case G: return "February";
        case H: return "March";
        case J: return "April";
        case K: return "May";
        case M: return "June";
        case N: return "July";
        case Q: return "August";
        case U: return "September";
        case V: return "October";
        case X: return "November";
        case Z: return "December";
        default: return " ";
        }
}

#endif
