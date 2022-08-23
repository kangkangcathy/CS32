#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

AttributeTranslator::AttributeTranslator()
{
    sourceVec = new vector<std::string>;
    tree = new RadixTree<std::vector<AttValPair> *>;
    
}
AttributeTranslator::~AttributeTranslator()
{
    for(vector<string>::iterator s1 = sourceVec->begin(); s1 != sourceVec->end(); s1 ++)
    {
        vector<AttValPair>** get = tree->search(*s1);
        if(get != nullptr)
        {
            delete *get;
        }
    }
    delete tree;
    delete sourceVec;
}
bool AttributeTranslator::Load(std::string filename)
{
      std::ifstream File(filename);
      if (!File)
      {
            return false;
      }
      else
      {
            if (File.is_open())
            {
                  string sourceAtt;
                  string sourceVal;
                  string comAtt;
                  string comVal;
                  while (File.good())
                  {
                        getline(File, sourceAtt, ',');
                        getline(File, sourceVal, ',');
                        getline(File, comAtt, ',');
                        getline(File, comVal);
                        string so = sourceAtt + sourceVal;
                        AttValPair com(comAtt, comVal);
                        vector<AttValPair> **search = tree->search(so);
                        if (search == nullptr)
                        {
                              tree->insert(so, new vector<AttValPair>);
                              sourceVec->push_back(so);
                              search = tree->search(so);
                        }
                        (*search)->push_back(com);
                  }
            }
      }
      return true;
}
vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair &source) const
{
      vector<AttValPair> **com = tree->search(source.attribute + source.value);
      if(com == nullptr)
      {
            return vector<AttValPair>();
      }
      else
      {
            return **com;
      }
}
