#include <vector>

using namespace std;

void divide(vector<long>& s, vector<long>& s1, vector<long>& s2) {
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

void mergeSortRecur(vector<long>& s) {
    if (s.size() == 0) {
        return;
    }
    else if (s.size() == 1) {
        return;
    }
    else {
        vector<long> s1;
        vector<long> s2;
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

void mergeSort(vector<long>& s) {
    mergeSortRecur(s);
}

int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<long> B;
    for (int i = 0; i < A.size(); i++) {
        B.push_back((long)A[i]);
    }
    mergeSort(B);

    if (A.size() < 3)
        return 0;

    for (int i = 2; i < A.size(); i++) {
        int P = i - 2;
        int Q = i - 1;
        int R = i;

        long y1 = B[P] + B[Q];
        long y2 = B[Q] + B[R];
        long y3 = B[R] + B[P];

        bool isTriangular = true;
        if (y1 > B[R]) {
            // Do nothing
        }
        else {
            isTriangular = false;
        }

        if (y2 > B[P]) {
            // Do nothing
        }
        else {
            isTriangular = false;
        }

        if (y3 > B[Q]) {
            // Do nothing
        }
        else {
            isTriangular = false;
        }

        if (isTriangular == true) {
            return 1;
        }
    }

    return 0;
}

int main() {

}