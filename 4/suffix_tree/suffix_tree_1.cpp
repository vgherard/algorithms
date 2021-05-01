#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <map>

using std::vector;
using std::pair;
using std::unordered_map;
using std::map;
using std::string;
using std::cin;
using std::cout;

typedef std::tuple<> Empty;

template<class edge_t,
         class node_t = Empty,
         class edge_hash = std::hash<edge_t>
	>
class Tree {
protected:
	class Node {
		node_t node_;
		unordered_map<edge_t, Node*, edge_hash> children_;
	public:
		// Node constructor
		Node (node_t node) : node_(node) {}

		// Access node content
		node_t content() { return node_; }

		// Find child from labeled edge
		bool has_child (const edge_t e) const
			{ return children_.find(e) != children_.end(); }

		// Number of children
		size_t n_children () const { return children_.size(); }

		// Add new child with labeled edge
		void new_child (const edge_t e, Node* n) { children_[e] = n; }

		// Access child or leaves
		Node* child (const edge_t e) { return children_[e]; }

		friend class SuffixTree;
	}; // Node

	Node* root_;
	size_t size_;
public:
	Tree (node_t root) : root_(new Node(root)) {}
}; // class Tree

// SuffixTrie with edges storing suffix characters, nodes storing nothing
class SuffixTrie : public Tree <char, Empty>
	{
	size_t text_length_;
public:
	// Append the suffix text[i:) to the trie
	void append_suffix(const string & text, size_t start) {
		Node* current = root_;
		for (size_t j = start; j < text_length_; ++j) {
			char c = text[j];
			if (current->has_child(c)) {
				current = current->child(c);
			} else {
				current->new_child(c, new Node(Empty()));
				current = current->child(c);
			}
		}
	}

	// Append all suffixes of 'text' to the trie
	SuffixTrie (const string& text)
	: Tree(Empty()), text_length_(text.length())
	{
		text_length_ = text.length();
		for (size_t i = 0; i < text_length_; ++i)
			append_suffix(text, i);
	};
	friend class SuffixTree;
}; // Class SuffixTrie

struct PairHasher {
	size_t operator() (const pair<size_t, size_t>& p) const {
		// size_t ret = p.first;
		// ret *= 2654435761U;     <--- Knuth's hash
		// return ret ^ p.second;
		size_t hash = p.first + p.second;
		hash *= hash;           // <---  Szudzik's pairing function
		hash += 3 * p.first + p.second;
		return hash / 2;
	}
};

// SuffixTree with edges storing position and length of suffix, nodes storing
// unique integer IDs
class SuffixTree : public Tree <pair<size_t, size_t>, Empty, PairHasher>
{
	size_t text_length_;
	size_t new_branch(SuffixTrie::Node* from, Node* start_node) {
		// Calculate length of suffix, i.e. second label for the edge
		// to be created
		size_t suffix_length = 1;
		while (from->n_children() == 1) {
			from = from->children_.begin()->second;
			suffix_length++;
		}

		// Create end_node
		Node* end_node = new Node(Empty());

		// Grow other branches from end_node (if any), saving the min
		// of their starting position.
		size_t m = text_length_;
		for (auto child : from->children_) {
			m = std::min(m, new_branch(child.second, end_node));
		}

		// Start position is either:
		// text_length_ - suffix_length (if suffix reaches end of text)
		// or:
		// next_start - suffix_length (otherwise)
		size_t start = m - suffix_length;

		// Create edge between start_node and end_node
		start_node->new_child({start, suffix_length}, end_node);

		// Return starting point
		return start;
	}

public:
	SuffixTree (SuffixTrie t)
	: Tree(Empty()), text_length_(t.text_length_) {
		for (auto child : t.root_->children_) {
			new_branch(child.second, root_);
		}
	}

	void suffix_list(Node* node, const string & text, vector<string>& res) {
		for (auto child : node->children_) {
			size_t start = child.first.first;
			size_t len = child.first.second;
			res.push_back(text.substr(start, len));
			suffix_list(child.second, text, res);
		}
	}

	vector<string> suffix_list(const string & text) {
		vector<string> res;
		suffix_list(root_, text, res);
		return res;
	}


}; // Class SuffixTree



int main() {
	string text;
	cin >> text;
	vector<string> res = SuffixTree(SuffixTrie(text)).suffix_list(text);
	for (const auto & x : res)
		cout << x << '\n';
	return 0;
}
