
#ifndef MEMBERDATABASE_H
#define MEMBERDATABASE_H
#include <vector>
#include <list>
#include <string>
#include "provided.h"
#include "PersonProfile.h"

class MemberDatabase
{
public:
      MemberDatabase();
      ~MemberDatabase();
      bool LoadDatabase(string filename);
      vector<string> FindMatchingMembers(const AttValPair &input) const;
      const PersonProfile *GetMemberByEmail(string email) const;

private:
      RadixTree<vector<string> *> *pairemail;
      RadixTree<PersonProfile *> *emapro;
    vector<string> *pair;
      vector<string> *emailVec;
     
};
#endif
