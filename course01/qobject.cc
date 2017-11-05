#include <QObject>
#include <QString>
#include <QDebug>

#include <iostream>
#include <memory>

struct Item : public QObject
{
    Item(QString name, QObject* parent = nullptr) :
        QObject(parent)
    {
        setObjectName(name);
    }

    ~Item() 
    {
       qDebug() << "destroying" << objectName(); 
    }
};

int main()
{
  QObject root;
  root.setObjectName("root");

  Item* foo = new Item("foo", &root);
  Item* bar = new Item("bar", foo);
  Item* baz = new Item("baz", &root);
  
  // no stack allocation nor smart pointer except for the parent
  // Item wrong("wrong", &root);
  // auto wrong2 = std::make_unique<Item>("wrong2", &root);

  root.dumpObjectTree();

  return 0;
}

