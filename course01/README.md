Qt Concepts
  - QObject 
  - Signals/slots
  - Meta Objects
  - COW/implicit sharing
  - QVariant 
  - Qt Event Loop
  - MVC


QObject
======= 
 - base class of many Qt classes  -> needed for signals/slots, meta info, event loop, etc
 - cannot be copied
 - ctor(QObject ptr) -> tree of QObject -> memory management: 1. deleting the parent will delete recursively all children 2. deleting a child will unparent it -> no children on the stack!
 - is named -> QList<T> findChildren<T>(const QRegExp&)
 - ... which is why most of the time widgets arent stored as member attributes: you dont own them, and you can find them if needed
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
       qDebug() << "destroying" << objectName(); 
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
 - part of class declaration:

```c++
class QTimer : class QObject
{
  Q_OBJECT

public:
  explicit QTimer(QObject *parent = nullptr);
  ~QTimer();
  
  void setInterval(int msec);

public slots:
  void start();
  void stop();

signals:
  void timeout();
};
```


```c++
QTimer* timer = new QTimer(this);
timer->setInternal(1000);

// do NOT use the old syntax - no build time checks
// QObject::connect(this, SIGNAL(started), timer, SLOT(start(int)));

QObject::connect(this, &Application::started, timer, &QTimer::start);

QObject::connect(timer, &QTimer::timeout, [this]() 
{ 
    qApp->quit(); 
});
```

 - Q_OBJECT's black magic = generated code by MOC, the Meta Object Compiler
 - comes with some limitations, cf multiple inheritance, templates
 - signals, slots are just here for MOC, cf qobjectdefs.h

```c++
#define signals public
#define slots /* nothing */
#define emit /* nothing */
```

 - running MOC can be enabled automatically via CMake:

```c++
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
add_executable(app main.cc mainwindow.cc table_view.cc)

qt5_use_modules(app Widgets)
```


MetaObject
==========
