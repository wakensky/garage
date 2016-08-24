// stack based on singly linked list, and its application of postfix expression

#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
public:
	Stack() {
		head_.next = &z_;
		z_.next = &z_;
	}
	~Stack() {
		try {
			while (1) {
				pop();
			}
		} catch (...) {
			// do nothing
		}
	}

	void push(const T &val) {
		Node *new_node = new Node();
		new_node->next = head_.next;
		head_.next = new_node;
	}

	// throw exception on empty
	T pop() {
		if (head_.next == &z_) {
			throw std::out_of_range("stack empty");
		}
		Node *to_be_deleted = head_.next;
		head_.next = to_be_deleted->next;
		T ret = to_be_deleted->val;
		delete to_be_deleted;
		return ret;
	}
private:
	struct Node {
		T val;
		Node *next;
	};
private:
	Node head_, z_;
};

// (,),+,-,*,/,single_digit
// throw exception if infix is illegal (括号不匹配，运算符不匹配)
std::string infix_to_postfix(const std::string &infix_string) {
	std::string postfix_string;
	Stack<char> stack;
	for (const auto iter = infix_string.cbegin(); iter != infix_string.cend(); ++iter) {
		if (isdigit(*iter)) {
			postfix_string.append(*iter);
		}
	}
	return postfix_string;
}

int main (int argc, char **argv) {
	std::string infix_string;
	char opt;
	while ((opt = getopt(argc, argv, "e:")) != -1) {
		switch (opt) {
			case 'e':
				infix_string = optarg;
				break;
			default:
				break;
		};
	};

	std::string postfix_string = infix_to_postfix(infix_string);
	std::cerr << postfix_string << std::endl;
	return 0;
}
