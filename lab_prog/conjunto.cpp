#include <bits/stdc++.h>

template<class T> class Conjunto {
    std::multiset<T> st;
public:
    Conjunto() {}
    std::multiset<T> getSet() {
        return st;
    }
    Conjunto& operator += (T const &b) {
        st.insert(b);
        return *this;
    }
    Conjunto& operator += (Conjunto const &b) {
        std::multiset<T> tmp = b.getSet();
        for(T e : tmp) {
            st.insert(e);
        }
        return *this;
    }
    Conjunto& operator -= (T const &b) {
        assert(st.find(b) != st.end());
        st.erase(st.find(b));
        return *this;
    }
    Conjunto& operator -= (Conjunto const &b) {
        std::multiset<T> tmp = b.getSet();
        for(T e : tmp) {
            assert(st.find(e) != st.end());
            st.erase(st.find(e));
        }
        return *this;
    }
    Conjunto& operator *= (Conjunto const &b) {
        std::multiset<T> tmp = b.getSet(), ans;
        for(T e : tmp) {
            if(st.find(e) != st.end()) {
                ans.insert(e);
            }
        }
        st = ans;
        return *this;
    }
    T operator[](int x) const {
        assert(x >= 0 and x < st.size());
        auto itr = st.begin();
        while(x--) {
            itr++;
        }
        return *itr;
    }
    void operator ! () const {
        for(T e : st) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    operator int() {
        return (int)st.size();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}