#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int A[1000];
int M, N;
vector<int> closest[2];
int current_sum = 0;

void merge(vector<int>& a, unsigned long st, unsigned long end) { // O(N)
    unsigned long mid = (st + end) / 2;
    vector<int> b;
    b.reserve(end - st);
    unsigned long i = st, j = mid;
    while (i != mid && j != end) {
        if (a[i] < a[j]) {
            b.push_back(a[i]);
            i++;
        }
        else {
            b.push_back(a[j]);
            j++;
        }
    }
    while (i != mid) {
        b.push_back(a[i]);
        ++i;
    }
    while (j != end) {
        b.push_back(a[j]);
        j++;
    }
    for (int i = st; i < end; ++i) {
        a[i] = b[i - st];
    }
}

void merge_sort(vector<int>& a, unsigned long st, unsigned long end) { // O(n*logn)
    if (end - st == 1)
        return;
    unsigned long mid = (st + end) / 2;
    merge_sort(a, st, mid);
    merge_sort(a, mid, end);

    merge(a, st, end);
}

void rec(int i, int end) {
    if (i == end) {
        if (current_sum <= M) {
            int currentIndex1 = (end - N / 2) / (N / 2);
            closest[currentIndex1].push_back(current_sum);
        }
        return;
    }
    if (current_sum > M)
        return;
    rec(i+1, end); // Do not use A[i].
    current_sum += A[i];
    rec(i+1, end); // DO use A[i].
    current_sum -= A[i];
}

int find_pair() {
    unsigned long i = closest[0].size(),
        j = closest[1].size(),
        k = 0;
    int closestVal = 0;
    while(closest[0][i] > M) {
        i--;
    }
    while(closest[1][j] > M) {
        j--;
    }
    while(i > 0 && k < j) {
        if(closest[0][i] + closest[1][j] <= M) {
            if(closest[0][i] + closest[1][j] > closestVal) {
                closestVal = closest[0][i] + closest[1][j];
            } else {
                k++;
            }
        } else {
            i--;
        }
    }
    return closestVal;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    rec(0, N / 2 + 1);
    rec(N / 2 + 1, N + 1);

    merge_sort(closest[0], 0, closest[0].size() + 1);
    merge_sort(closest[1], 0, closest[1].size() + 1);

    for (int i = 0; i <= closest[0].size(); ++i) {
        cout << closest[0][i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= closest[1].size(); ++i) {
        cout << closest[1][i] << " ";
    }

    cout << "Closest value to " << M
         << " is " << find_pair() << endl;
    return 0;
}

/*
7 17
2 4 6 8 10 12 14
*/