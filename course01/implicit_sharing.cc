#include <QString>

QString __attribute__ ((noinline)) CopyString(const QString& str)
{
  return str;
}

int main()
{
  QString str = "foo";
  QString copy = CopyString(str);

  str += "bar";
  return copy.size();
}

