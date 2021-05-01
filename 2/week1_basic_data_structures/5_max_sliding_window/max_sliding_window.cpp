#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

class StackWithMax {
    std::stack<int> stack_;
    std::stack<int> max_stack_;
    public:
    void Push(int value) {
        stack_.push(value);
        if (max_stack_.empty() or max_stack_.top() <= value) 
            max_stack_.push(value);
    }

    void Pop() {
        assert(not stack_.empty());
        int value = stack_.top();
        stack_.pop();
        if(value == max_stack_.top()) max_stack_.pop();
    }
    
    int Top() {
        assert(not stack_.empty());
        return stack_.top();
    }

    int Max() const {
        assert(not stack_.empty());
        return max_stack_.top();
    }
    
    bool Empty() const {
        return stack_.empty();
    }
};

// Queue implementation using two stacks, c.f. this SO question:
//https://stackoverflow.com/questions/69192/how-to-implement-a-queue-using-two-stacks

class QueueWithMax { 
        StackWithMax inbox_;
        StackWithMax outbox_;
        
public:
        void Enqueue(int value) {
            inbox_.Push(value);
        }
        
        void Dequeue() {
            if (outbox_.Empty())
                while(not inbox_.Empty()) {
                    outbox_.Push(inbox_.Top());
                    inbox_.Pop();
                }
            outbox_.Pop();
        }
        
        int Max() { 
            if (inbox_.Empty())
                return outbox_.Max();
            if (outbox_.Empty())
                return inbox_.Max();
            return max(inbox_.Max(), outbox_.Max()); }
};

void max_sliding_window_naive(vector<int> const & A, int w) {
    QueueWithMax window;
    
    for(int i = 0; i < w; ++i) {
        window.Enqueue(A[i]);
    }
    
    for(int i = w; i < A.size(); ++i) {
        std::cout << window.Max() << " ";
        window.Dequeue();
        window.Enqueue(A[i]);
    }
    
    std::cout << window.Max() << " ";
    
    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
