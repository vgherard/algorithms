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


typedef char trie_edge_t;
typedef pair<size_t, size_t> tree_edge_t;
typedef std::tuple<> Empty;

template<class edge_t,
         class node_t = Empty,
         class leaf_t = Empty
	>
class Tree {
protected:
	class Leaf {
		leaf_t leaf_;
	public:
		Leaf (leaf_t leaf) : leaf_(leaf) {}
		leaf_t content() { return leaf_; }
	};
	class Node {
		node_t node_;
		unordered_map<edge_t, Node*> children_;
		unordered_map<edge_t, Node*> leaves_;
	public:
		// Node constructor
		Node (node_t node) : node_(node) {}

		// Access node content
		node_t content() { return node_; }

		// Find child or leaf
		bool has_child(const edge_t e) const
			{ return children_.find(e) != children_.end(); }
		bool has_leaf(const edge_t e) const
			{ return leaves_.find(e) != leaves_.end(); }

		// Add child or leaf with labeled edge
		void add_child(const edge_t e, Node* n) { children_[e] = n; }
		void add_leaf(const edge_t e, Leaf* l) { leaves_[e] = l; }

		// Access child or leaves
		Node* child (const edge_t e) { return children_[e]; }
		Node* leaf (const edge_t e) { return leaves_[e]; }
	}; // Node

	// TODO: is this repetition unavoidable?
	class Root {
		unordered_map<edge_t, Node*> children_;
		unordered_map<edge_t, Node*> leaves_;
	public:
		// Find child or leaf
		bool has_child(const edge_t e) const
		{ return children_.find(e) != children_.end(); }
		bool has_leaf(const edge_t e) const
		{ return leaves_.find(e) != leaves_.end(); }

		// Add child or leaf with labeled edge
		void add_child(const edge_t e, Node* n) { children_[e] = n; }
		void add_leaf(const edge_t e, Leaf* l) { leaves_[e] = l; }

		// Access child or leaves
		Node* child (const edge_t e) { return children_[e]; }
		Node* leaf (const edge_t e) { return leaves_[e]; }
	}; // Node

	Node* root_;
	size_t size_;
public:
	Tree ()
		: root_(new Root(root)) {}
};

class SuffixTrie : public Tree
	<char /*edges*/, size_t /*root*/, size_t /*nodes*/, size_t /*leaves*/>
	{
public:
	SuffixTrie () : Tree(0) {};
	// Return # nodes + # leaves
	size_t size() const { return root_->content(); }

};

Trie::Node* Trie::append(const string & pattern) {
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
	return current;
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

class SuffixTrie : public Trie {
public:
	void append(const string & text, size_t start_pos){
		Node* last = Trie::append(text.substr(start_pos));
		Leaf* l = new Leaf(++size_, start_pos);
		last->new_edge('$', l);
	}
	SuffixTrie (const string & text) {
		for (size_t start = 0; start < text.length(); ++start)
			append(text, start);
	}
	bool find_pattern(const string &, size_t, size_t) const;
	vector<size_t> find_matches(const string& text) const;

};

class Tree {
	class Node {
		size_t id_;
		map<tree_edge_t, Node*> edges_;
	};
};

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
