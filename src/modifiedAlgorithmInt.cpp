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
  int count = 0;

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

unordered_map<int, list<pair<int, int>>>
leftCycleLeftJoin_pair_CallByReference_ModifiedInt(
    list<pair<int, int>> leftTable, int leftIndex,
    list<pair<int, int>> &rightTable, int rightIndex,
    unordered_map<int, list<pair<int, int>>> hashTable) {

  makeHashFunction_pair_CallByReference_ModifiedInt(leftTable, leftIndex,
                                                    hashTable);
  unordered_map<int, list<pair<int, int>>> hashTemp;

  int tempKey;
  if (rightIndex) {
    // for (list<pair<int, int>>::iterator it = rightTable.begin();
    //      it != rightTable.end(); it++) {
    //   tempKey = it->second;
    //   if (hashTable.find(tempKey) != hashTable.end()) {
    //     if (hashTemp.find(tempKey) == hashTemp.end()) {
    //       hashTemp[tempKey] = hashTable[tempKey];
    //       hashTable.erase(tempKey);
    //     }
    //   } else if (hashTemp.find(tempKey) == hashTemp.end()) {
    //     it = rightTable.erase(it);
    //     it--;
    //   }
    // }
    for (auto x : rightTable) {
      tempKey = x.second;
      if (hashTable.find(tempKey) != hashTable.end()) {
        if (hashTemp.find(tempKey) == hashTemp.end())
          hashTemp[tempKey] = hashTable[tempKey];
        hashTable.erase(tempKey);
      }
    }
  } else {
    for (auto x : rightTable) {
      tempKey = x.first;
      if (hashTable.find(tempKey) != hashTable.end()) {
        if (hashTemp.find(tempKey) == hashTemp.end()) {
          hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        }
      }
    }
  }
  return hashTemp;
}

unordered_map<int, list<pair<int, int>>>
leftCycleLeftJoin_pair_CallByReference_ModifiedInt_hash(
    list<pair<int, int>> leftTable, int leftIndex,
    unordered_map<int, list<pair<int, int>>> &rightTabelHash, int rightIndex,
    unordered_map<int, list<pair<int, int>>> hashTable, bool deleteflag) {

  makeHashFunction_pair_CallByReference_ModifiedInt(leftTable, leftIndex,
                                                    hashTable);

  unordered_map<int, list<pair<int, int>>> hashTemp;

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
          if (hashTemp.find(tempKey) == hashTemp.end())
            hashTemp[tempKey] = hashTable[tempKey];
          hashTable.erase(tempKey);
        } else if (hashTemp.find(tempKey) == hashTemp.end() && deleteflag) {
          it2 = it->second.erase(it2);
          it2--;
        }
      }

      if (it->second.empty() && deleteflag) {
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
          if (hashTemp.find(tempKey) == hashTemp.end())
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
  return hashTemp;
}

list<pair<int, int>> rightCycleLeftJoin_pair_CallByReference_ModifiedInt(
    unordered_map<int, list<pair<int, int>>> leftHashTable, int rightIndex,
    unordered_map<int, list<pair<int, int>>> &rightHashTable) {
  list<pair<int, int>> rightTable;
  int flag = 0;
  unordered_map<int, list<pair<int, int>>> rightHashTableTemp;

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
  return rightTable;
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

void callPairImplementation_CallByReference_ModifiedInt(
    list<pair<int, int>> followTabel, list<pair<int, int>> friendOfTabel,
    list<pair<int, int>> likesTabel, list<pair<int, int>> reviewTabel) {

  unordered_map<int, list<pair<int, int>>> followTabelHash;
  unordered_map<int, list<pair<int, int>>> friendOfTabelHash;
  unordered_map<int, list<pair<int, int>>> likesTabelHash;
  unordered_map<int, list<pair<int, int>>> reviewTabelHash;

  const clock_t begin_time = clock();
  friendOfTabelHash = leftCycleLeftJoin_pair_CallByReference_ModifiedInt(
      friendOfTabel, 0, followTabel, 1, friendOfTabelHash);
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "likesTabel " << likesTabel.size() << endl;
  bool flag = true;
  likesTabelHash = leftCycleLeftJoin_pair_CallByReference_ModifiedInt_hash(
      likesTabel, 0, friendOfTabelHash, 1, likesTabelHash, flag);
  flag = true;
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "reviewTabel " << reviewTabel.size() << endl;
  reviewTabelHash = leftCycleLeftJoin_pair_CallByReference_ModifiedInt_hash(
      reviewTabel, 0, likesTabelHash, 1, reviewTabelHash, flag);
  cout << "reviewTabel " << reviewTabel.size() << endl;
  cout << "reviewTabelHash " << reviewTabelHash.size() << endl;
  cout << "----------------------------------------------" << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

  const clock_t begin_time2 = clock();
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "friendOfTabelHash  " << friendOfTabelHash.size() << endl;

  friendOfTabel = rightCycleLeftJoin_pair_CallByReference_ModifiedInt(
      likesTabelHash, 1, friendOfTabelHash);
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin_pair_CallByReference_ModifiedInt_Table(friendOfTabelHash,
                                                            followTabel, 1);
  cout << "follow Table " << followTabel.size() << endl;

  std::cout << float(clock() - begin_time2) / CLOCKS_PER_SEC << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}