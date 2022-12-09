#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

vector<string> string_burst(string str, char delimeter);

void format100k(string line, unordered_map<string, list<list<string>>>& tabels);

void format100k_(string line, unordered_map<string, list<pair<string, string>>>& tabels);

void format10M(string line, unordered_map<string, list<list<string>>>& tabels);

void format10M_(string line, unordered_map<string, list<pair<string, string>>>& tabels);

int joinAttributePosition(list<list<string>> leftTable, string attribute);