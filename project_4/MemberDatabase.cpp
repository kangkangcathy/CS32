#include "MemberDatabase.h"
#include "PersonProfile.h"
#include <algorithm>
#include <fstream>
#include <string>

MemberDatabase::MemberDatabase()
{
    pairemail = new RadixTree<std::vector<string> *>;
    emailVec = new vector<string> ;
    pair = new vector<string>;
    emapro = new RadixTree<PersonProfile *>;
    
}

MemberDatabase::~MemberDatabase()
{
    for (vector<string>::iterator v1 = emailVec->begin(); v1 != emailVec->end(); v1++)
      {
            PersonProfile **p = emapro->search(*v1);
            if (p != nullptr)
            {
                  delete (*p);
            }
            else{
                continue;
            }
      }
      for (vector<std::string>::iterator v2 = pair->begin(); v2 != pair->end(); v2++)
      {
            std::vector<std::string> **searchpair = pairemail->search(*v2);
            if (searchpair != nullptr)
            {
                delete (*searchpair);
            }
      }
      delete pairemail;
    delete emailVec;
    delete pair;
      delete emapro;
      
}

bool MemberDatabase::LoadDatabase(string filename)
{
      string line;
      string name;
      string email;
    string number;
      string attribute;
      string space;
      string value;
      string valpair;
      int numPair = 0;
      ifstream file(filename);
      if (!file)
      {
            return false;
      }
      if (file.is_open())
      {
            while (file.good())
            {
                getline(file, name);
                  getline(file, email);
                  
                  if (emapro->search(email) == nullptr)
                  {
                        emailVec->push_back(email);
                        PersonProfile *p = new PersonProfile(name, email);
                      getline(file, number);
                      numPair = stoi(number);
                        for (int i = 0; i < numPair; i++)
                        {
                              getline(file, attribute, ',');
                              getline(file, value);
                              p->AddAttValPair(AttValPair(attribute, value));
                              vector<std::string> **searchemail = pairemail->search(attribute + value);
                              if(searchemail == nullptr)
                              {
                                    pairemail->insert(attribute + value, new std::vector<std::string>);
                                    
                                    pair->push_back(attribute + value);
                              }
                            searchemail = pairemail->search(attribute + value);
                              (*searchemail)->push_back(email);
                        }
                        getline(file, space);
                        emapro->insert(email, p);
                  }
                  else
                  {
                        return false;
                  }
            }
      }
    return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair &input) const
{
      vector<string> **p = pairemail->search(input.attribute + input.value);
      if (p != nullptr)
      {
            return **p;
      }
      return vector<string>();
}

const PersonProfile *MemberDatabase::GetMemberByEmail(std::string email) const
{
      PersonProfile **p = emapro->search(email);
      if (p == nullptr)
      {
            return nullptr;
      }
      else
      {
            return *p;
      }
}
