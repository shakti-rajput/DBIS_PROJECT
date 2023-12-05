#include "modifiedAlgorithm.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void makeHashFunction_pair_CallByReference_ModifiedInt(
    list<pair<int, int>> &tables, int index,
    unordered_map<int, list<pair<int, int>>> &hashTable) {

  const clock_t begin_time = clock();

  if (index) {
    for (auto x : tables) {
      hashTable[x.second].push_back(x);
    }
  } // if index == 1 then custom key is second element
  else {
    for (auto x : tables) {
      hashTable[x.first].push_back(x);
    }
  }
  std::cout << "Hash Table making time --> "
            << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}

void leftCycleLeftJoin_pair_CallByReference_ModifiedInt(
    list<pair<int, int>> leftTable, int leftIndex,
    list<pair<int, int>> &rightTable, int rightIndex,
    unordered_map<int, list<pair<int, int>>> &hashTemp) {
  const clock_t begin_time = clock();
  unordered_map<int, list<pair<int, int>>> hashTable;
  makeHashFunction_pair_CallByReference_ModifiedInt(leftTable, leftIndex,
                                                    hashTable);

  int tempKey;
  if (rightIndex) {
    for (auto x : rightTable) {
      tempKey = x.second;
      if (hashTable.find(tempKey) != hashTable.end()) {
        hashTemp[tempKey] = hashTable[tempKey];
        hashTable.erase(tempKey);
      }
    }
  } else {
    for (auto x : rightTable) {
      tempKey = x.first;
      if (hashTable.find(tempKey) != hashTable.end()) {
        hashTemp[tempKey] = hashTable[tempKey];
        hashTable.erase(tempKey);
      }
    }
  }
  std::cout << "Last line ----->  "
            << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}

void leftCycleLeftJoin_pair_CallByReference_ModifiedInt_hash(
    list<pair<int, int>> leftTable, int leftIndex,
    unordered_map<int, list<pair<int, int>>> &hashTemp,
    unordered_map<int, list<pair<int, int>>> &rightTabelHash, int rightIndex) {
  unordered_map<int, list<pair<int, int>>> hashTable;
  makeHashFunction_pair_CallByReference_ModifiedInt(leftTable, leftIndex,
                                                    hashTable);
int nishtha;
  int tempKey;
  int flag = 0;
  if (rightIndex) {
    for (unordered_map<int, list<pair<int, int>>>::iterator it =
             rightTabelHash.begin();
         it != rightTabelHash.end();) {
      for (list<pair<int, int>>::iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++) {
        tempKey = it2->second;
        if (hashTable.find(tempKey) != hashTable.end()) {
          hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        } else if (hashTemp.find(tempKey) == hashTemp.end()) {
          it2 = it->second.erase(it2);
          it2--;
        }
      }

      if (it->second.empty()) {
        it = rightTabelHash.erase(it);
        flag = 1;
      }
      if (flag != 1)
        it++;
      flag = 0;
    }
  } else {
    for (unordered_map<int, list<pair<int, int>>>::iterator it =
             rightTabelHash.begin();
         it != rightTabelHash.end();) {
      for (list<pair<int, int>>::iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++) {
        tempKey = it2->first;
        if (hashTable.find(tempKey) != hashTable.end()) {
          hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        } else if (hashTemp.find(tempKey) == hashTemp.end()) {
          it2 = it->second.erase(it2);
          it2--;
        }
      }
      if (it->second.empty()) {
        it = rightTabelHash.erase(it);
        flag = 1;
      }
      if (flag != 1)
        it++;
      flag = 0;
    }
  }
}

void rightCycleLeftJoin_pair_CallByReference_ModifiedInt(
    int rightIndex, unordered_map<int, list<pair<int, int>>> &rightHashTable,
    unordered_map<int, list<pair<int, int>>> leftHashTable,
    list<pair<int, int>> &rightTable) {

  int flag = 0;

  if (rightIndex) {
    for (unordered_map<int, list<pair<int, int>>>::iterator it =
             rightHashTable.begin();
         it != rightHashTable.end();) {

      for (list<pair<int, int>>::iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++) {
        if (leftHashTable.find(it2->second) != leftHashTable.end())
          rightTable.push_back(*it2);
        else {
          it2 = it->second.erase(it2);
          it2--;
        }
      }
      if (it->second.empty()) {
        it = rightHashTable.erase(it);
        flag = 1;
      }
      if (flag != 1)
        it++;
      flag = 0;
    }
  } else {
    for (unordered_map<int, list<pair<int, int>>>::iterator it =
             rightHashTable.begin();
         it != rightHashTable.end();) {
      for (list<pair<int, int>>::iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++) {
        if (leftHashTable.find(it2->first) != leftHashTable.end())
          rightTable.push_back(*it2);
        else {
          it2 = it->second.erase(it2);
          it2--;
        }
      }
      if (it->second.empty()) {
        it = rightHashTable.erase(it);
        flag = 1;
      }
      if (flag != 1)
        it++;
      flag = 0;
    }
  }
}

void rightCycleLeftJoin_pair_CallByReference_ModifiedInt_Table(
    unordered_map<int, list<pair<int, int>>> &leftHashTable,
    list<pair<int, int>> &rightTable, int rightIndex) {
  if (rightIndex) {
    for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
      if (leftHashTable.find(x->second) == leftHashTable.end()) {
        x = rightTable.erase(x);
        x--;
      }
    }
  } else {
    for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
      if (leftHashTable.find(x->first) == leftHashTable.end()) {
        x = rightTable.erase(x);
        x--;
      }
    }
  }
}

void callPairImplementation_CallByReference_ModifiedIntAuto(
    list<list<pair<int, int>>> tables) {
  const clock_t begin_time = clock();

  list<unordered_map<int, list<pair<int, int>>>> hashs;
  unordered_map<int, list<pair<int, int>>> empty;
  for (int i = 0; i < tables.size() - 1; i++)
    hashs.push_back(empty);

  auto hash = hashs.begin();
  auto table = tables.begin();

  if (tables.size() >= 2)
    leftCycleLeftJoin_pair_CallByReference_ModifiedInt(*(++table), 0, *table, 1,
                                                       *hash);

  std::cout << "Here----->  " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << endl;
  if (tables.size() >= 3) {
    for (table++; table != tables.end(); table++) {
      leftCycleLeftJoin_pair_CallByReference_ModifiedInt_hash(
          *table, 0, *(++hash), *hash, 1);
    }
  }
  if (tables.size() >= 3) {
    table--;
    hash--;
    table--;
  }

  table--;

  std::cout << "Left----->  " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << endl;
  if (tables.size() >= 4) {
    for (int i = 3; i < tables.size(); i++) {
      rightCycleLeftJoin_pair_CallByReference_ModifiedInt(1, *(--hash), *hash,
                                                          *table);
    }
    --table;
  }
  cout << tables.size() << endl;
  if (tables.size() >= 2)
    rightCycleLeftJoin_pair_CallByReference_ModifiedInt_Table(*hash, *(table),
                                                              1);
  cout << (*table).size() << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}