#include "pairVersionCallByRefrence.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void makeHashFunction_pair_CallByReference(
    list<pair<string, string>> &tables, int index,
    unordered_map<string, list<pair<string, string>>> &hashTable) {
  int count = 0;
  string key = "";

  for (auto x : tables) {
    if (index) // if index == 1 then custom key is second element
      key = x.second;
    else
      key = x.first;
    hashTable[key].push_back(x);
  }
}

list<pair<string, string>> leftCycleLeftJoin_pair_CallByReference(
    list<pair<string, string>> leftTable, int leftIndex,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &hashTable) {

  list<pair<string, string>> finalTable;
  makeHashFunction_pair_CallByReference(leftTable, leftIndex, hashTable);

  // Can be avoided.
  unordered_map<string, list<pair<string, string>>> hashTemp = hashTable;

  string tempKey;
  for (auto x : rightTable) {

    if (rightIndex)
      tempKey = x.second;
    else
      tempKey = x.first;

    for (auto entry : hashTemp[tempKey])
      finalTable.push_back(entry);

    hashTemp.erase(tempKey);
  }
  for (auto x : hashTemp)
    hashTable.erase(x.first);

  return finalTable;
}

void rightCycleLeftJoin_pair_CallByReference(
    unordered_map<string, list<pair<string, string>>> &leftHashTable,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &rightHashTable) {

  string tempKey, tempKey2;
  unordered_map<string, list<pair<string, string>>> rightHashTableTemp;

  for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
    if (rightIndex) {
      tempKey = (*x).second;
      tempKey2 = (*x).first;
    } else {
      tempKey = (*x).first;
      tempKey2 = (*x).second;
    }

    if ((leftHashTable.find(tempKey) == leftHashTable.end())) {
      x = rightTable.erase(x);
      x--;
    } else {
      if (rightHashTableTemp.find(tempKey2) == rightHashTableTemp.end())
        rightHashTableTemp[tempKey2] = rightHashTable[tempKey2];
    }
  }
  rightHashTable = rightHashTableTemp;
}

void callPairImplementation_CallByReference(
    list<pair<string, string>> &followTabel,
    list<pair<string, string>> &friendOfTabel,
    list<pair<string, string>> &likesTabel,
    list<pair<string, string>> &reviewTabel) {

  unordered_map<string, list<pair<string, string>>> followTabelHash;
  unordered_map<string, list<pair<string, string>>> friendOfTabelHash;
  unordered_map<string, list<pair<string, string>>> likesTabelHash;
  unordered_map<string, list<pair<string, string>>> reviewTabelHash;

  const clock_t begin_time = clock();
  friendOfTabel = leftCycleLeftJoin_pair_CallByReference(
      friendOfTabel, 0, followTabel, 1, friendOfTabelHash);
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "likesTabel " << likesTabel.size() << endl;
  likesTabel = leftCycleLeftJoin_pair_CallByReference(
      likesTabel, 0, friendOfTabel, 1, likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "reviewTabel " << reviewTabel.size() << endl;
  reviewTabel = leftCycleLeftJoin_pair_CallByReference(
      reviewTabel, 0, likesTabel, 1, reviewTabelHash);
  cout << "reviewTabel " << reviewTabel.size() << endl;
  cout << "reviewTabelHash " << reviewTabelHash.size() << endl;
  cout << "----------------------------------------------" << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

  const clock_t begin_time2 = clock();
  rightCycleLeftJoin_pair_CallByReference(reviewTabelHash, likesTabel, 1,
                                          likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "friendOfTabelHash  " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin_pair_CallByReference(likesTabelHash, friendOfTabel, 1,
                                          friendOfTabelHash);
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin_pair_CallByReference(friendOfTabelHash, followTabel, 1,
                                          followTabelHash);
  cout << "follow Table " << followTabel.size() << endl;

  std::cout << float(clock() - begin_time2) / CLOCKS_PER_SEC << endl;
}
