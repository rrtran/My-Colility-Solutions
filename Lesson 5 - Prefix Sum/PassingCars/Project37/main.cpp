// Time complexity is O(N)
// Score is 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)

    int sum = 0;
    for (int i = 0; i < A.size(); i++) {
        sum += A[i];
    }

    int count = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == 0) {
            count += sum;
        }
        else {
            sum = sum - A[i];
        }

        if (count > 1000000000) {
            return -1;
        }
    }

    return count;
}