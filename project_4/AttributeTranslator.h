#ifndef _ATTRIBUTETRANSLATOR_H_
#define _ATTRIBUTETRANSLATOR_H_
#include <vector>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class AttributeTranslator
{
public:
      AttributeTranslator();
      ~AttributeTranslator();
      bool Load(std::string filename);
      vector<AttValPair> FindCompatibleAttValPairs(const AttValPair &source) const;

private:
    vector<std::string> *sourceVec;
      RadixTree<std::vector<AttValPair> *> *tree;
};

#endif //_ATTRIBUTETRANSLATOR_H_
