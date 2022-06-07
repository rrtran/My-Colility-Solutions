#include <vector>

using namespace std;

void divide(vector<int>& s, vector<int>& s1, vector<int>& s2) {
    for (int i = 0; i < s.size() / 2; i++) {
        s1.push_back(s[i]);
    }

    for (int i = s.size() / 2; i < s.size(); i++) {
        s2.push_back(s[i]);
    }

    while (s.empty() == false) {
        s.pop_back();
    }
}

void mergeSortRecur(vector<int>& s) {
    if (s.size() == 0) {
        return;
    }
    else if (s.size() == 1) {
        return;
    }
    else {
        vector<int> s1;
        vector<int> s2;
        divide(s, s1, s2);
        mergeSortRecur(s1);
        mergeSortRecur(s2);
        int i = 0;
        int j = 0;
        while (i < s1.size()) {
            if (j < s2.size()) {
                if (s1[i] < s2[j]) {
                    s.push_back(s1[i]);
                    i++;
                }
                else {
                    s.push_back(s2[j]);
                    j++;
                }
            }
            else {
                s.push_back(s1[i]);
                i++;
            }
        }
        while (j < s2.size()) {
            s.push_back(s2[j]);
            j++;
        }
    }
}

void mergeSort(vector<int>& s) {
    mergeSortRecur(s);
}

// Time complexity is O(Nlog(N))
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    mergeSort(A);

    int product = A[A.size() - 1] * A[A.size() - 2] * A[A.size() - 3];
    int product2 = A[A.size() - 1] * A[0] * A[1];
    int product3 = A[0] * A[1] * A[2];

    if (product > product2) {
        if (product > product3) {
            return product;
        }
        else {
            return product3;
        }
    }
    else if (product2 > product3) {
        if (product2 > product) {
            return product2;
        }
        else {
            return product;
        }
    }
    else {
        if (product3 > product) {
            return product3;
        }
        else {
            return product;
        }
    }
}