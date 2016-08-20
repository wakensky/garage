#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <iostream>

template <typename T>
class SinglyLinkedList {
public:
	struct Node {
		T val;
		Node *next{nullptr};
		Node(const T &in_val) : val(in_val) { }
		Node(const Node &another) :
			val(another.val), next(another.next) { }
	};
public:
	SinglyLinkedList() :
		head_(0), z_(0) {
		head_.next = &z_;
		z_.next = &z_;
	}
	SinglyLinkedList(const SinglyLinkedList &another) = delete; // 禁止拷贝构造
	SinglyLinkedList& operator= (const SinglyLinkedList &another) = delete;  // 禁止赋值
	~SinglyLinkedList() {
		while (head_.next != &z_) {
			delete_next(&head_);
		}
	}
	void delete_next(Node *node) {
		Node *to_be_deleted = node->next;
		node->next = node->next->next;
		if (to_be_deleted != &z_) {
			delete to_be_deleted;
		}
	}
	// may throw bad_alloc if memory full
	Node *insert_after(Node *node, T val) {
		Node *new_node = new Node(val);
		new_node->next = node->next;
		node->next = new_node;
		return new_node;
	}
	Node *head() {
		return &head_;
	}
private:
	Node head_, z_;
};

int main (int argc, char **argv) {
	SinglyLinkedList<size_t> list;
	SinglyLinkedList<size_t>::Node *latest_added_node = list.insert_after(list.head(), 0);
	for (size_t i = 1; i < 10000 * 1000; ++i) {
		latest_added_node = list.insert_after(latest_added_node, i);
	}
	return 0;
}
