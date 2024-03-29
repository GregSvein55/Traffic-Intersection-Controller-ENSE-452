/**
   Project: Implementation of a Queue in C++.
   Programmer: Karim Naqvi
   Course: enel452
   Modified by: Greg Sveinbjornson
   Description: Assignement 4 for ENSE 452 testcode,
   I implemented a test for my overloaded insert function 
   called testInsert.

*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#include "queue.h"

/**
   Compare the given queue to the given array of data elements.  Return
   true if they are all equal.
 */
bool testQueueEquality( Queue & q, std::vector<Data> const & array)
{
    if (q.size() != array.size())
	return false;

    for (unsigned i = 0; i < q.size(); ++i)
    {
        Data d(0,0);
	q.remove(&d);
	if ( !d.equals(array[i]) )
	    return false;
	q.insert(d);
    }
    return true;
}

/**
 * @brief MY TEST CODE
 * 
 * @return Test 

   Test the insert into positions
 */

bool testInsert(){
    Queue q;
    q.insert(Data(1,2));
    q.insert(Data(3,4));
    q.insert(Data(5,6));
    q.insert(Data(-2,-3), 1);
    q.insert(Data(-4,-5), 3);
    q.print();
    // should produce 0:(1,2) 1:(-2,-3) 2:(3,4) 3:(-4,-5) 4:(5,6)
    std::vector<Data> array;
    array.push_back(Data(1,2));
    array.push_back(Data(-2,-3));
    array.push_back(Data(3,4));
    array.push_back(Data(-4,-5));
    array.push_back(Data(5,6));
    return testQueueEquality(q, array);

}

int main()
{
    using namespace std;

    cout << "Testing queue.\n";
    Queue q1;

    q1.insert(Data(1,1));
    q1.insert(Data(3,3));
    q1.insert(Data(5,5));

    q1.print();

    vector<Data> dataVec;
    dataVec.push_back(Data(1,1));
    dataVec.push_back(Data(3,3));
    dataVec.push_back(Data(5,5));

    assert(testQueueEquality(q1, dataVec));

    Data d44(4, 4);
    bool found = q1.search(d44);
    assert(found == false);


    q1.insert(d44);  // now is (1,1),(3,3),(5,5),(4,4)
    found = q1.search(d44);
    assert(found == true);

    // now queue is(1,1),(3,3),(5,5),(4,4) and 
    // dataVec has (1,1),(3,3),(5,5).  Not equal
    assert(testQueueEquality(q1, dataVec) == false);

    Data temp;
    q1.remove(&temp);  // now q1 is (3,3),(5,5),(4,4)

    Data temp2(1,1);
    assert(temp.equals(temp2));  // (1,1) == (1,1)

    Data temp3(6,6);
    found = q1.search(temp3);
    assert(found == false);

    assert(testInsert());//TESTING MY CODE HERE
    
}
