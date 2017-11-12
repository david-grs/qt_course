#include "qobject.h"

#include <iostream>
#include <memory>

int main()
{
  QObject root;
  root.setObjectName("root");

  Item* foo = new Item("foo", &root);
  Item* bar = new Item("bar", foo);
  
  root.dumpObjectTree();

  return 0;
}

