#include <QObject>
#include <QString>
#include <QDebug>

#include <iostream>

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

  root.dumpObjectTree();

  return 0;
}

