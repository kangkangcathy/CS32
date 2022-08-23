#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <map>
#include <set>
#include <unordered_map>

bool compareEmailCount(const EmailCount &lhs, const EmailCount &rhs);

MatchMaker::MatchMaker(const MemberDatabase &mdb, const AttributeTranslator &at)
{
      mbdtb = &mdb;
      atbtlr = &at;
}

MatchMaker::~MatchMaker()
{
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
      const PersonProfile *cpp = mbdtb->GetMemberByEmail(email);
      vector<AttValPair> avpv;
      for (int i = 0; i < cpp->GetNumAttValPairs(); i++)
      { 
            AttValPair avp;
            cpp->GetAttVal(i, avp);
            vector<AttValPair> find = atbtlr->FindCompatibleAttValPairs(avp);
            for (vector<AttValPair>::iterator v1 = find.begin(); v1 != find.end(); v1++)
            {
                  avpv.push_back(*v1);
            }
      }
    set<string> candidates;
      for (vector<AttValPair>::iterator v2 = avpv.begin(); v2 != avpv.end(); v2++)
      {
            vector<string> emailsmatched = mbdtb->FindMatchingMembers(*v2);
          for(int i=0; i<emailsmatched.size(); ++i)
          {
              candidates.insert(emailsmatched[i]);
          }
      }
      vector<EmailCount> ec;
    for(string name: candidates)
    {
        const PersonProfile* him = mbdtb->GetMemberByEmail(name);
        AttValPair temp;
        int count=0;
        for(int i=0; i<him->GetNumAttValPairs(); ++i)
        {
            him->GetAttVal(i, temp);
            if(find(avpv.begin(), avpv.end(), temp)!=avpv.end())
            {
                count++;
            }
        }
        if(count>=threshold)
        {
            EmailCount em(him->GetEmail(), count);
            ec.push_back(em);
        }
    }
    sort(ec.begin(),ec.end(), [](const EmailCount& e1, const EmailCount& e2){return e1.count == e2.count ? e1.email>e2.email : e1.count>e2.count;});
      return ec;
}
