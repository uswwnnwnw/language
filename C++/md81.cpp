#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
using namespace std;

int main() {
    // =========================
    // 1. vector 示例：动态数组
    // =========================

    vector<int> scores;

    scores.push_back(90);
    scores.push_back(85);
    scores.push_back(100);

    cout << "vector 中的分数：" << endl;

    for (int i = 0; i < scores.size(); i++) {
        cout << scores[i] << endl;
    }

    cout << "vector 第一个元素：" << scores[0] << endl;
    cout << "vector 元素个数：" << scores.size() << endl;


    // =========================
    // 2. map 示例：键值对
    // =========================

    map<string, int> ageMap;

    ageMap["张三"] = 18;
    ageMap["李四"] = 20;
    ageMap["王五"] = 19;

    cout << endl;
    cout << "map 中的姓名和年龄：" << endl;

    for (auto it = ageMap.begin(); it != ageMap.end(); it++) {
        cout << it->first << " 的年龄是 " << it->second << endl;
    }

    string targetName = "李四";

    if (ageMap.find(targetName) != ageMap.end()) {
        cout << targetName << " 存在，年龄是 " << ageMap[targetName] << endl;
    } else {
        cout << targetName << " 不存在" << endl;
    }


    // =========================
    // 3. list 示例：链表
    // =========================

    list<string> tasks;

    tasks.push_back("学习 C++");
    tasks.push_back("写作业");
    tasks.push_front("吃早餐");

    cout << endl;
    cout << "list 中的任务：" << endl;

    for (auto it = tasks.begin(); it != tasks.end(); it++) {
        cout << *it << endl;
    }

    tasks.pop_front();

    cout << "删除第一个任务后：" << endl;

    for (auto it = tasks.begin(); it != tasks.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}