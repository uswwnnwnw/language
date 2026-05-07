#include <iostream>      // 输入输出用
#include <vector>        // 用 vector 存图书
#include <map>           // 用 map 做编号到书名的映射
#include <string>        // 用 string 类型
#include <algorithm>     // 用 sort 排序、find_if 查找
#include <iomanip>       // 用 setprecision 控制价格输出的小数位数

using namespace std;

// 1. 定义 Book 结构体
struct Book {
    int id;               // 图书编号
    string title;         // 书名
    double price;         // 价格
};

// 全局变量：所有图书存在这里
vector<Book> books;
// 编号 → 书名的映射（为了快速按编号查找）
map<int, string> idToTitle;

// 函数声明（让 main 函数知道下面有这些函数）
void addBook();
void sortAndPrint();
void findBookById();
void findBooksByPriceRange();
void showMenu();

// ========== 功能1：添加图书 ==========
void addBook() {
    Book newBook;
    
    cout << "请输入图书编号: ";
    cin >> newBook.id;
    
    // 检查编号是否已存在
    if (idToTitle.find(newBook.id) != idToTitle.end()) {
        cout << "错误：该编号已存在！" << endl;
        return;
    }
    
    cout << "请输入书名: ";
    cin.ignore();                // 忽略上一个回车
    getline(cin, newBook.title); // 允许书名带空格
    
    cout << "请输入价格: ";
    cin >> newBook.price;
    
    // 存入 vector
    books.push_back(newBook);
    // 同步存入 map（为了快速按编号查找）
    idToTitle[newBook.id] = newBook.title;
    
    cout << "添加成功！当前共有 " << books.size() << " 本书" << endl;
}

// ========== 功能2：按价格排序并输出 ==========
void sortAndPrint() {
    if (books.empty()) {
        cout << "暂无图书，请先添加！" << endl;
        return;
    }
    
    // 复制一份，排序后再打印（不改变原数据）
    vector<Book> sortedBooks = books;
    
    // 用 lambda 表达式按价格升序排序
    sort(sortedBooks.begin(), sortedBooks.end(), 
         [](const Book& a, const Book& b) {
             return a.price < b.price;  // 价格低的在前
         });
    
    // 输出表头
    cout << "\n========== 按价格排序（从低到高） ==========" << endl;
    cout << "编号\t书名\t\t价格" << endl;
    cout << "----------------------------------------" << endl;
    
    // 遍历输出
    for (const auto& book : sortedBooks) {
        cout << book.id << "\t" 
             << book.title << "\t\t"
             << "￥" << book.price << endl;
    }
    cout << "==========================================" << endl;
}

// ========== 功能3：根据编号查找书名（用 map） ==========
void findBookById() {
    if (idToTitle.empty()) {
        cout << "暂无图书，请先添加！" << endl;
        return;
    }
    
    int searchId;
    cout << "请输入要查找的图书编号: ";
    cin >> searchId;
    
    // map 的 find 方法：O(log n) 快速查找
    auto it = idToTitle.find(searchId);
    
    if (it != idToTitle.end()) {
        // 找到了，it->first 是编号，it->second 是书名
        cout << "找到图书！编号 " << it->first 
             << " 对应的书名是：《" << it->second << "》" << endl;
    } else {
        cout << "未找到编号为 " << searchId << " 的图书" << endl;
    }
}

// ========== 扩展功能：按价格范围查找（用 find_if） ==========
void findBooksByPriceRange() {
    if (books.empty()) {
        cout << "暂无图书，请先添加！" << endl;
        return;
    }
    
    double minPrice, maxPrice;
    cout << "请输入最低价格: ";
    cin >> minPrice;
    cout << "请输入最高价格: ";
    cin >> maxPrice;
    
    // 用 find_if 查找符合条件的书（需要循环找多次）
    cout << "\n价格在 " << minPrice << " ~ " << maxPrice << " 之间的图书：" << endl;
    cout << "编号\t书名\t\t价格" << endl;
    cout << "----------------------------------------" << endl;
    
    bool found = false;
    
    // 遍历所有书，找出价格在范围内的
    for (const auto& book : books) {
        if (book.price >= minPrice && book.price <= maxPrice) {
            cout << book.id << "\t" 
                 << book.title << "\t\t"
                 << "￥" << book.price << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "没有找到价格在这个范围内的图书" << endl;
    }
    cout << "==========================================" << endl;
}

// ========== 显示菜单 ==========
void showMenu() {
    cout << "\n====== 图书管理系统 ======" << endl;
    cout << "1. 添加图书" << endl;
    cout << "2. 按价格排序并显示所有图书" << endl;
    cout << "3. 根据编号查找书名（用map）" << endl;
    cout << "4. 按价格范围查找图书" << endl;
    cout << "5. 退出系统" << endl;
    cout << "==========================" << endl;
    cout << "请选择功能: ";
}

// ========== 主函数 ==========
int main() {
    int choice;
    
    // 主菜单循环
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                sortAndPrint();
                break;
            case 3:
                findBookById();
                break;
            case 4:
                findBooksByPriceRange();
                break;
            case 5:
                cout << "感谢使用，再见！" << endl;
                break;
            default:
                cout << "无效输入，请选择 1-5" << endl;
        }
        
    } while (choice != 5);  // 选择5才退出
    
    return 0;
}