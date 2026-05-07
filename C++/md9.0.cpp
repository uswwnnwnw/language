#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>                     // sort, max_element, min_element
#include <numeric>                       // accumulate
#include <sstream>                       // stringstream
#include <string>
using namespace std;

int main() {
    // ---------- 1. 打开输入文件 ----------
    ifstream fin("scores.txt");          // 打开当前目录的 scores.txt
    if (!fin) {                          // 如果文件打开失败
        cerr << "错误：无法打开 scores.txt 文件！" << endl;
        return 1;                        // 异常退出
    }

    // ---------- 2. 逐行读取并解析 ----------
    vector<int> scores;                  // 存储有效成绩的 vector
    string line;                         // 存放每一行的字符串
    int skipped = 0;                     // 统计跳过的非数字行数

    while (getline(fin, line)) {         // 每次读一整行到 line
        if (line.empty()) continue;      // 忽略空行

        stringstream ss(line);          // 把该行字符串变成输入流
        int num;
        if (ss >> num) {                 // 尝试从流中提取一个整数
            scores.push_back(num);       // 成功则存入 vector
        } else {
            cerr << "警告：跳过非数字行 -> \"" << line << "\"" << endl;
            skipped++;                   // 非数字行计数+1
        }
    }
    fin.close();                         // 关闭输入文件

    // ---------- 3. 检查是否有有效数据 ----------
    if (scores.empty()) {                // vector 为空
        ofstream fout("report.txt");     // 创建输出文件
        fout << "处理结果：scores.txt 中没有有效的整数数据。" << endl;
        if (skipped > 0) {
            fout << "跳过的非数字行数：" << skipped << endl;
        }
        fout.close();
        cout << "没有有效数据，已生成报告 report.txt" << endl;
        return 0;
    }

    // ---------- 4. 计算统计值 ----------
    int sum = accumulate(scores.begin(), scores.end(), 0); // 总和
    double average = static_cast<double>(sum) / scores.size(); // 平均值
    int maxVal = *max_element(scores.begin(), scores.end());  // 最大值
    int minVal = *min_element(scores.begin(), scores.end());  // 最小值

    // ---------- 5. 降序排序 ----------
    sort(scores.begin(), scores.end(), greater<int>()); // greater<int> 实现从大到小

    // ---------- 6. 写入报告到 report.txt ----------
    ofstream fout("report.txt");
    if (!fout) {
        cerr << "错误：无法创建 report.txt 文件！" << endl;
        return 1;
    }

    fout << "========= 成绩分析报告 =========" << endl;
    fout << "有效数据数量：" << scores.size() << " 个" << endl;
    if (skipped > 0) {
        fout << "跳过的非数字行数：" << skipped << endl;
    }
    fout << "总和：" << sum << endl;
    fout << "平均分：" << average << endl;
    fout << "最高分：" << maxVal << endl;
    fout << "最低分：" << minVal << endl;
    fout << "\n降序排序后的成绩：" << endl;
    for (size_t i = 0; i < scores.size(); ++i) {
        fout << scores[i] << endl;       // 每行一个成绩
    }
    fout << "========= 报告结束 =========" << endl;
    fout.close();

    cout << "分析完成！结果已写入 report.txt" << endl;
    return 0;
}