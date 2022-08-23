#include "Map.h"
#include <iostream>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

Map::Map()
{
      head = new Node; //create a new node
      head->nex = head;  //set a circular linked list
      head->pre = head;  //set a circular linked list
      num = 0;  //set the number of element as 0
}
bool Map::empty() const
{
      if (num == 0)  // if there is no element
      {
            return true;
      }
      else
      { 
            return false;
      }
}
int Map::size() const
{
      return num;  //return size of the circular linked list
}
bool Map::insert(const KeyType &key, const ValueType &value)
{
      if (num == 0)  //check if the map is empty
      {
            Node *first = new Node;
            first->nodekey = key;  //link the first new node with the nead
            first->nodevalue = value;
            head->nex = first;
            head->pre = first;
            first->pre = head;
            first->nex = head;
            num++; //refresh the number of element in the map
            return true;
      }
      for (Node *j = head->nex; j != head; j = j->nex)  //check if the node’s key has already been existed in the map
      {
            if (j->nodekey == key)
            {
                  return false;
            }
      }
      for (Node *i = head->nex; i != head; i = i->nex) //check throughout the map elements
      {
            if (i->nodekey < key && i->nex == head) //if the new key value is larger than all the other element’s key (which means the next node will be the head)
            {
                  Node *last = new Node;  //linked the last element with this new node and link this new node with head (which means the new node’s previous is the last node and the new node’s next is the head)
                  last->nodekey = key;
                  last->nodevalue = value;
                  last->pre = i;
                  last->nex = head;
                  i->nex = last;
                  head->pre = last;
                  num++; //refresh the number of elements in the circular linked list
                  return true;
            }
            else if (i->nodekey > key)  //else if the new node’s key is larger than the map’s node
            {
                  Node *temp = new Node;  //link the new node with the map’s node (which means the new node’s previous node is the map’s previous node and the new node’s next node is the map’s next node)
                  temp->nodekey = key;
                  temp->nodevalue = value;

                  i->pre->nex = temp;  
                  temp->pre = i->pre;
                  temp->nex = i;
                  i->pre = temp;
                  num++;  //refresh the number of elements in the circular linked list
                  return true;
            }
      }
      return true;
}
bool Map::update(const KeyType &key, const ValueType &value)
{
      for (Node *j = head->nex; j != head; j = j->nex)  //for all the node (except the head node in the map)
      {
            if (j->nodekey == key)  //if the Key of the node is equal to key
            {
                  j->nodevalue = value;  //update the Value of the node with value
                  return true;
            }
      }
      return false;  //if no Key of the node in the map is equal to key
}
bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
      if (update(key, value))  //if successfully updated
      {
            return true;
      }
      else
      {
            insert(key, value);
            return true;
      }
}
bool Map::erase(const KeyType &key)
{
      for (Node *j = head->nex; j != head; j = j->nex)  //for all the node(except the head node in the map)
      {
            if (j->nodekey == key)  //if the Key of the node is equal to key
            {
                  j->pre->nex = j->nex;  //let the node’s previous node’s next node link to the node’s next node
                  j->nex->pre = j->pre;
                  delete j; // delete the node
                  num--;  //refresh the number of node in the map
                  return true;
            }
      }
      return false;  //if there is no Key of node in the map equals to key
}
bool Map::contains(const KeyType &key) const
{
      for (Node *j = head->nex; j != head; j = j->nex)  //for all the node(except the head node in the map)
      {
            if (j->nodekey == key)  //if the Key of the node is equal to key
            {
                  return true;
            }
      }
      return false;  //if there is no Key of node in the map equals to key
}
bool Map::get(const KeyType &key, ValueType &value) const
{
      for (Node *j = head->nex; j != head; j = j->nex)  //for all the node(except the head node in the map)
      {
            if (j->nodekey == key)  //if the Key of the node is equal to key
            {
                  value = j->nodevalue;  //set the value equal to the node’s value
                  return true;
            }
      }
      return false;  //if there is no Key of node in the map equals to key
}
bool Map::get(int i, KeyType &key, ValueType &value) const
{
      if (i < 0 || i >= num)  //if i is smaller than 0 or is greater and equal to map’s size
      {
            return false;
      }
      else
      {
            int count = 0;
            for (Node *j = head->nex; j != head; j = j->nex)  //start to count node from the beginning of map
            {
                  if (count == i)  //if count is equal to i
                  {
                        key = j->nodekey;  //set the key equal to the node’s key at this point
                        value = j->nodevalue;  //set the value equal to the node’s value at this point
                        return true;
                  }
                  count++;  //else, continue to count 
            }
      }
      return true;
}
void Map::swap(Map &other)
{
      int tempnum = num;
      num = other.size();  //let the map’s size equal the other’s size
      other.num = tempnum;

      Node *temphead = head;  //set the map’s head node to the other’s head node
      head = other.head;
      other.head = temphead;
}
Map::~Map()
{
      for (int i = num - 1; i >= 0; i--)
      {
            KeyType tempkey;
            ValueType tempvalue;
            get(i, tempkey, tempvalue);
            erase(tempkey);  //delete the tempkey
      }
      delete head;
}
Map &Map::operator=(const Map &other)
{
      if (this != &other)  //if this is not the other
      {
            for (int i = num - 1; i >= 0; i--)
            {
                  KeyType tempkey;
                  ValueType tempvalue;
                  get(i, tempkey, tempvalue);
                  erase(tempkey);  //erase all the elements in map
            }
            num = 0;
            for (int j = other.num - 1; j >= 0; j--)
            {
                  KeyType otherkey;
                  ValueType othervalue;
                  other.get(j, otherkey, othervalue);
                  insert(otherkey, othervalue);  //insert the element into the new map
            }
      }
      return *this;
}
Map::Map(const Map &map)
{
      num = 0;
      head = new Node;
      head->nex = head;
      head->pre = head;  //constructor a new map
      for (int j = map.num - 1; j >= 0; j--)
      {
            KeyType mapkey;
            ValueType mapvalue;
            map.get(j, mapkey, mapvalue);
            insert(mapkey, mapvalue);  //insert every element
      }
}

