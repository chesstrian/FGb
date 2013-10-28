#include <iostream>
#include <cstring>
#include <string>
#include "Utils.hh"

using namespace std;

Utils::Utils(string str) {
  this->str = str;
}

void Utils::printString() {
  cout << this->str << endl;
}

char *Utils::str2chr() {
  char *chr = new char[this->str.length() + 1];
  strcpy(chr, this->str.c_str());
  return chr;
}

void Utils::replace(string search, string replacement) {
  this->str.replace(this->str.find(search), search.length(), replacement);
}
