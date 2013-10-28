#include <string>

#include "UtilsWrapper.h"
#include "Utils.hh"

using namespace std;

extern "C" {
  CUtils *str_new(char *str) {
    Utils *s = new Utils(string(str));
    return (CUtils *)s;
  }

  void str_print(const CUtils *util) {
    Utils *u = (Utils *)util;
    u->printString();
  }

  char *str_value(const CUtils *util) {
    Utils *u = (Utils *)util;
    return u->str2chr();
  }

  char *str_replace(const CUtils *util, char *search, char *replacement) {
    Utils *u = (Utils *)util;
    u->replace(string(search), string(replacement));
    return u->str2chr();
  }

  void str_delete(CUtils *util) {
    Utils *u = (Utils *)util;
    delete u;
  }
}
