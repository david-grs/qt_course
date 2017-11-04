Qt Concepts
  - QObject and its implications (no template)
  - Signals/slots
  - Meta Objects
  - COW/implicit sharing
  - QVariant 
  - Qt Event Loop
  - MVC


QObject
======= 
 - base class of many Qt classes  -> needed for signals/slots, event loop, etc
 - QObject parent, QObject children: bidirectional association (convention of ctor(QObject ptr) -> tree of QObject
 - when destroyed, all children are destroyed
 - cannot be copied
 - is named -> findChildren()
 - supports signals/slots, metaobjects, qobject\_cast

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

Item* foo = new Item("foo", &root);
Item* bar = new Item("bar", foo);
Item* baz = new Item("baz", &root);

root.dumpObjectTree();
```


signal/slot
===========
 - publish/subsribe (1 -> N) pattern: lose coupling between objects
 - part of class definition
 - Q_OBJECT's black magic = generated code, from moc, the Meta Object Compiler
 - ... comes with some limitations, cf multiple inheritance, templates
 - toolchain:

```c++
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
add_executable(app main.cc mainwindow.cc table_view.cc)

qt5_use_modules(app Widgets)
```


MetaObject
==========
