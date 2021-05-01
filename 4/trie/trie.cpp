#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;

typedef char edge_type;

class Trie {

        class Node {
                size_t id_;
                unordered_map<edge_type, Node*> edges_;
        public:
                // Node constructor
                Node (size_t id) : id_(id) {}

                bool has_edge(const edge_type label) const {
                        return edges_.find(label) != edges_.end();
                }
                void new_edge(const edge_type label, Node* n) {
                        edges_[label] = n;
                }
                Node* follow_edge (const edge_type label) {
                        return edges_[label];
                }
                void list_edges() const;
        }; // Node

        size_t size_;
        Node* root_;
public:
        Trie(const vector<string> &);
        void append(const string &);
        void list_edges() const { root_->list_edges(); }
};

void Trie::append(const string & pattern) {
        Node* current = root_;
        for (const char c : pattern) {
                if (current->has_edge(c)) {
                        current = current->follow_edge(c);
                        continue;
                } else {
                        Node* new_node = new Node(++size_);
                        current->new_edge(c, new_node);
                        current = new_node;
                }
        }
}

Trie::Trie(const vector<string> & patterns)
        : size_(0), root_(new Node(0)) {
        for (const string & pattern : patterns)
                append(pattern);
}

// Traverse the trie spanning from a node with printing in (pseudo) pre-order
void Trie::Node::list_edges() const {
        for (const auto & edge : edges_) {
                std::cout <<
                        id_ << "->" << edge.second->id_ << ":" << edge.first <<
                        '\n';
                edge.second->list_edges();
        }
}

int main() {
        size_t n;
        std::cin >> n;
        vector<string> patterns;
        for (size_t i = 0; i < n; i++) {
                string s;
                std::cin >> s;
                patterns.push_back(s);
        }

        Trie t(patterns);
        t.list_edges();

        return 0;
}
