#include<iostream>
using namespace std;

int N; int* Nums; int* cnt;

void Merge(int *nums, int l, int m, int h) {
    int i = l, j = m + 1, k = 0;
    int* temp = new int[h - l + 1];
    while (i <= m && j <= h) {
        if (nums[i] < nums[j]) {
            temp[k] = nums[i];
            cnt[nums[i] - 1] += j - m - 1; i++;
        }
        else {
            temp[k] = nums[j];
            cnt[nums[j] - 1] += m - i + 1; j++;
        }
        k++;
            
    }
    while (i <= m) {
        temp[k] = nums[i];
        cnt[nums[i] - 1] += j - m - 1; i++; k++;
    }
    while (j <= h) {
        temp[k] = nums[j];
        cnt[nums[j] - 1] += m - i + 1; j++; k++;
    }
    for (i = l, k = 0; i <= h; i++, k++)
        nums[i] = temp[k];
    delete[] temp;
}


void MergeSort(int *nums, int l, int h) {
    if (l < h) {
        int mid = (l + h) / 2;
        MergeSort(nums, l, mid);
        MergeSort(nums, mid + 1, h);
        Merge(nums, l, mid, h);
    }
}

int main() {
    cin >> N; Nums = new int[N]; cnt = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> Nums[i];
        cnt[i] = 0;
    }

    MergeSort(Nums, 0, N - 1);
    for (int i = 0; i < N; i++)
        cout << cnt[i] << " ";
    return 0;
}