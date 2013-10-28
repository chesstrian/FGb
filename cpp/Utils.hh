#include <string>

class Utils {
public:
  Utils(std::string str);
  void printString();
  char *str2chr();
  void replace(std::string search, std::string replacement);

private:
  std::string str;
};
