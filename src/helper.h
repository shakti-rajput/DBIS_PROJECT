#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> string_burst(string str, char delimeter);

void format100k(string line, unordered_map<string, list<list<string>>> &tabels);

void format100k_(string line,
                 unordered_map<string, list<pair<string, string>>> &tabels);

void format10M(string line, unordered_map<string, list<list<string>>> &tabels);

void format10M_(string line,
                unordered_map<string, list<pair<string, string>>> &tabels);

int joinAttributePosition(list<list<int>> leftTable, int attribute);

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
                                  list<pair<int, int>> &reviewerTabel_);