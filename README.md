reversed_range
==============

This is just something I hacked for fun, when I saw Stephane Charette's [post] (https://plus.google.com/107464459158813746872/posts/d9kGNpCGaGm) this morning.

Obviously, you should use [Boost] (http://www.boost.org/doc/libs/1_51_0/libs/range/doc/html/range/reference/adaptors/reference/reversed.html) if your code base already depend on it. If not, this may just work for you.

```
// $ clang++ -std=c++11 -g -I path/to/reversed_range/ reversed_range.cpp -o reversed_range && ./reversed_range

#include <reversed_range.hpp>
#include <string>
#include <iostream>

int main()
{
  using namespace std;

  string hello = "hello";

  for(auto c : hello)
    cout << c;
  cout << endl;

  for(auto c : reversed_range::reversed(hello))
    cout << c;
  cout << endl;

  for(auto i = reversed_range::crbegin(hello);
      i != reversed_range::crend(hello);
      ++i)
  {
    cout << *i;
  }
  cout << endl;

  for(auto c : reversed_range::reversed(reversed_range::creversed(hello)))
  {
    cout << c;
  }
  cout << endl;

  return 0;
}
```
