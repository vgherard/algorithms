#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <stack>

using std::cin;
using std::string;
using std::cout;
using std::max_element;

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

    int Max() const {
        assert(not stack_.empty());
        return max_stack_.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
