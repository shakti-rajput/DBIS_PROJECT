#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "basicImplementation.h"

using namespace std;

unordered_map<string, list<list<string>>>

makeHashFunction(list<list<string>> &tables, int index) {
  int count = 0;
  unordered_map<string, list<list<string>>> hashTable;

  for (auto x : tables) {
    list<string> temp;
    list<string>::iterator ptr1 = x.begin();
    list<string>::iterator ptr2 = ptr1;
    advance(ptr1, 1);
    temp.push_back(*ptr2);
    temp.push_back(*ptr1);
    if (index)
      hashTable[*ptr1].push_back(temp);
    else
      hashTable[*ptr2].push_back(temp);
  }
  return hashTable;
}

list<list<string>>
leftCycleLeftJoin(list<list<string>> leftTable, int leftIndex,
                  list<list<string>> rightTable, int rightIndex,
                  unordered_map<string, list<list<string>>> &hashTable) {
  list<list<string>> finalTable;
  hashTable = makeHashFunction(leftTable, leftIndex);
  unordered_map<string, list<list<string>>> hashTemp =
      hashTable; // Can be avoided.
  for (auto x : rightTable) {
    list<string>::iterator ptr1 = x.begin();
    if (rightIndex)
      advance(ptr1, 1);
    for (auto entry : hashTemp[*ptr1])
      finalTable.push_back(entry);
    hashTemp.erase(*ptr1);
  }
  for (auto x : hashTemp)
    hashTable.erase(x.first);

  return finalTable;
}

void rightCycleLeftJoin(
    unordered_map<string, list<list<string>>> leftHashTable,
    list<list<string>> &rightTable, int rightIndex,
    unordered_map<string, list<list<string>>> &rightHashTable) {

  unordered_map<string, list<list<string>>> rightHashTableTemp;
  for (auto x = rightTable.begin(); x != rightTable.end(); x++) {
    list<string>::iterator ptr1 = (*x).begin();
    list<string>::iterator ptr2 = ptr1;
    if (rightIndex)
      advance(ptr1, 1);
    else
      advance(ptr2, 1);
    if ((leftHashTable.find(*ptr1) == leftHashTable.end())) {
      x = rightTable.erase(x);
      x--;
    } else {
      rightHashTableTemp[*ptr2] = rightHashTable[*ptr2];
    }
  }
  rightHashTable = rightHashTableTemp;
}

void callBasicImplementation(list<list<string>> followTabel,
                             list<list<string>> friendOfTabel,
                             list<list<string>> likesTabel,
                             list<list<string>> reviewTabel) {

  unordered_map<string, list<list<string>>> followTabelHash;
  unordered_map<string, list<list<string>>> friendOfTabelHash;
  unordered_map<string, list<list<string>>> likesTabelHash;
  unordered_map<string, list<list<string>>> reviewTabelHash;

  const clock_t begin_time = clock();
  friendOfTabel =
      leftCycleLeftJoin(friendOfTabel, 0, followTabel, 1, friendOfTabelHash);
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "likesTabel " << likesTabel.size() << endl;
  likesTabel =
      leftCycleLeftJoin(likesTabel, 0, friendOfTabel, 1, likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "reviewTabel " << reviewTabel.size() << endl;
  reviewTabel =
      leftCycleLeftJoin(reviewTabel, 0, likesTabel, 1, reviewTabelHash);
  cout << "reviewTabel " << reviewTabel.size() << endl;
  cout << "reviewTabelHash " << reviewTabelHash.size() << endl;
  cout << "----------------------------------------------" << endl;
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

  const clock_t begin_time2 = clock();
  rightCycleLeftJoin(reviewTabelHash, likesTabel, 1, likesTabelHash);
  cout << "likesTabel " << likesTabel.size() << endl;
  cout << "likesTabelHash " << likesTabelHash.size() << endl;
  cout << "friendOfTabelHash  " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin(likesTabelHash, friendOfTabel, 1, friendOfTabelHash);
  cout << "friendOfTabel " << friendOfTabel.size() << endl;
  cout << "friendOfTabelHash " << friendOfTabelHash.size() << endl;

  rightCycleLeftJoin(friendOfTabelHash, followTabel, 1, followTabelHash);
  cout << "follow Table " << followTabel.size() << endl;

  std::cout << float(clock() - begin_time2) / CLOCKS_PER_SEC << endl;
}