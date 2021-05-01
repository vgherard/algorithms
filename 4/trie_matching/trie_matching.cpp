#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;
using std::cin;
using std::cout;

typedef char edge_type;

// Represent a Trie of patterns through its adjacency list
class Trie {

protected:
	class Node {
		size_t id_;
		unordered_map<edge_type, Node*> edges_;
	public:
		// Node constructor
		Node (size_t id) : id_(id) {}

		bool has_edge(const edge_type label) const {
			return edges_.find(label) != edges_.end();
		}
		bool is_leaf() const { return edges_.empty(); }
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

class PatternTrie : public Trie {
	using Trie::Trie;
public:
	bool find_pattern(const string &, size_t, size_t) const;
	vector<size_t> find_matches(const string& text) const;
};

// Check if any pattern in the trie coincides with text[start:end)
bool PatternTrie::find_pattern(const string& text, size_t start, size_t end)
	const
{
	if (root_->is_leaf())
		return false; // Handle empty trie case separately
	Node* current_node = root_;
	for(size_t i = start; i < end; ++i) {
		if (current_node->is_leaf())
			return true;
		else if (current_node->has_edge(text[i])) {
			current_node = current_node->follow_edge(text[i]);
		} else {
			return false;
		}
	}
	return current_node->is_leaf();
}

vector<size_t> PatternTrie::find_matches(const string &text) const {
	vector<size_t> res;
	// Handle empty trie case separately
	size_t len = text.length();
	for (size_t i = 0; i < len; ++i) {
		if (find_pattern(text, i, len))
			res.push_back(i);
	}
	return res;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}
	PatternTrie trie(patterns);

	vector <size_t> ans =  trie.find_matches(t);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << std::endl;
		}
	}

	return 0;
}
