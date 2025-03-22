#include "common/proxy_run_main.h"

#include <iostream>
#include <string>

int main(int nargs, char **pargs) {
  std::string solution_name;
  if (nargs >= 2) {
    solution_name = pargs[1];
  } else {
    std::cout << "Input codeforces solution to run:" << std::endl;
    std::cin >> solution_name;
  }
  return auto_run_or_test(solution_name, (nargs > 2) ? pargs[2] : "",
                          (nargs > 3) ? pargs[3] : "");
}
