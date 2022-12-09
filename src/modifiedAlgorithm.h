#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void makeHashFunction_pair_CallByReference_Modified(
    list<pair<string, string>> &tables, int index,
    unordered_map<string, list<pair<string, string>>> &hashTable);

void leftCycleLeftJoin_pair_CallByReference_Modified(
    list<pair<string, string>> leftTable, int leftIndex,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &hashTable);

void rightCycleLeftJoin_pair_CallByReference_Modified(
    unordered_map<string, list<pair<string, string>>> &leftHashTable,
    list<pair<string, string>> &rightTable, int rightIndex,
    unordered_map<string, list<pair<string, string>>> &rightHashTable);

void callPairImplementation_CallByReference_Modified(
    list<pair<string, string>> &followTabel,
    list<pair<string, string>> &friendOfTabel,
    list<pair<string, string>> &likesTabel,
    list<pair<string, string>> &reviewTabel);