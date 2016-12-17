/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 * @Create by Xinlu Xiao
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"
#include "tradebookingservice.hpp"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:
	Position() {};

  // ctor for a position
	Position(const T &_product);

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(string &book);

  // Get the aggregate position
  long GetAggregatePosition();

  // Initialize the position
  void position_begin();

  // Add a new position
  void position_sum(string bookNum, int quantity);

private:
  T product;
  map<string,long> positions;

};

/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:

  // Add a trade to the service
  virtual void AddTrade(const Trade<T> &trade) = 0;

private:
	PositionService();

};

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

template<typename T>
long Position<T>::GetPosition(string &book)
{
  return positions[book];
}

template<typename T>
long Position<T>::GetAggregatePosition()
{
	long aggregate_position = 0;
	for (int i = 0; i < 3; ++i)
	{
		string s = "TRSY" + to_string(i + 1);
		aggregate_position += positions.at(s);
	}
	return aggregate_position;
}

template<typename T>
void Position<T>::position_begin()
{
	for (int i = 0; i < 3; ++i)
	{
		positions["TRSY" + to_string(i + 1)] = 1000000;
	}
}

template<typename T>
void Position<T>::position_sum(string bookNum, int quantity)
{
	//if (positions.find(bookNum) != position.end())
	assert(positions.find(bookNum) != positions.end());
	
		positions[bookNum] += quantity;
	
}

#endif
 