#include <iostream>
#include <stdexcept>                     // 标准异常库，用于抛出异常
#include <string>
using namespace std;

// 定义类模板 Queue<T>
template <typename T>
class Queue {
private:
    T* data;                             // 动态数组指针，存储队列元素
    int front;                           // 队头索引，指向第一个元素
    int rear;                            // 队尾索引，指向下一个待插入位置
    int capacity;                        // 队列总容量
    int count;                           // 当前队列中的元素个数

public:
    // 构造函数：分配指定大小的动态数组，初始化各成员
    Queue(int size = 100) {              // 伪代码：默认容量100
        capacity = size;                 // 设置容量
        data = new T[capacity];          // 在堆上申请动态数组
        front = 0;                       // 队头初始为0
        rear = 0;                        // 队尾初始为0
        count = 0;                       // 元素个数初始为0
    }

    // 析构函数：释放动态数组
    ~Queue() {
        delete[] data;                   // 释放数组，防止内存泄漏
    }

    // 入队操作
    void enqueue(const T& value) {
        if (count == capacity) {         // 判断队满
            throw runtime_error("Queue Overflow: 队列已满！"); // 队满抛出异常
        }
        data[rear] = value;              // 将新元素放到队尾
        rear = (rear + 1) % capacity;    // 队尾指针后移，取模实现循环
        count++;                         // 元素个数+1
    }

    // 出队操作
    T dequeue() {
        if (isEmpty()) {                 // 判断队空
            throw runtime_error("Queue Underflow: 队列为空！"); // 队空抛出异常
        }
        T value = data[front];           // 暂存队首元素
        front = (front + 1) % capacity;  // 队头指针后移，取模实现循环
        count--;                         // 元素个数-1
        return value;                    // 返回取出的元素
    }

    // 查看队首元素
    T peek() const {
        if (isEmpty()) {                 // 判断队空
            throw runtime_error("Queue is empty!");
        }
        return data[front];              // 返回队首元素但不移除
    }

    // 判断队列是否为空
    bool isEmpty() const {
        return count == 0;               // 元素个数为0即空
    }

    // 返回当前元素个数
    int size() const {
        return count;
    }
};

int main() {
    try {
        cout << "--- 测试整型队列 ---" << endl;
        Queue<int> intQ(5);              // 实例化容量为5的int队列
        intQ.enqueue(10);                // 入队10
        intQ.enqueue(20);                // 入队20
        intQ.enqueue(30);                // 入队30
        cout << "出队元素: " << intQ.dequeue() << " (期望: 10)" << endl;
        cout << "当前队首: " << intQ.peek() << " (期望: 20)" << endl;
        cout << "队列大小: " << intQ.size() << endl;

        cout << "\n--- 测试字符串队列 ---" << endl;
        Queue<string> strQ(3);           // 实例化容量为3的string队列
        strQ.enqueue("龙虾");            // 入队字符串
        strQ.enqueue("指挥官");
        cout << "出队元素: " << strQ.dequeue() << " (期望: 龙虾)" << endl;

        cout << "\n--- 测试边界条件（队满） ---" << endl;
        Queue<int> smallQ(2);            // 容量只有2的队列
        smallQ.enqueue(1);
        smallQ.enqueue(2);
        // smallQ.enqueue(3);            // 取消注释将触发队满异常

        cout << "\n--- 测试边界条件（队空） ---" << endl;
        Queue<int> emptyQ(3);
        // emptyQ.dequeue();             // 取消注释将触发队空异常
        cout << "emptyQ 是否为空: " << (emptyQ.isEmpty() ? "是" : "否") << endl;

        cout << "\n--- 测试循环队列 ---" << endl;
        Queue<int> loopQ(3);
        loopQ.enqueue(100);
        loopQ.enqueue(200);
        cout << "出队: " << loopQ.dequeue() << endl;  // front后移
        loopQ.enqueue(300);
        loopQ.enqueue(400);              // rear绕回
        cout << "队列内容（逐个出队）: " << loopQ.dequeue() << " " 
             << loopQ.dequeue() << " " << loopQ.dequeue() << endl;
    } catch (const exception& e) {
        cerr << "捕获到异常: " << e.what() << endl;
    }
    return 0;
}