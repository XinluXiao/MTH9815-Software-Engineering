//Create by Team2: XInlu Xiao and Zhaoyue Wei
//C++ Homework2
//11/20/2016

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

using namespace std;
using namespace boost::interprocess;

int main(int argc)
{
 if(argc == 1)
 {
  //Create the first program
  shared_memory_object shm(create_only, "SharedInt", read_write);
  //Set the size
  //The size should be bigger than the size of an integer
  shm.truncate(500);
  //Map the whole shared memory in this process
  mapped_region region(shm, read_write);
  int *i1 = static_cast<int*>(region.get_address());
  *i1 = 100;
  //See the output of the first program
  cout<<"The result of the first program is: "<<*i1<<endl;
  //Call the second program
  main(0);
  //Remove the shared memory object
  shared_memory_object::remove("SharedInt");
  return 0;
 }
 else
 {
  //Create the second program
  shared_memory_object(open_only, "SharedInt", read_only);
  //Map the whole shared memory in this process
  mapped_region region2(shm, read_only);
  int *i2 = static_cast<int*>(region2.get_address());
  cout<<"The result of the second program is: "<<*i2<<endl;
  return 0;
 }
}
