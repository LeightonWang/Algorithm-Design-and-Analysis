#include <bits/stdc++.h>
using namespace std;

int n, k;
vector <int> a;
void read_input_data_vector()
{
    int m;
    cin >> n >> k >> m; a.resize(n);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i];
    }
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++)
    {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}

int kth_smallest(vector<int> nums, int K) {
    srand((unsigned)time(NULL));
    int size_nums = nums.size();
    int rd = (rand() % (size_nums));
    int pivot = nums[rd]; int m = 0;

    vector<int> L; vector<int> R;
    for (int i = 0; i < size_nums; i++) {
        if (nums[i] < pivot) {
            L.push_back(nums[i]);
        }
        else if (nums[i] == pivot) m++;
        else R.push_back(nums[i]);
    }

    int l = L.size(), r = R.size();
    if (K <= l) return kth_smallest(L, K);
    if (K <= l + m) return pivot;
    return kth_smallest(R, K - l - m);
}

int main() {
    read_input_data_vector();
    cout << kth_smallest(a, k);
    return 0;
}