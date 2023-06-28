#include <bits/stdc++.h>
using namespace std;

struct Task {
    int start;
    int end;
};

// 比较任务结束时间的函数
bool cmpr(const Task& a, const Task& b) {
    return a.end < b.end;
}

vector<Task> selectTasks(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), cmpr); // 按照任务的结束时间进行升序排序

    vector<Task> selectedTasks;
    selectedTasks.push_back(tasks[0]);

    int prevEndTime = tasks[0].end;

    for (size_t i = 1; i < tasks.size(); ++i) {
        if (tasks[i].start > prevEndTime) {
           
            selectedTasks.push_back(tasks[i]);
            prevEndTime = tasks[i].end;
        }
    }

    return selectedTasks;
}

int main() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<Task> tasks(m);

    int s, t, a;
    for (int i = 0; i < m; i++) {
        cin >> s >> t >> a;
        tasks[i].start = s;
        tasks[i].end = t;
    }

    vector<Task> selectedTasks = selectTasks(tasks);

    cout << selectedTasks.size();

    return 0;
}
