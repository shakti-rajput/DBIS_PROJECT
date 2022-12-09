#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// first implementatin of project file
unordered_map<string, list<list<string>>>
makeHashFunction(list<list<string>> &tables, int index);

list<list<string>>
leftCycleLeftJoin(list<list<string>> leftTable, int leftIndex,
                  list<list<string>> rightTable, int rightIndex,
                  unordered_map<string, list<list<string>>> &hashTable);

void rightCycleLeftJoin(
    unordered_map<string, list<list<string>>> leftHashTable,
    list<list<string>> &rightTable, int rightIndex,
    unordered_map<string, list<list<string>>> &rightHashTable);

void callBasicImplementation(list<list<string>> followTabel,
                             list<list<string>> friendOfTabel,
                             list<list<string>> likesTabel,
                             list<list<string>> reviewTabel);