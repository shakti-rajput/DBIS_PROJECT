#include "modifiedAlgorithm.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void makeHashFunction_pair_CallByReference_Modified(
    list<pair<string, string>> &tables, int index,
    unordered_map<string, list<pair<string, string>>> &hashTable) {
  int count = 0;
  string key = "";

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
}

void leftCycleLeftJoin_pair_CallByReference_Modified(
    list<pair<string, string>> leftTable, int leftIndex,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &hashTable) {

  makeHashFunction_pair_CallByReference_Modified(leftTable, leftIndex,
                                                 hashTable);
  // Can be avoided.
  unordered_map<string, list<pair<string, string>>> hashTemp;

  string tempKey;
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
  hashTable = hashTemp;
}

void leftCycleLeftJoin_pair_CallByReference_Modified_hash(
    list<pair<string, string>> leftTable, int leftIndex,
    unordered_map<string, list<pair<string, string>>> rightTabelHash,
    int rightIndex,
    unordered_map<string, list<pair<string, string>>> &hashTable) {

  makeHashFunction_pair_CallByReference_Modified(leftTable, leftIndex,
                                                 hashTable);

  // Can be avoided.
  unordered_map<string, list<pair<string, string>>> hashTemp;

  string tempKey;

  if (rightIndex) {
    for (auto x : rightTabelHash) {
      for (auto item : x.second) {
        tempKey = item.second;
        if (hashTable.find(tempKey) != hashTable.end()) {
          hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        }
      }
    }
  } else {
    for (auto x : rightTabelHash) {
      for (auto item : x.second) {
        tempKey = item.first;
        if (hashTable.find(tempKey) != hashTable.end()) {
          hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        }
      }
    }
  }
  hashTable = hashTemp;
}

void rightCycleLeftJoin_pair_CallByReference_Modified(
    unordered_map<string, list<pair<string, string>>> &leftHashTable,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &rightHashTable) {
  list<pair<string, string>> temp;
  rightTable = temp;
  string tempKey, tempKey2;
  unordered_map<string, list<pair<string, string>>> rightHashTableTemp;

  if (rightIndex) {
    for (auto x : rightHashTable) {
      for (auto y : x.second) {
        tempKey = y.second;
        tempKey2 = y.first; // This assignment should need to be changed in
                            // generic implementation
        if ((leftHashTable.find(tempKey) != leftHashTable.end())) {
          rightTable.push_back(y);
        }
      }
    }
  } else {
    for (auto x : rightHashTable) {
      for (auto y : x.second) {
        tempKey = y.first;
        tempKey2 = y.second; // This assignment should need to be changed in
                             // generic implementation
        if ((leftHashTable.find(tempKey) != leftHashTable.end())) {
          rightTable.push_back(y);
        }
      }
    }
  }
}

void rightCycleLeftJoin_pair_CallByReference_Modified_Table(
    unordered_map<string, list<pair<string, string>>> &leftHashTable,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &rightHashTable) {

  string tempKey, tempKey2;
  unordered_map<string, list<pair<string, string>>> rightHashTableTemp;

  if (rightIndex) {
    for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
      tempKey = (*x).second;
      tempKey2 = (*x).first;
      if ((leftHashTable.find(tempKey) == leftHashTable.end())) {
        x = rightTable.erase(x);
        x--;
      } 
    }
  } else {
    for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
      tempKey = (*x).first;
      tempKey2 = (*x).second;
      if ((leftHashTable.find(tempKey) == leftHashTable.end())) {
        x = rightTable.erase(x);
        x--;
      } 
    }
  }
}

void callPairImplementation_CallByReference_Modified(
    list<pair<string, string>> &followTabel,
    list<pair<string, string>> &friendOfTabel,
    list<pair<string, string>> &likesTabel,
    list<pair<string, string>> &reviewTabel) {

  unordered_map<string, list<pair<string, string>>> followTabelHash;
  unordered_map<string, list<pair<string, string>>> friendOfTabelHash;
  unordered_map<string, list<pair<string, string>>> likesTabelHash;
  unordered_map<string, list<pair<string, string>>> reviewTabelHash;

  const clock_t begin_time = clock();
  leftCycleLeftJoin_pair_CallByReference_Modified(friendOfTabel, 0, followTabel,
                                                  1, friendOfTabelHash);
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "likesTabel " << likesTabel.size() << endl;
  leftCycleLeftJoin_pair_CallByReference_Modified_hash(
      likesTabel, 0, friendOfTabelHash, 1, likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "reviewTabel " << reviewTabel.size() << endl;
  leftCycleLeftJoin_pair_CallByReference_Modified_hash(
      reviewTabel, 0, likesTabelHash, 1, reviewTabelHash);
  cout << "reviewTabel " << reviewTabel.size() << endl;
  cout << "reviewTabelHash " << reviewTabelHash.size() << endl;
  cout << "----------------------------------------------" << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

  const clock_t begin_time2 = clock();
  rightCycleLeftJoin_pair_CallByReference_Modified(reviewTabelHash, likesTabel,
                                                   1, likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "friendOfTabelHash  " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin_pair_CallByReference_Modified(
      likesTabelHash, friendOfTabel, 1, friendOfTabelHash);
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin_pair_CallByReference_Modified_Table(
      friendOfTabelHash, followTabel, 1, followTabelHash);
  cout << "follow Table " << followTabel.size() << endl;

  std::cout << float(clock() - begin_time2) / CLOCKS_PER_SEC << endl;
}