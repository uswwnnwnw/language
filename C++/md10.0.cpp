// 文件名：main.cpp
// 一个完整的、极简的饿汉式单例日志记录器

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// ---------- 日志类 ----------
class Logger {
private:
    std::ofstream logFile;                     // 输出文件流
    static Logger instance;                    // 饿汉：唯一的实例提前造好

    Logger() {                                 // 私有构造函数
        logFile.open("app.log", std::ios::app); // 打开日志文件（追加模式）
        if (!logFile) {
            std::cerr << "无法打开日志文件！" << std::endl;
        }
    }

    ~Logger() {                                // 私有析构函数
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    // 禁止拷贝构造和赋值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 获取当前时间字符串
    std::string getCurrentTime() const {
        time_t now = time(nullptr);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return std::string(buffer);
    }

public:
    // 全局访问点：返回实例的引用
    static Logger& getInstance() {
        return instance;
    }

    // 写日志
    void log(const std::string& message) {
        std::string timeStr = getCurrentTime();
        logFile << "[" << timeStr << "] " << message << std::endl;
        std::cout << "[" << timeStr << "] " << message << std::endl;
    }
};

// ---------- 关键：定义静态成员变量（饿汉在这里干活） ----------
Logger Logger::instance;

// ---------- 主函数测试 ----------
int main() {
    Logger::getInstance().log("程序启动");
    Logger::getInstance().log("正在处理数据...");
    Logger::getInstance().log("程序结束");
    return 0;
}
