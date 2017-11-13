#include <QString>
#include <QVariant>
#include <QDebug>

struct A { int i; };
Q_DECLARE_METATYPE(A);

template <typename StreamT>
StreamT& operator<<(StreamT&& strm, const A& a) 
{ 
  strm << a.i; 
  return strm; 
}

int main()
{
  QMetaType::registerDebugStreamOperator<A>();

  QVariant v = 123;
  int i = v.toInt();

  v = "foo";
  qDebug() << v.typeName() << "=" << v.toString();

  v = QVariant::fromValue(A{1234});

  if (v.canConvert<A>())
    qDebug() << v.typeName() << "=" << v.value<A>();
 
  qDebug() << v;
  return 0;
}

