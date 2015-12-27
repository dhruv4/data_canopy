#include <iostream>
#include <string>
#include <regex>

//g++ -std=c++11 practice.cc
//gcc version 4.9.3

int main ()
{
  std::string s ("14;13;{1,2,3,4,5,9,12}");
  std::regex e ("(\\d+)(?=;)|([0-9]+)(?=,)|([0-9]+)(?=})");

  std::sregex_iterator next(s.begin(), s.end(), e);
  std::sregex_iterator end;

  std::smatch match = *next;
  printf("%ld\n", std::stol(match.str()));
  next++;
  match = *next;
  printf("%ld\n", std::stol(match.str()));
  next++;

  while (next != end) {
    match = *next;
    printf("%d\n", std::stoi(match.str()));
    //std::cout << match.str() << "\n";
    next++;
  }

  return 0;
}