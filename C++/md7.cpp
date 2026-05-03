#include <iostream>
#include <stdexcept> // 用于抛出异常
#include <string>

// 模块一：类模板定义
template <typename T>
class Queue {
private:
    T* data;          // 动态数组指针，存储队列元素
    int front;        // 队头索引：指向第一个元素
    int rear;         // 队尾索引：指向下一个待插入位置
    int capacity;     // 队列总容量
    int count;        // 当前队列中的元素个数

public:
    // 模块二：构造函数 - 初始化动态数组
    Queue(int size = 100) {
        capacity = size;
        data = new T[capacity];
        front = 0;
        rear = 0;
        count = 0;
    }

    // 模块三：析构函数 - 释放内存，防止内存泄漏
    ~Queue() {
        delete[] data;
    }

    // 模块四：入队操作 (enqueue)
    void enqueue(const T& value) {
        if (count == capacity) {
            throw std::runtime_error("Queue Overflow: 队列已满！");
        }
        data[rear] = value;
        // 核心逻辑：取模运算实现循环效果
        rear = (rear + 1) % capacity; 
        count++;
    }

    // 模块五：出队操作 (dequeue)
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue Underflow: 队列为空！");
        }
        T value = data[front];
        // 核心逻辑：取模运算实现循环效果
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    // 模块六：查看队首元素 (peek)
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return data[front];
    }

    // 模块七：辅助函数 - 判断状态与获取大小
    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

// 模块八：主函数 - 测试 Queue<int> 和 Queue<string>
int main() {
    try {
        // 测试整型队列
        std::cout << "--- 测试整型队列 ---" << std::endl;
        Queue<int> intQ(5);
        intQ.enqueue(10);
        intQ.enqueue(20);
        intQ.enqueue(30);
        std::cout << "出队元素: " << intQ.dequeue() << " (期望结果: 10)" << std::endl;
        std::cout << "当前队首: " << intQ.peek() << " (期望结果: 20)" << std::endl;

        // 测试字符串队列
        std::cout << "\n--- 测试字符串队列 ---" << std::endl;
        Queue<std::string> strQ(3);
        strQ.enqueue("龙虾");
        strQ.enqueue("指挥官");
        std::cout << "出队元素: " << strQ.dequeue() << " (期望结果: 龙虾)" << std::endl;

        // 测试边界条件（队空抛出异常）
        std::cout << "\n--- 测试边界条件 ---" << std::endl;
        strQ.dequeue(); // 此时变为空
        // strQ.dequeue(); // 如果取消注释，将触发异常

    } catch (const std::exception& e) {
        std::cerr << "捕获到异常: " << e.what() << std::endl;
    }

    return 0;
}
