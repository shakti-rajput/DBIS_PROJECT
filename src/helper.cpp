#include "helper.h"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> string_burst(string str, char delimeter) {
  // condition: works with only single character delimeter, like $,_,space,etc.
  vector<string> words;
  int n = str.length();
  for (int i = 0; i < n; i++) {
    int j = i;
    while (str[i] != delimeter && i < n)
      i++;
    string temp = str.substr(j, i - j);
    words.push_back(temp);
  }
  return words;
}

void format100k(string line,
                unordered_map<string, list<list<string>>> &tabels) {
  vector<string> results = string_burst(line, '	');
  list<string> entry;
  string tableName;

  for (int i = 0; i < results.size(); i++) {
    vector<string> ele = string_burst(results[i], ':');
    if (ele.size() > 1) {
      if (i == results.size() - 1)
        ele[1] = ele[1].substr(0, ele[1].size() - 2);
      if (i == 1)
        tableName = ele[1];
      else
        entry.push_back(ele[1]);
    } else {
      ele[0] = ele[0].substr(0, ele[0].size() - 2);
      entry.push_back(ele[0]);
    }
  }
  tabels[tableName].push_back(entry);
}

void format100k_(string line,
                 unordered_map<string, list<pair<string, string>>> &tabels) {
  vector<string> results = string_burst(line, '	');

  pair<string, string> entry;
  string tableName;
  for (int i = 0; i < results.size(); i++) {
    vector<string> ele = string_burst(results[i], ':');

    if (ele.size() > 1) {
      if (i == results.size() - 1)
        ele[1] = ele[1].substr(0, ele[1].size() - 2);
      if (i == 1)
        tableName = ele[1];
      else if (i == 0)
        entry.first = ele[1];
      else if (i == 2)
        entry.second = ele[1];
    } else {
      ele[0] = ele[0].substr(0, ele[0].size() - 2);
      entry.second = ele[0];
    }
  }
  tabels[tableName].push_back(entry);
}

void format10M(string line, unordered_map<string, list<list<string>>> &tabels) {
  vector<string> results = string_burst(line, '	');

  list<string> entry;
  string tableName;

  entry.push_back(results[0]);
  entry.push_back(results[2]);
  tabels[results[1]].push_back(entry);
}

void format10M_(string line,
                unordered_map<string, list<pair<string, string>>> &tabels) {
  vector<string> results = string_burst(line, '	');

  pair<string, string> entry;
  entry.first = results[0];
  entry.second = results[2];

  tabels[results[1]].push_back(entry);
}

int joinAttributePosition(list<list<string>> leftTable, string attribute) {
  list<list<string>>::iterator ptr1 = leftTable.begin();
  list<string>::iterator innerPtr = (*ptr1).begin();
  if (*innerPtr == attribute)
    return 0;
  advance(innerPtr, 1);
  if (*innerPtr == attribute)
    return 1;
  else
    return -1;
}

void preprocessingStringtoInteger(list<pair<string, string>> followTabel_S,
                                  list<pair<string, string>> friendOfTabel_S,
                                  list<pair<string, string>> likesTabel_S,
                                  list<pair<string, string>> reviewTabel_S,
                                  list<pair<string, string>> reviewerTabel_S,
                                  unordered_map<string, int> &store,
                                  list<pair<int, int>> &followTabel_,
                                  list<pair<int, int>> &friendOfTabel_,
                                  list<pair<int, int>> &likesTabel_,
                                  list<pair<int, int>> &reviewTabel_,
                                  list<pair<int, int>> &reviewerTabel_) {

  // Tables are stored seperately now.

  int count = 0;
  for (auto x : followTabel_S) {
    if (store.find(x.first) == store.end()) {
      store[x.first] = count;
      count++;
    }
    if (store.find(x.second) == store.end()) {
      store[x.second] = count;
      count++;
    }
    followTabel_.push_back(pair(store[x.first], store[x.second]));
  }
  //////////////////////////////////////////////////////////////
  for (auto x : friendOfTabel_S) {
    if (store.find(x.first) == store.end()) {
      store[x.first] = count;
      count++;
    }
    if (store.find(x.second) == store.end()) {
      store[x.second] = count;
      count++;
    }
    friendOfTabel_.push_back(pair(store[x.first], store[x.second]));
  }
  //////////////////////////////////////////////////////////////
  for (auto x : likesTabel_S) {
    if (store.find(x.first) == store.end()) {
      store[x.first] = count;
      count++;
    }
    if (store.find(x.second) == store.end()) {
      store[x.second] = count;
      count++;
    }
    likesTabel_.push_back(pair(store[x.first], store[x.second]));
  }
  //////////////////////////////////////////////////////////////
  for (auto x : reviewTabel_S) {
    if (store.find(x.first) == store.end()) {
      store[x.first] = count;
      count++;
    }
    if (store.find(x.second) == store.end()) {
      store[x.second] = count;
      count++;
    }
    reviewTabel_.push_back(pair(store[x.first], store[x.second]));
  }
  //////////////////////////////////////////////////////////////
  for (auto x : reviewerTabel_S) {
    if (store.find(x.first) == store.end()) {
      store[x.first] = count;
      count++;
    }
    if (store.find(x.second) == store.end()) {
      store[x.second] = count;
      count++;
    }
    reviewerTabel_.push_back(pair(store[x.first], store[x.second]));
  }
}