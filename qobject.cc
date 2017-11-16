#include "qobject.h"

int main()
{
  Item root("root");

  Item* foo = new Item("foo", &root);
  Item* bar = new Item("bar", foo);
  Item* baz = new Item("baz", &root);
  
  root.dumpObjectTree();

  return 0;
}

