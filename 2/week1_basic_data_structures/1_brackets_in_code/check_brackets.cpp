#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cassert>

namespace check_brackets {
    std::unordered_map<char, char> bra_of_ket {
        {'}', '{'}, 
        {')', '('}, 
        {']', '['}
    };
    
    struct Bracket {
        Bracket(char type, int position):
            type(type),
            position(position)
        {}

        bool Matchc(char c) {
            if (type == '[' && c == ']')
                return true;
            if (type == '{' && c == '}')
                return true;
            if (type == '(' && c == ')')
                return true;
            return false;
        }

        char type;
        int position;
    };
    
    int check_brackets(std::string text) {
        
        std::stack <Bracket> bra_stack;
        for (int position = 0; position < text.length(); ++position) {
            char next = text[position];

            if (next == '(' || next == '[' || next == '{') {
                bra_stack.push(Bracket(next, position));
            }

            if (next == ')' || next == ']' || next == '}') {
                if (bra_stack.empty() or 
                    bra_of_ket[next] != bra_stack.top().type) {
                    std::cout << position + 1;
                    return 1;
                    } 
                else bra_stack.pop();
            }
        }

        if (not bra_stack.empty()) {
            std::cout << bra_stack.top().position + 1;
            return 2;
        }

        std::cout << "Success";
        return 0;
    }

} // namespace check_brackets

int main() {
    std::string text;
    getline(std::cin, text);
    

    return check_brackets::check_brackets(text);
}
