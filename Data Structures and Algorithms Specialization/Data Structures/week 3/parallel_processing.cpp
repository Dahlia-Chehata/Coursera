#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using std::vector;
using std::cin;
using std::cout;
using namespace std;
class Node
{
public:
  long long priority ;
  int workerNum;
  Node(long long priority,int workerNum);
};
Node::Node(long long priority,int workerNum)
{
    this->priority=priority;
    this->workerNum=workerNum;
}
 bool operator > (Node a, Node b)
{
    if (a.priority==b.priority)
    return a.workerNum > b.workerNum;
    return a.priority >b.priority;
}

class JobQueue {
 private:
  int num_workers;
  vector<int> jobs;
  vector<int> assigned_workers;
  vector<long long> start_times;

  void WriteResponse() const {
    for (int i = 0; i < jobs.size(); ++i) {
      cout << assigned_workers[i] << " " << start_times[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers >> m;
    jobs.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs[i];
  }

  void AssignJobs() {

    assigned_workers.resize(jobs.size());
    start_times.resize(jobs.size());
    vector<long long> next_free_time(num_workers, 0);
    priority_queue < Node, vector <Node> ,greater <Node> > pq ;

    for (int i=0;i<num_workers;i++)
        pq.push(Node(0,i));

    for (int i = 0; i < jobs.size(); ++i) {
      long long duration = jobs[i];
      Node x = pq.top();
     // cout <<"priority : "<<x.priority<<"     ID : "<<x.workerNum<<endl;
      assigned_workers[i] = x.workerNum;
      start_times[i] = next_free_time[x.workerNum];
      next_free_time[x.workerNum] += duration;
      pq.pop();
      pq.push(Node(x.priority+duration,x.workerNum));
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
