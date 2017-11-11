#include <QString>

#include <chrono>
#include <string>
#include <iostream>

template <typename Callable>
void run_benchmark(const std::string& desc, std::size_t iterations, Callable&& callable)
{
    auto start = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < iterations; ++i)
        callable();

    auto end = std::chrono::steady_clock::now();

    double total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << desc << ": total_time=" << total_time << "ms";

    double per_iteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / double(iterations);
    std::cout << " per_iteration=" << per_iteration << "ns" << std::endl;
}


QString __attribute__ ((noinline)) CopyString(const QString& str)
{
  return str;
}

int main()
{
  QString str = "foo";
  int sum = 0;

  run_benchmark("implicit_sharing", 10e6, [&]()
  {
    QString copy = CopyString(str);
    sum += copy.size();
  });

  str += "bar";
  return 0;
}

