class Counter {
public:
    Counter() : counter(0), maxCounter(nullptr) {}

    Counter(int* maxCounter) : counter(0), maxCounter(maxCounter) {}

    void update() {
        if (counter < *maxCounter) {
            counter = *maxCounter;
        }
    }

    int getCounter() {
        return counter;
    }

    int* getMaxCounter() {
        return maxCounter;
    }

    void setCounter(int counter) {
        this->counter = counter;
    }

    void setMaxCounter(int* maxCounter) {
        this->maxCounter = maxCounter;
    }

    ~Counter() {
        maxCounter = nullptr;
    }
private:
    int counter;
    int* maxCounter;
};


// Time complexity is O(N+M)
// Score is 100%
vector<int> solution(int N, vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    int* maxCounter = new int(0);
    vector<Counter> counters(N);
    for (int i = 0; i < N; i++) {
        counters[i].setMaxCounter(maxCounter);
    }

    int maxCounter2 = 0;
    bool maxCounterNeedsToBeUpdated = false;
    for (int i = 0; i < A.size(); i++) {
        int X = A[i];
        if (X <= N) {
            if (maxCounterNeedsToBeUpdated == true) {
                counters[X - 1].update();
            }

            counters[X - 1].setCounter(counters[X - 1].getCounter() + 1);
            if (maxCounter2 < counters[X - 1].getCounter()) {
                maxCounter2 = counters[X - 1].getCounter();
            }
        }
        else {
            maxCounterNeedsToBeUpdated = true;
            *maxCounter = maxCounter2;
        }
    }

    vector<int> resultCounters(N);
    for (int i = 0; i < counters.size(); i++) {
        counters[i].update();
        resultCounters[i] = counters[i].getCounter();
    }

    return resultCounters;
}