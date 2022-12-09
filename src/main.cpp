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
#include "pairVersion.h"
#include "pairVersionCallByRefrence.h"

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int count = 0;
  string FILENAME = "100k.txt";
  FILENAME = "watdiv10M.txt";
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
      // tablesChecking.
      format10M(line, tabels);
      format10M_(line, tabelsChecking);

      // count++;
      // if (count == 5)
      // {
      //     break;
      // }
    }
    file.close();
  }
  // cout << tabels.size() << endl;
  // cout << "Here-" << endl;
  // for (auto x : tabels) {
  //   cout << x.first << endl;
  //   count++;
  //   if (count == 5) {
  //     break;
  //   }
  // }

  // for (auto x : followTabel_)
  // {
  //     cout << x.flag << endl;

  //         cout << x.entries[0]<< " ";

  //     cout << endl;
  //     count++;
  //     if (count == 5)
  //     {
  //         break;
  //     }
  // }

  list<list<string>> followTabel = tabels["follows"];
  // Tables are stored seperately now.
  list<list<string>> friendOfTabel = tabels["friendOf"];
  list<list<string>> likesTabel = tabels["likes"];
  list<list<string>> reviewTabel = tabels["hasReview"];

  list<pair<string, string>> followTabel_ = tabelsChecking["follows"];
  // Tables are stored seperately now.
  list<pair<string, string>> friendOfTabel_ = tabelsChecking["friendOf"];
  list<pair<string, string>> likesTabel_ = tabelsChecking["likes"];
  list<pair<string, string>> reviewTabel_ = tabelsChecking["hasReview"];

  // Custom key of string can be made.. TO know wether we have deleted the key
  // or not.
  unordered_map<string, list<pair<string, string>>> followTabelHash_;
  unordered_map<string, list<pair<string, string>>> friendOfTabelHash_;
  unordered_map<string, list<pair<string, string>>> likesTabelHash_;
  unordered_map<string, list<pair<string, string>>> reviewTabelHash_;
  callBasicImplementation(followTabel, friendOfTabel, likesTabel, reviewTabel);
  cout << "=============================================================="
       << endl;
  callPairImplementation(followTabel_, friendOfTabel_, likesTabel_,
                         reviewTabel_);
  cout << "=============================================================="
       << endl;
  callPairImplementation_CallByReference(followTabel_, friendOfTabel_,
                                         likesTabel_, reviewTabel_);
  cout << "=============================================================="
       << endl;
  callPairImplementation_CallByReference_Modified(followTabel_, friendOfTabel_,
                                                  likesTabel_, reviewTabel_);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
