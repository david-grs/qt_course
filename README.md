Qt Concepts
  - QObject 
  - Signals/slots
  - Meta Objects
  - COW/implicit sharing
  - QVariant 
  - Qt Event Loop
  - MVC

Qt
==
 - originally GUI only
 - gained so much popularity that many developers use it for non-GUI stuff: Core, Xml, Json, Networking, Databases, Multimedia, ...



QObject
======= 
 - base class of many Qt classes, all widget classes - exceptions: containers, lightweight types
 - offers support for memory management, signals/slots, meta info, qobject\_cast, event loop, ...
 - every QObject has a parent: "hierarchical and queryable object tree that organize object ownership in a natural way"

```c++
class Item : public QObject
{
    Q_OBJECT

public:
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

root.dumpObjectTree(); // useful for debugging!
```

 - memory management
   - rule of thumb: every allocated with new, except "root" widget: no stack, no smart pointer: can cause double-free
   - deleting the parent will delete recursively all children 
   - deleting a child will unparent it 
 - named: debugging, finding widget (QList<T> findChildren<T>(const QRegExp&))
 - widgets don't need to be stored as class attributes: you create them (link to parent) and connect their signals/slots
 - cannot be copied: name? connections? parent?

Avoid classic mistakes:
 - QObject declaration should be in a .h file
 - All QObject should be have Q_OBJECT declared
 - Allocate children QObject on the heap with *new*
 - If multiple inheritance: only one inherited class can inherit from QObject, and it should be the *first one*



Signals/Slots
=============
 - publish/subsribe (1 -> N) pattern
 - part of class declaration:

```c++
class QTimer : public QObject
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

 - used for all GUI events, but not only!
 - better than direct callbacks:
   - types don't know about each other (lose coupling)
   - solves lifetime issue on receiver end
   - event loop integration
   - multi threading for free



Meta Object
===========
 - like RTTI, but better (+ some reflection)
 - every QObject has an associated meta object
 - Q_OBJECT offers introspection features: className(), inherits(), classInfo
 - MOC, Meta Object Compiler, parses header and generates code
 - classic c++ build: class.h + class.cc -> class.o -> exec
 - qt build: same, + class.h -> moc_class.cc -> moc_class.o + class.o -> exec
 - MOC parses the header file, generates stubs for signals and slots, meta info, etc.
 - a signal is just a function! it's only here for MOC, cf qobjectdefs.h:

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
add_executable(app main.cc widget.cc)

qt5_use_modules(app Widgets)
```



Containers
==========
 - std::vector -> QVector
 - std::map -> QMap
 - std::unordered_map -> QHash
 - std::set -> N/A
 - std::list -> QLinkedList
 - QList: an interesting beast
   - O(1) index lookup, amortized O(1) prepending and appending, O(n) insertion
   - preallocates memory before/after its internal array
   - store the element directly if sizeof(T) <= sizeof(void\*), otherwise store T\*
 - std::vector<std::string> -> QStringList inherits from QList<QString>, and adds join, split, filter, etc.


Implicit sharing
================
```c++
QStringList foo;
foo << "foo" << "bar" << "baz";

QStringList bar = foo;
```

 - `foo` and `bar` points to the same internal object
 - copying any Qt object is very cheap (cf implicit\_sharing.cc): shallow copy: atomic int + pointer copy
 - modifying the object causes a "detach": deep copy
 - also called Copy On Write (COW)



Q&A
===
 - What does QObject offer exactly, except the memory management?
 - Can a (custom) type be declared with Q_OBJECT without inheriting from QObject?
 - What can we do with QObject::metaObject()? Is this a static method?
