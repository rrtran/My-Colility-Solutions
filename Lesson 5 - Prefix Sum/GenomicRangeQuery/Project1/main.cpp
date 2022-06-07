#include <string>
#include <vector>

using namespace std;

class Node {
public:
    Node() {}
    Node(char letter, int impactFactor, int index) : letter(letter), impactFactor(impactFactor), index(index) {}
    char getLetter() { return letter; }
    int getImpactFactor() { return impactFactor; }
    int getIndex() { return index; }
    void setLetter(char letter) { this->letter = letter; }
    void setImpactFactor(int impactFactor) { this->impactFactor = impactFactor; }
    void setIndex(int index) { this->index = index; }
    ~Node() {}
private:
    char letter;
    int impactFactor;
    int index;
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
                if (s1[i].getLetter() < s2[j].getLetter()) {
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
    mergeSortRecur(s);
}

// Time complexity is O(NM) - 75%
vector<int> solution(string& S, vector<int>& P, vector<int>& Q) {
    // write your code in C++14 (g++ 6.2.0)
    vector<Node> B;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'A') {
            Node node(S[i], 1, i);
            B.push_back(node);
        }
        else if (S[i] == 'C') {
            Node node(S[i], 2, i);
            B.push_back(node);
        }
        else if (S[i] == 'G') {
            Node node(S[i], 3, i);
            B.push_back(node);
        }
        else {
            Node node(S[i], 4, i);
            B.push_back(node);
        }
    }

    mergeSort(B);

    vector<int> impactFactors;
    for (int j = 0; j < P.size(); j++) {
        int i = 0;
        bool found = false;
        while (found == false && i < B.size()) {
            if (P[j] <= B[i].getIndex() && Q[j] >= B[i].getIndex()) {
                impactFactors.push_back(B[i].getImpactFactor());
                found = true;
            }
            else {
                i++;
            }
        }
    }

    return impactFactors;
}

int main()
{

}