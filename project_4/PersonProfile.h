#ifndef _PERSONPROFILE_H_
#define _PERSONPROFILE_H_
#include <string>
#include <iostream>
#include "RadixTree.h"
#include "provided.h"
#include <vector>
using namespace std;

class PersonProfile
{
public:
      PersonProfile(string Na, string Em)
      {
            name = Na;
            email = Em;
            numpairs = 0;
      }
      
      ~PersonProfile(){}
    
      string GetName() const;
      //The GetName method returns the member’s name.
      string GetEmail() const;
      //The GetEmail method returns the member’s email address.
      void AddAttValPair(const AttValPair &attval);
      int GetNumAttValPairs() const;
      bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    RadixTree<string> tree;
    vector<string> duplicate;
    vector<AttValPair*> ap;
string name;
string email;
int numpairs;

};

#endif //_PERSONPROFILE_H_
