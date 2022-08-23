#include <iostream>
#include <cassert>
#include "Map.h"
using namespace std;

int main()
{
      Map a;
      assert(a.size() == 0);            //a is empty
      assert(!a.contains("a"));         //a won't contain anything
      assert(a.empty());                //a is empty
      assert(a.insertOrUpdate("a", 1)); //insert a,1 into a
      assert(!a.empty());               //now a is not empty
      assert(!a.insert("a", 2));        // a has already contains a,1
      assert(a.insert("b", 2));         //insert b,2 into a
      assert(a.contains("b"));          //a now contains b
      assert(a.insert("c", 4));         //insert c,4 into a
      assert(a.update("c", 3));         //update c with 3 in a
      assert(a.insert("d", 4));         //insert d,4 into a
      assert(!a.contains("e"));         // a does not contain e
      assert(a.contains("c"));          //a contains c
      assert(a.size() == 4);            //a's size is 4
      ValueType val;
      assert(!a.get("f", val)); // a cannot get f
      assert(a.get("c", val));  //a can get c with 3
      assert(val == 3);         //c is corresponding to 3
      assert(!a.get("g", val)); // a does not contain g
      assert(val == 3);         //val doesn't change;
      KeyType key;
      assert(!a.get(4, key, val));  // a only contains 4 elements
      assert(val == 3);             //val doesn't change
      assert(!a.get(-1, key, val)); //get cannot access to negative number of elements
      assert(a.get(0, key, val));
      assert(key == "a" && val == 1); //get the a,1
      assert(a.get(1, key, val));
      assert(key == "b" && val == 2); //get the b,2
      assert(a.get(2, key, val));
      assert(key == "c" && val == 3); //get the c,3
      assert(a.get(3, key, val));
      assert(key == "d" && val == 4); //get the d,4
      Map k(a);                       //use copy constuctor to copy k
      assert(!k.get(4, key, val));    // k only contains 4 elements
      assert(val == 4);               //val doesn't change
      assert(!k.get(-1, key, val));   //get cannot access to negative number of elements
      assert(k.get(0, key, val));
      assert(key == "a" && val == 1); //get the a,1
      assert(k.get(1, key, val));
      assert(key == "b" && val == 2); //get the b,2
      assert(k.get(2, key, val));
      assert(key == "c" && val == 3); //get the c,3
      assert(k.get(3, key, val));
      assert(key == "d" && val == 4); //get the d,4
      assert(!k.insert("a", 9));      //a,1 is already in the k
      assert(k.insert("e", 5));       // insert e,5 into k
      assert(k.size() == 5);          //now k has 5 elements;
      a = k;
      assert(a.size() == 5);       //a should have the same number of elements as k
      assert(!a.get(5, key, val)); // get cannot get access to equal number of size of the map
      assert(a.get(1, key, val));
      assert(key == "b" && val == 2); //a should still contains b,2
      assert(a.get("c", val));        // a should be able to get c
      assert(val == 3);               //c,3 is in a
      assert(a.erase("e"));           //erase e from a
      assert(a.size() == 4);          // not only 4 elements in a
      assert(k.size() == 5);          //k should not be modified
      Map i;
      i.insert("a", 10);
      i.insert("b", 20);
      i.insert("c", 30);
      i.insert("d", 40);
      i.insert("e", 50);
      Map j;
      j.insert("f", 60);
      j.insert("g", 70);
      j.insert("h", 80);
      j.insert("a", 30);
      Map q;
      assert(!merge(i, j, q));  //unable to merge because of the different value of a corresponding to
      assert(q.size() == 7);    //now q doesn't contain a
      assert(!q.contains("a")); //q doesn't contains a
      assert(j.erase("a"));
      assert(merge(i, j, q)); //able to merge i and j
      assert(q.size() == 8);  // now every elemtns in i and j is in q
      assert(i.insert("i", 90));
      assert(j.insert("i", 90));
      assert(merge(i, j, q)); //able to merge i and j
      assert(q.size() == 9);  //q contains element from a to i
      assert(q.get(8, key, val));
      assert(key == "i" && val == 90); // the largest element in q should be i,90
      Map result;
      reassign(q, result); // reassign q into result
      assert(q.get("a", val));
      assert(val == 10); // q doesn't changed
      assert(result.get("a", val));
      assert(val != 10); // result has been reassigned
      assert(q.get("b", val));
      assert(val == 20); // q doesn't changed
      assert(result.get("b", val));
      assert(val != 20); // result has been reassigned
      assert(q.get("c", val));
      assert(val == 30); // q doesn't changed
      assert(result.get("c", val));
      assert(val != 30); // result has been reassigned
      assert(q.get("d", val));
      assert(val == 40); // q doesn't changed
      assert(result.get("d", val));
      assert(val != 40); // result has been reassigned
      assert(q.get("e", val));
      assert(val == 50); // q doesn't changed
      assert(result.get("e", val));
      assert(val != 50); // result has been reassigned
      assert(q.get("f", val));
      assert(val == 60); // q doesn't changed
      assert(result.get("f", val));
      assert(val != 60); // result has been reassigned
      assert(q.get("g", val));
      assert(val == 70); // q doesn't changed
      assert(result.get("g", val));
      assert(val != 70); // result has been reassigned
      assert(q.get("h", val));
      assert(val == 80); // q doesn't changed
      assert(result.get("h", val));
      assert(val != 80); // result has been reassigned
      assert(q.get("i", val));
      assert(val == 90); // q doesn't changed
      assert(result.get("i", val));
      assert(val != 90); // result has been reassigned
      cerr << "Passed all tests!!!!" << endl;
}