// circular linked list and its application in Josephus Problem
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

template <typename T>
class CircularLinkedList {
public:
	struct Node {
		T val;
		Node *next{nullptr};
		Node (const T &in_val) : val(in_val) { }
	};
public:
	CircularLinkedList() = default;
	~CircularLinkedList();
	Node *insert_after(const T &val, Node *node = nullptr);
	void delete_next(Node *node = nullptr);

private:
	Node *reference_ptr_{nullptr};
};

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
	while (reference_ptr_) {
		delete_next();
	}
}

template <typename T>
typename CircularLinkedList<T>::Node* CircularLinkedList<T>::insert_after(const T &val, Node *node) {
	Node *new_node_ptr = new Node(val);
	if (!node && !reference_ptr_) {
		// insert into an empty circular list
		new_node_ptr->next = new_node_ptr;
		reference_ptr_ = new_node_ptr;
	} else {
		Node *current_node_ptr = node;
		if (!current_node_ptr) {
			current_node_ptr = reference_ptr_;
		}
		new_node_ptr->next = current_node_ptr->next;
		current_node_ptr->next = new_node_ptr;
	}
	return new_node_ptr;
}

template <typename T>
void CircularLinkedList<T>::delete_next(CircularLinkedList<T>::Node *node) {
	if (!reference_ptr_) return;  // empty list
	Node *current_node_ptr = node ? node : reference_ptr_;
	Node *to_be_deleted = current_node_ptr->next;

	if (to_be_deleted->next == to_be_deleted) {
		// the last node in the circular list
		reference_ptr_ = nullptr;
	} else {
		current_node_ptr->next = to_be_deleted->next;
	}
	delete to_be_deleted;
}

int main (int argc, char **argv) {
	CircularLinkedList<size_t> circular_list;
	CircularLinkedList<size_t>::Node *latest_node_ptr = circular_list.insert_after(1);
	for (size_t i = 2; i <= 9; ++i) {
		latest_node_ptr = circular_list.insert_after(i, latest_node_ptr);
	}

	std::ostringstream oss;
	latest_node_ptr = latest_node_ptr->next;
	while  (latest_node_ptr->next != latest_node_ptr) {
		for (size_t inner = 0; inner < 3; ++inner) {
			latest_node_ptr = latest_node_ptr->next;
		}
		CircularLinkedList<size_t>::Node *to_be_deleted = latest_node_ptr->next;
		CircularLinkedList<size_t>::Node *next_latest_node_ptr = to_be_deleted->next;
		oss << to_be_deleted->val << " ";
		circular_list.delete_next(latest_node_ptr);
		latest_node_ptr = next_latest_node_ptr;
	}
	oss << latest_node_ptr->val;
	std::cout << oss.str() << std::endl;
}
