#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    Node() : data(0) {}
    Node(int data) : data(data) {}
    int getData() { return data; }
    int getAbsoluteValue() {
        if (data < 0)
            return data * -1;
        else
            return data;
    }
    void setData(int data) { this->data = data; }
    ~Node() {}
private:
    int data;
};

void divide(vector<Node>& s, vector<Node>& s1, vector<Node>& s2) {
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

void mergeSortRecur(vector<Node>& s) {
    if (s.size() == 0) {
        return;
    }
    else if (s.size() == 1) {
        return;
    }
    else {
        vector<Node> s1;
        vector<Node> s2;
        divide(s, s1, s2);
        mergeSortRecur(s1);
        mergeSortRecur(s2);
        int i = 0;
        int j = 0;
        while (i < s1.size()) {
            if (j < s2.size()) {
                if (s1[i].getAbsoluteValue() < s2[j].getAbsoluteValue()) {
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

void mergeSort(vector<Node>& s) {
    if (s.size() == 0) {
        return;
    }
    else if (s.size() == 1) {
        return;
    }

    mergeSortRecur(s);
}

// Time complexity is O(N * log(N))
// Score is 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<Node> B;
    for (int i = 0; i < A.size(); i++) {
        Node node(A[i]);
        B.push_back(node);
    }

    mergeSort(B);

    int a = B[B.size() - 3].getData();
    int b = B[B.size() - 2].getData();
    int c = B[B.size() - 1].getData();
    int maximalProduct = a * b * c;

    if (B.size() == 3) {
        return maximalProduct;
    }
    else {
        int index = B.size() - 3;
        for (int i = B.size() - 3; i >= 0; i--) {
            a = B[i].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
                index = i;
            }
        }
        int index2 = B.size() - 2;
        for (int j = B.size() - 2; j > index; j--) {
            b = B[j].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
                index2 = j;
            }
        }
        for (int j = index - 1; j >= 0; j--) {
            b = B[j].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
                index2 = j;
            }
        }
        for (int k = B.size() - 1; k > index2; k--) {
            c = B[k].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
            }
        }
        for (int k = index2 - 1; k > index; k--) {
            c = B[k].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
            }
        }

        for (int k = index - 1; k >= 0; k--) {
            c = B[k].getData();
            int product = a * b * c;
            if (product > maximalProduct) {
                maximalProduct = product;
            }
        }
    }
    return maximalProduct;
}