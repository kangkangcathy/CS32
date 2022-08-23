#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_
#include <string>
#include <vector>
#include <iostream>
using namespace std;

template <typename ValueType>
class RadixTree
{
public:
      RadixTree()
      {
            Root = nullptr;
      }
      //The RadixTree constructor.
      ~RadixTree()
      {
            delete Root;
      }
      //You may define a destructor for RadixTree if you need
      //one to free any dynamically allocated memory used by your object.
      void insert(std::string key, const ValueType &value)  // will this value be pointer or simply valuetype?
      {
            if (key.empty())
            {
                  return;
            }
            ValueType copyvalue = value;
            RadixTreeNode *Root = getRoot();
            Radix_insert(Root, key, copyvalue);
      }

      ValueType *search(std::string key) const
      {
            RadixTreeNode *Root = getRoot();
            RadixTreeNode *node = Radix_Query(Root, key);
            if (node == nullptr)
            {
                  return nullptr;
            }
            else
            {
                  ValueType *result = getVal(node);
                  return result;
            }
      }

private:
      struct RadixTreeNode
      {
            ValueType *m_value;  //should it be a pointer or not
            string word[128];
            bool endOfWord;
            RadixTreeNode *edges[128];

            RadixTreeNode()
            {
                  for (int i = 0; i < 128; i++)
                  {
                        edges[i] = nullptr;
                  }
                  endOfWord = true;
            }
            ~RadixTreeNode()
            {
                  for (int j = 0; j < 128; j++)
                  {
                        delete edges[j];
                  }
            }
      };
      RadixTreeNode *getRoot() const
      {
            return Root;
      }
      ValueType *getVal(RadixTreeNode *node) const  //should it returns a pointer or not
      {
            return node->m_value;
      }
      void Radix_insert(RadixTreeNode *node, string s, ValueType val) // should this val be pointer or simply valuetype
      {
            if (s.empty()) //finish insertion
            {
                  node->endOfWord = true;
                  node->m_value = &val;
                  return;
            }
            else
            {
                int firstLetter = s[0] ;
                if(node == nullptr)
                {
                    RadixTreeNode* newnode = new RadixTreeNode;
                    newnode->word[firstLetter] = s;
                    Root = newnode;
                    Radix_insert(Root, "", val);
                    return;
                }
                  if (node->edges[firstLetter] == nullptr) //then insert s into the edges
                  {
                        node->edges[firstLetter] = new RadixTreeNode;
                        node->word[firstLetter] = s;
                        Radix_insert(node->edges[firstLetter], "", val);
                        return;
                  }
                  string transition = node->word[firstLetter];
                  int matchlen = 0;
                  while (matchlen < min(transition.length(), s.length()) && transition[matchlen] == s[matchlen])
                  {
                        matchlen++;
                  }
                  if (matchlen == transition.length()) //if partial s matches entire transition string
                  {
                        Radix_insert(node->edges[firstLetter], s.substr(matchlen), val);
                  }
                  else if (matchlen == s.length()) //entire s matches partial transition string
                  {
                        RadixTreeNode *newnode = new RadixTreeNode;
                        newnode->edges[transition[matchlen]] = node->edges[firstLetter];
                        newnode->word[transition[matchlen]] = transition.substr(matchlen);
                        node->edges[firstLetter] = newnode;
                        node->word[firstLetter] = s;
                        Radix_insert(node->edges[firstLetter], "", val);
                  }
                  else //paritial s matches partial transition string
                  {
                        RadixTreeNode *newnode = new RadixTreeNode;
                        newnode->edges[transition[matchlen]] = node->edges[firstLetter];
                        newnode->word[transition[matchlen]] = transition.substr(matchlen);
                        node->edges[firstLetter] = newnode;
                        node->word[matchlen] = s.substr(0, matchlen);
                        Radix_insert(node->edges[firstLetter], s.substr(matchlen), val);
                  }
            }
      }
      RadixTreeNode *Radix_Query(RadixTreeNode *node, string s) const
      {
            if (s.empty())
            {
                  return (node->endOfWord) ? node : nullptr;
            }
            int firstLetter = s[0];
          if(node == nullptr)
          {
              return nullptr;
          }
            //s doesn't match any prefix
            if (node->edges[firstLetter] == nullptr)
            {
                  return nullptr;
            }
            string transition = node->word[firstLetter];
            int minlen = min(transition.length(), s.length());
            if (transition.substr(0, minlen) != s.substr(0, minlen)) //mismatch
            {
                  return nullptr;
            }
            if (transition.length() == minlen) //partial s matches entire transition
            {
                  return Radix_Query(node->edges[firstLetter], s.substr(transition.length()));
            }
            else //entire s matches partial transition
            {
                  return nullptr;
            }
      }
      void Radix_Prefix_helper(RadixTreeNode *node, string s, vector<string> &v)
      {
            if (node->endOfWord)
            {
                  v.push_back(s);
            }
            for (int i = 0; i < 128; i++)
            {
                  if (node->edges[i] != nullptr)
                  {
                        Radix_Prefix_helper(node->edges[i], s + node->word[i], v);
                  }
            }
      }
      void Radix_Prefix(RadixTreeNode *node, string input, string s, vector<string> &v)
      {
            if (s.empty())
            {
                  Radix_Prefix_helper(node, input, v);
                  return;
            }
            int firstLetter = s[0];
            if (node->edges[firstLetter] == nullptr) //not prefix of any word
            {
                  return;
            }
            string transition = node->word[firstLetter];
            int len = min(transition.length(), s.length());
            if (transition.substr(0, len) != s.substr(0, len)) //prefix not found
            {
                  return;
            }
            if (len == transition.length())
            {
                  Radix_Prefix(node->edges[firstLetter], input, s.substr(len), v);
            }
            else
            {
                  Radix_Prefix(node->edges[firstLetter], input + transition.substr(len), "", v);
            }
      }
      RadixTreeNode *Root = new RadixTreeNode;
};

#endif
