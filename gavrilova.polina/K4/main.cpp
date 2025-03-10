#include <iostream>
#include <istream>

template< class T >
struct FwdList {
  T data;
  FwdList* next;
};

template< class T >
void clear(FwdList< T >* head)
{
  while (head) {
    FwdList< T >* new_head = head->next;
    delete head;
    head = new_head;
  }
}

template< class T >
FwdList< T >* reverse_with_list(FwdList< T >* head)
{
  FwdList< FwdList< T >* >* stack = new FwdList< FwdList< T >* >{head, nullptr};
  while (head) {
    try {
      FwdList< FwdList< int >* >* new_node = new FwdList< FwdList< T >* >{head, stack};
      stack = new_node;
      head = head->next;
    } catch(const std::bad_alloc&) {
      clear< FwdList< T >*>(stack);
      throw;
    }
  }
  head = stack->data;
  FwdList< T >* current_head = head;
  FwdList< FwdList< T >* >* cur_stack = stack;
  while (cur_stack->next) {
    current_head->next = cur_stack->next->data;
    cur_stack = cur_stack->next;
    current_head = current_head->next;
    delete stack;
    stack = cur_stack;
  }
  clear< FwdList< int >*>(stack);
  return head;

}

template< class T >
FwdList< T >* reverse_cleanly(FwdList< T >* head) {
  if (!head) return nullptr;
  FwdList< T >* cur = head->next;
  if (!cur) return head;
  FwdList< T >* temp = cur->next;
  head->next = nullptr;
  while (temp) {
    cur->next = head;
    head = cur;
    cur = temp;
    temp = temp->next;
  }
  return cur;
}

template<class T>
FwdList<T>* reverse_recursively(FwdList<T>* head) {
    if (!head || !head->next) {
        return head;
    }

    FwdList<T>* new_head = reverse_recursively(head->next);

    head->next->next = head;
    head->next = nullptr;

    return new_head;
}

std::istream& inputListInt(std::istream& in, FwdList< int >* head)
{
  FwdList< int >* cur = head;
  while (!std::cin.eof()) {
    int newData = 0;
    if (!(in >> newData)) {
      return in;
    }
    try {
      cur = new FwdList< int >{newData, nullptr};
      cur = cur->next;
    } catch(const std::bad_alloc&) {
      clear< int >(head);
      throw;
    }
  }
  return in;
}

std::ostream& outputListInt(std::ostream& out, FwdList< int >* head)
{
  while (head) {
    out << head->data;
    head = head->next;
  }
  return out;
}

int main (int argc, char** argv)
{
  *argv = nullptr;
  FwdList< int >* head = nullptr;
  if (!inputListInt(std::cin, head)) {
    std::cerr << "Invalid input\n";
    return 1;
  }
  FwdList< int >* new_head = nullptr;
  switch(argc) {
    case 0:
      new_head = reverse_with_list< int >(head);
      break;
    case 1:
      new_head = reverse_cleanly< int >(head);
      break;
    case 2:
      new_head = reverse_recursively< int >(head);
      break;
    default:
      new_head = reverse_cleanly< int >(head);
  }
  outputListInt(std::cout, new_head);
}
