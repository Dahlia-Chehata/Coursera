#include <iostream>
using namespace std;

int get_change(int m) {
int w1=10,w2=5,w3=1;
int n=0;
while (m > 0)
{
  if (m-w1>=0)m-=w1;
  else if (m-w2>=0) m-=w2;
  else m-=w3;
  n++;
}
  return n;
}

int main() {
  int m;
  cin >> m;
  cout << get_change(m) << '\n';
}
