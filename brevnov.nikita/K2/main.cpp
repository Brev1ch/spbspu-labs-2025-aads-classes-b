#include <iostream>

struct FwdList {
  int value;
  FwdList * next;
};

void addElements(FwdList * head, int a, int b)
{
  FwdList * help = head;
  for (int i = 0; i < a - 1; i++)
  {
    help = help->next;
  }
  int value = help->value;
  for (int i = 0; i < b; i++)
  {
    help->next = new FwdList{value, help->next};
    help = help->next;
  }
}

void clearElements(FwdList * deletehelp, int i)
{
  FwdList * deletenext = deletehelp->next;
  for (int j = 0; j < i - 1; j++)
  {
    delete deletehelp;
    deletehelp = deletenext;
    deletenext = deletenext->next;
  }
  delete deletehelp;
}

int main()
{
  FwdList * head = new FwdList{0, nullptr};
  FwdList * tail = head;
  FwdList * deletehelp = head;
  for (int i = 1; i < 10; i++)
  {
    tail->next = new FwdList{i, nullptr};
    tail = tail->next;
  }
  int size = 10;
  int a = 0, b = 0;
  while (!std::cin.eof())
  {
    std::cin >> a;
    if (std::cin.eof() || std::cin.fail() || a <= 0)
    {
      break;
    }
    std::cin >> b;
    if (std::cin.fail())
    {
      break;
    }
    if (a > size)
    {
      std::cerr << "Index out of range!\n";
      clearElements(deletehelp, size);
      return 1;
    }
    addElements(head, a, b);
    size += b;
  }
  std::cout << head->value;
  for (int i = 1; i < size; i++)
  {
    head = head->next;
    std::cout << " " << head->value;
  }
  std::cout << "\n";
  clearElements(deletehelp, size);
  return 0;
}
