#include <iostream>
#include <stack>
using namespace std;
 int isBalanced (string str)
 {
    stack < pair <char,int > > S ;
    int idx=-1;

    for (int i=0;i<str.size();i++)
     {
       if (str[i]=='{'||str[i]=='('||str[i]=='[')
            S.push(make_pair(str[i],(i+1)));
       else if (str[i]=='}')
       {
           if (S.size()&&S.top().first =='{')S.pop();
           else return (i+1);
       }
       else if (str[i]==')')
       {
           if (S.size()&&S.top().first=='(')S.pop();
           else return (i+1);
       }
       else if (str[i]==']')
       {
           if (S.size()&&S.top().first=='[')S.pop();
           else return (i+1);
       }
     }
     while (!S.empty())
     {
       idx= S.top().second;
       S.pop();
     }
     return idx ;
 }
int main()
{
  string str;
  cin>>str;
  int sol =isBalanced(str);
  (sol==-1)? cout <<"Success" : cout <<sol;
    return 0;
}
