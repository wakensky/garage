#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <queue>

struct UDT {
    int field{0};
    bool operator> (const UDT& another) const {
        return field > another.field;
    }
};

int main(int argc, char **argv) {
    std::priority_queue<UDT, std::vector<UDT>, std::greater<UDT>> heap;

    for (int i = 0; i < 10; ++i) {
        UDT u;
        u.field = i;
        heap.push(u);
    }

    while (!heap.empty()) {
        std::cout << heap.top().field << std::endl;
        heap.pop();
    }
    return 0;
}
