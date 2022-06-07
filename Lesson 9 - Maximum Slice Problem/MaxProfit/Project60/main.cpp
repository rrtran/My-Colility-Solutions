#include <vector>

using namespace std;

// Time complexity is O(N) - 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    int max = 0;
    int min = 200000;
    int profit = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] > max) {
            max = A[i];
        }
        if (A[i] < min) {
            min = A[i];
        }

        int difference = A[i] - min;
        if (difference > profit) {
            profit = difference;
        }
    }

    return profit;
}