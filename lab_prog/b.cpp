#include <bits/stdc++.h>

class example {
    int key;
public:
    static int count;
    example(int k) {
        key = k;
        count++;
    }
    void print() {
        std::cout << count << " " << key << "\n";
    }
    ~example() {
        count--;
    }
};

int example::count = 0;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    example* a = new example(2);
    example* b = new example(3);
    a->print();
    b->print();
    delete a;
    b->print();
    return 0;
}