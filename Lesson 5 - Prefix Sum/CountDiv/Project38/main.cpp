// Time complexity is O(1)
// Score is 100%
int solution(int A, int B, int K) {
    // write your code in C++14 (g++ 6.2.0)
    int smallestIntegerDivisibleByK = 0;
    int i = A;
    while (i % K != 0 && i < B) {
        i++;
    }
    smallestIntegerDivisibleByK = i;

    int count = 0;
    int countB = B / K;
    int countA;
    if (smallestIntegerDivisibleByK % K == 0) {
        countA = smallestIntegerDivisibleByK / K - 1;
    }
    else {
        countA = smallestIntegerDivisibleByK / K;
    }
    count = countB - countA;

    return count;
}