#include <iostream>
#include "tstack.h"

int main(int argc, char** argv) {
  TStack t = {};
  t.push(1);
  assert(t.top() == 1);
  t.push(2);
  assert(t.top() == 2);
  t.begin();
  assert(t.top() == 2);
  t.push(3);
  assert(t.top() == 3);
  t.push(4);
  assert(t.top() == 4);
  t.begin();
  assert(t.top() == 4);
  t.push(5);
  assert(t.top() == 5);
  t.commit();
  assert(t.top() == 5);
  t.rollback();
  assert(t.top() == 2);
  assert(t.pop() == 2);
  assert(t.pop() == 1);

  t = {};
  t.push(1);
  assert(t.top() == 1);
  t.push(2);
  assert(t.top() == 2);
  t.begin();
  assert(t.top() == 2);
  t.pop();
  assert(t.top() == 1);
  t.begin();
  assert(t.top() == 1);
  t.push(3);
  assert(t.top() == 3);
  t.commit();
  assert(t.top() == 3);
  t.rollback();
  assert(t.top() == 2);
  assert(t.pop() == 2);
  assert(t.pop() == 1);

  t = {};
  t.push(1);
  assert(t.top() == 1);
  t.push(2);
  assert(t.top() == 2);
  t.begin();
  assert(t.top() == 2);
  t.pop();
  assert(t.top() == 1);
  t.begin();
  assert(t.top() == 1);
  t.push(3);
  assert(t.top() == 3);
  t.rollback();
  assert(t.top() == 1);
  t.rollback();
  assert(t.top() == 2);
  assert(t.pop() == 2);
  assert(t.pop() == 1);


  t = {};
  t.push(1);
  assert(t.top() == 1);
  t.push(2);
  assert(t.top() == 2);
  t.begin();
  assert(t.pop() == 2);
  assert(t.pop() == 1);
  t.push(1);
  t.push(2);
  t.push(3);
  assert(t.top() == 3);
  t.begin();
  assert(t.top() == 3);
  t.push(4);
  assert(t.pop() == 4);
  assert(t.pop() == 3);
  assert(t.pop() == 2);
  assert(t.pop() == 1);
  t.rollback();
  assert(t.top() == 3);
  t.rollback();
  assert(t.top() == 2);
  return 0;
}
