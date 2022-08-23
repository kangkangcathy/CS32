#include "PersonProfile.h"
#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

//You may define a destructor for PersonProfile if you need one.
string PersonProfile::GetName() const
{
      return name;
}
//The GetName method returns the member’s name.
string PersonProfile::GetEmail() const
{
      return email;
}
//The GetEmail method returns the member’s email address.
void PersonProfile::AddAttValPair(const AttValPair &attval)
{
      string insert = attval.attribute + "-" + attval.value;
      if (tree.search(insert) != nullptr)
      {
            return;
      }
      else
      {
            duplicate.push_back(insert);
            tree.insert(insert, attval.value);
            numpairs++;
      }
}
int PersonProfile::GetNumAttValPairs() const
{
      return numpairs;
}
bool PersonProfile::GetAttVal(int attribute_num, AttValPair &attval) const
{
      if (attribute_num < 0 || attribute_num > GetNumAttValPairs())
      {
            return false;
      }
      else
      {
            attval.attribute = duplicate[attribute_num].substr(0, duplicate[attribute_num].find('-'));
            attval.value = duplicate[attribute_num].substr(duplicate[attribute_num].find('-')+1);
            return true;
      }
}
