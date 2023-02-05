// ConsoleApplication1.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "basicImplementation.h"
#include "helper.h"
#include "modifiedAlgorithm.h"
#include "modifiedAlgorithmInt.h"
#include "pairVersion.h"
#include "pairVersionCallByRefrence.h"

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  string FILENAME = "watdiv10M.txt";
  ifstream file(FILENAME);

  unordered_map<string, list<pair<string, string>>>
      tabelsChecking; // Tables Name and pair entries of the table will be
                      // stored.
  // Ex - tabels["follows"] as 1 entry.

  unordered_map<string, list<list<string>>>
      tabels; // Tables Name and pair entries of the table.
  // Ex - tabels["follows"] as 1 entry.

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {

      // format100k(line, tabels);          // Entries getting stored in tables.
      // format100k_(line, tabelsChecking); // Entries getting stored in

      format10M(line, tabels);
      format10M_(line, tabelsChecking);
    }
    file.close();
  }

  list<list<string>> followTabel = tabels["follows"];
  // Tables are stored seperately now.
  list<list<string>> friendOfTabel = tabels["friendOf"];
  list<list<string>> likesTabel = tabels["likes"];
  list<list<string>> reviewTabel = tabels["hasReview"];
  // list<list<string>> reviewer = tabels["reviewer"];
  //  list<list<int>> followTabel = tabels["follows"];
  // // Tables are stored seperately now.
  // list<list<int>> friendOfTabel = tabels["friendOf"];
  // list<list<int>> likesTabel = tabels["likes"];
  // list<list<int>> reviewTabel = tabels["hasReview"];
  // // list<list<string>> reviewer = tabels["reviewer"];

  list<pair<string, string>> followTabel_S = tabelsChecking["follows"];
  // Tables are stored seperately now.
  list<pair<string, string>> friendOfTabel_S = tabelsChecking["friendOf"];
  list<pair<string, string>> likesTabel_S = tabelsChecking["likes"];
  list<pair<string, string>> reviewTabel_S = tabelsChecking["hasReview"];
  list<pair<string, string>> reviewerTabel_S = tabelsChecking["reviewer"];
  unordered_map<string, int> store;
  list<pair<int, int>> followTabel_;
  list<pair<int, int>> friendOfTabel_;
  list<pair<int, int>> likesTabel_;
  list<pair<int, int>> reviewTabel_;
  list<pair<int, int>> reviewerTabel_;
  const clock_t begin_time_preprocessing = clock();
  preprocessingStringtoInteger(followTabel_S, friendOfTabel_S, likesTabel_S,
                               reviewTabel_S, reviewerTabel_S, store,
                               followTabel_, friendOfTabel_, likesTabel_,
                               reviewTabel_, reviewerTabel_);
  std::cout << "Preprocessing Time --> "
            << float(clock() - begin_time_preprocessing) / CLOCKS_PER_SEC
            << endl;

  // Custom key of string can be made.. TO know wether we have deleted the key
  // or not.
  callBasicImplementation(followTabel, friendOfTabel, likesTabel, reviewTabel);
  cout << "callBasicImplementation "
          "=============================================================="
       << endl;
  callPairImplementation(followTabel_S, friendOfTabel_S, likesTabel_S,
                         reviewTabel_S);
  cout << " callPairImplementation "
          "=============================================================="
       << endl;
  callPairImplementation_CallByReference(followTabel_S, friendOfTabel_S,
                                         likesTabel_S, reviewTabel_S);
  cout << "callPairImplementation_CallByReference "
          "=============================================================="
       << endl;
  callPairImplementation_CallByReference_Modified(
      followTabel_S, friendOfTabel_S, likesTabel_S, reviewTabel_S);
  cout << "callPairImplementation_CallByReference_Modified "
          "=============================================================="
       << endl;

  callPairImplementation_CallByReference_Modified(
      followTabel_S, likesTabel_S, reviewTabel_S, reviewerTabel_S);
  cout << "callPairImplementation_CallByReference_Modified Manik "
          "Query=============================================================="
       << endl;
  list<list<pair<int, int>>> tables1;
  tables1.push_back(followTabel_);
  tables1.push_back(likesTabel_);
  tables1.push_back(reviewTabel_);
  tables1.push_back(reviewerTabel_);
  callPairImplementation_CallByReference_ModifiedIntAuto(tables1);
  cout << "callPairImplementation_CallByReference_ModifiedInt Manik "
          "Query=============================================================="
       << endl;
  // const clock_t begin_time = clock();
  cout << "callPairImplementation_CallByReference_ModifiedInt "
          "=============================================================="
       << endl;
  list<list<pair<int, int>>> tables;
  tables.push_back(followTabel_);
  tables.push_back(friendOfTabel_);
  tables.push_back(likesTabel_);
  tables.push_back(reviewTabel_);
  callPairImplementation_CallByReference_ModifiedIntAuto(tables);
}