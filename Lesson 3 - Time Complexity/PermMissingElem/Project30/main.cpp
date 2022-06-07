
// Time complexity is O(N) or O(N * log(N))
// Score is 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    int inputSum = 0;
    for (int i = 0; i < A.size(); i++) {
        inputSum += A[i];
    }

    int sum = 0;
    for (int i = 1; i <= A.size() + 1; i++) {
        sum += i;
    }

    return sum - inputSum;
}