#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>

using std::string;
using std::vector;
using std::cin;
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {

    int bucket_count;
    vector <deque <string> > data;
    vector <string> result;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count):
        bucket_count(bucket_count)
        ,data(bucket_count)
        ,result()
         {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void insert(const string &str)
    {
       int index = hash_func(str);
       deque  <string> &q = data[index];
       //cout <<"insert " <<q.size() <<endl;
       if ( find ( q.begin(),q.end(),str) == q.end() )
        q.push_front(str);

    }
    void del (string str)
    {
        int index=hash_func(str);
        deque <string> &q = data[index];
        deque <string>::iterator it= find(q.begin(),q.end(),str);
       if (it!=q.end())
        q.erase(it);

    }
    string Find(string str)
    {
        int index=hash_func(str);
        deque <string> &q = data[index];
        deque <string>::iterator it= find(q.begin(),q.end(),str);
        if(it==q.end()) return "no";
        return "yes";
    }
    string check (int i)
    {
     deque <string> &q = data[i];
     stringstream ss;
     if (q.empty())return "";
     for (deque<string>::iterator it=q.begin();it!=q.end();++it)
        ss<<*it<<" ";
    return ss.str();
    }
    void writeSearchResult() {
         for (vector<string>::iterator it=result.begin(); it!=result.end(); it++)
                 cout<<*it<<endl;
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            string str = check(query.ind);
            result.push_back(str);
        } else {
            if (query.type == "find")
            result.push_back(Find(query.s));
            else if (query.type == "add")
                insert(query.s);
             else if (query.type == "del")
                del(query.s);
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
            writeSearchResult();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