bool merge(const Map &m1, const Map &m2, Map &result)
{
      for (int j = result.size() - 1; j >= 0; j--)  //for all node in result except the head node
      {
            KeyType tempkey;
            ValueType tempvalue;
            result.get(j, tempkey, tempvalue);
            result.erase(tempkey);  //erase every node
      }
      bool answer = true;
      for (int i = m1.size() - 1; i >= 0; i--)  //for every node in m1
      {
            KeyType tempkey1;
            ValueType tempvalue1;
            m1.get(i, tempkey1, tempvalue1);
            if (m2.contains(tempkey1))  //if m2 also contains the node’s key
            {
                  ValueType tempvalue2;
                  m2.get(tempkey1, tempvalue2);
                  if (tempvalue2 == tempvalue1)  //if the m2’s node’ value is equal to that of m1’s 
                  {
                        result.insert(tempkey1, tempvalue1);  //insert that node into result
                  }
                  else
                  {
                        answer = false;  //keep looping and set bool to false
                  }
            }
            else
            {
                  result.insert(tempkey1, tempvalue1);  //insert that node into result
            }
      }
      for (int k = m2.size() - 1; k >= 0; k--)  //for every node in m2
      {
            KeyType tempkey3;
            ValueType tempvalue3;
            m2.get(k, tempkey3, tempvalue3);
            if (!m1.contains(tempkey3))  //if m1 doesn’t contain the node’s key
            {
                  result.insert(tempkey3, tempvalue3);  //insert that node into result
            }
      }
      return answer;
}
void reassign(const Map &m, Map &result)
{
      for (int j = result.size() - 1; j >= 0; j--)  //for all node in result except the head node
      {
            KeyType tempkey;
            ValueType tempvalue;
            result.get(j, tempkey, tempvalue);
            result.erase(tempkey);  //erase every node
      }
      if(m.size() == 1)  //if there is only one element in m (except the head node)
      {
            KeyType tempkey1;
            ValueType tempvalue1;
            m.get(0, tempkey1, tempvalue1);
            result.insert(tempkey1, tempvalue1);  //copy the node and insert it into result
      }
      else
      {
            for(int i = m.size()-1; i >=0; i --)  //loop through all node in m
            {
                  KeyType tempkeylast;
                  ValueType tempvaluelast;
                  m.get(i,tempkeylast, tempvaluelast);
                  if(i == 0)  //if the node is the first node
                  {
                        KeyType tempkeyend;
                        ValueType tempvalueend;
                        m.get(m.size()-1,tempkeyend,tempvalueend);
                        result.insert(tempkeylast,tempvalueend);  //copy the end node’s key and value into that first node
                  }
                  else
                  {
                        KeyType tempkeybefore;
                        ValueType tempvaluebefore;
                        m.get(i-1, tempkeybefore,tempvaluebefore);
                        result.insert(tempkeylast,tempvaluebefore);  //copy the previous node’s key and value into this node
                  }
            }
      }
}