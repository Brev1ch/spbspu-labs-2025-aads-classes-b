#include <iostream>
#include "forward-list.hpp"

int main()
{
  kizhin::FwdList* list = kizhin::initList(0, 10);
  try {
    std::size_t position = 0;
    std::size_t size = 0;
    while (std::cin >> position >> size) {
      insertDuplicates(list, position, size);
    }
    kizhin::outputList(std::cout, list) << '\n';
  } catch (const std::exception& e) {
    kizhin::clear(list);
    std::cerr << e.what() << '\n';
    return 1;
  }
  kizhin::clear(list);
}

