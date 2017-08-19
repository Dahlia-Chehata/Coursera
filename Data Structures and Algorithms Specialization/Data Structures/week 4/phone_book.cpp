#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using std::string;
using std::vector;
using std::cin;
using namespace std;

unordered_map <int,string> Map ;

vector <string> read_queries() {
    int n;
    cin >> n;
    string type,name;
    int number ;
    vector <string> queries;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        if (type == "add")
        {
             cin >> number >> name;

             auto it = Map.find(number);
             if(it != Map.end())
                it->second = name;
             else
             Map.insert(make_pair(number,name));
        }

        else if (type=="find")
        {
           cin>>number;
           auto it=Map.find(number);
           if (it!=Map.end())
                queries.push_back(it->second);
           else
             queries.push_back("not found");
        }
        else
        {
             cin>>number;
            Map.erase(number);
        }
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int main() {
    write_responses(read_queries());
    return 0;
}
