#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <algorithm>

using std::vector;
using std::priority_queue;
using std::pair;
using std::cin;
using std::cout;
using WorkerLoad = pair<int, long long>;

class Compare{
public:
    bool operator() (WorkerLoad a, WorkerLoad b) {
        if (a.second == b.second) 
            return a.first > b.first;
        else
            return a.second > b.second;
    }
};
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  
  priority_queue<WorkerLoad, vector<WorkerLoad>, Compare > busy_workers_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
        
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        
        int worker_id;
        long long starting_time;
        
        size_t num_jobs = jobs_.size();
        for (size_t i = 0; i < num_jobs; ++i) {
            worker_id = 0;
            starting_time = 0;
            if (not busy_workers_.empty()) {
                starting_time = busy_workers_.top().second;
                if (starting_time != 0 and busy_workers_.size() < num_workers_) {
                    starting_time = 0;
                    worker_id = busy_workers_.size();
                } else {
                    worker_id = busy_workers_.top().first;
                    busy_workers_.pop();
                }
            }
            
            
            assigned_workers_[i] = worker_id;
            start_times_[i] = starting_time;
            
            starting_time += jobs_[i];
            busy_workers_.push({worker_id, starting_time});
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
