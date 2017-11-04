Qt Concepts
  - QObject and its implications (no template)
  - Signals/slots
  - Meta Objects
  - COW/implicit sharing
  - QVariant 
  - Qt Event Loop
  - MVC


QObject:
 - base class of many Qt classes  -> needed for signals/slots, event loop, etc
 - QObject parent, QObject children: bidirectional association (convention of ctor(QObject ptr) -> tree of QObject
 - when parent is destroyed, all children are destroyed
 - cannot be copied
 - it is named: findChildren()


```c++
struct Item : public QObject
{
    Item(QString name, QObject* parent = nullptr) :
        QObject(parent)
    {
        setObjectName(name);
    }

    ~Item() 
    {
       qDebug() << "destroying" << name; 
    }
};

QObject root;
root.setObjectName("root");

new Item("item1", &root);
new Item("item2", &root);
new Item("item3", &root);
```
