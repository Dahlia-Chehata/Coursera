#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Request {
    Request(int arrival_time, int process_time):  //constructor
    arrival_time(arrival_time),
    process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
    size_(size),
    finish_time_()
    {}

    Response Process(const Request &request) {
        if (finish_time_.size()== size_)  //  N == S
        {
            int start_time = max (request.arrival_time,finish_time_.back());
            int finish_time = start_time + request.process_time;
            int next = finish_time_.front ();
            int difference = request.arrival_time- next;
            if (difference >=0)  // no intersection in tasks
            {
                finish_time_.pop();
                finish_time_.push(finish_time);
                return Response (false,start_time);
            }
            return Response(true,-1);
        }
        if (finish_time_.empty())
        {
            finish_time_.push(request.process_time);
            return Response(false,request.arrival_time);
        }
        int start_time = max (request.arrival_time,finish_time_.back());
        int finish_time = start_time + request.process_time;
        finish_time_.push(finish_time);
        return Response(false,start_time);
    }
private:
    int size_;
    queue <int> finish_time_;
};

vector <Request> ReadRequests() {
    vector <Request> requests;
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

vector <Response> ProcessRequests(const vector <Request> &requests, Buffer *buffer) {
    vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        cout << (responses[i].dropped ? -1 : responses[i].start_time) <<endl;
}

int main() {
    int size;
    cin >> size;
    vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
