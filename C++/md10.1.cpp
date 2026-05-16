#include <iostream>           // 标准输入输出：cout, cin, cerr
#include <string>             // 字符串类 string
using namespace std;          // 使用标准命名空间，省得写 std::

// ========== 1. 单例模式：游戏配置管理器 ==========
class GameConfig {
private:
    static GameConfig* instance;    // 单例指针（这里实际没用到，是历史遗留，后面用的局部静态变量）
    string gameVersion;             // 游戏版本号
    int difficulty;                 // 游戏难度

    // 私有构造函数：外部不能 new，不能定义对象
    GameConfig() : gameVersion("0.0"), difficulty(1) {}   // 初始化列表：版本默认0.0，难度默认1
    // 私有析构函数
    ~GameConfig() {}

    // 禁止拷贝构造
    GameConfig(const GameConfig&) = delete;
    // 禁止赋值运算符
    GameConfig& operator=(const GameConfig&) = delete;

public:
    // 获取唯一实例的静态方法
    static GameConfig& getInstance() {
        static GameConfig inst;    // 局部静态变量：第一次调用时创建，之后一直存在（这也是单例的一种写法，属于懒汉但线程安全）
        return inst;               // 返回实例的引用
    }

    // 获取游戏版本
    string getGameVersion() const { return gameVersion; }
    // 设置游戏版本
    void setGameVersion(const string& v) { gameVersion = v; }

    // 获取难度
    int getDifficulty() const { return difficulty; }
    // 设置难度
    void setDifficulty(int d) { difficulty = d; }
};

// ========== 2. 工厂方法模式：角色与工厂 ==========

// 抽象产品类：所有角色的模板
class Character {
public:
    virtual ~Character() {}                    // 虚析构：保证子类对象能正确释放
    virtual void attack() = 0;                 // 纯虚函数：攻击，子类必须实现
    virtual void defend() = 0;                 // 纯虚函数：防御，子类必须实现
    virtual string getClassName() const = 0;   // 纯虚函数：返回角色类名
};

// 具体产品：战士
class Warrior : public Character {             // public 继承 Character
public:
    void attack() override {                   // 重写攻击
        cout << "战士挥动巨剑，造成 30 点伤害！" << endl;
    }
    void defend() override {                   // 重写防御
        cout << "战士举起盾牌，格挡攻击！" << endl;
    }
    string getClassName() const override { return "Warrior"; }  // 返回类名
};

// 具体产品：法师
class Mage : public Character {                // public 继承 Character
public:
    void attack() override {                   // 重写攻击
        cout << "法师释放火球术，造成 45 点伤害！" << endl;
    }
    void defend() override {                   // 重写防御
        cout << "法师展开魔法护盾，吸收伤害！" << endl;
    }
    string getClassName() const override { return "Mage"; }  // 返回类名
};

// 抽象工厂类：所有角色工厂的模板
class CharacterFactory {
public:
    virtual ~CharacterFactory() {}             // 虚析构
    virtual Character* createCharacter() = 0;  // 工厂方法：返回 Character 指针，子类负责 new 具体角色
};

// 具体工厂：战士工厂
class WarriorFactory : public CharacterFactory {
public:
    Character* createCharacter() override {    // 重写工厂方法
        return new Warrior();                  // 造一个战士对象并返回其指针
    }
};

// 具体工厂：法师工厂
class MageFactory : public CharacterFactory {
public:
    Character* createCharacter() override {    // 重写工厂方法
        return new Mage();                     // 造一个法师对象并返回其指针
    }
};

// ========== 3. 主函数 ==========
int main() {
    // 获取配置单例，并设置版本和难度
    GameConfig& config = GameConfig::getInstance();
    config.setGameVersion("1.0");
    config.setDifficulty(2);

    // 打印配置信息
    cout << "===== 游戏角色创建系统 =====" << endl;
    cout << "游戏版本: " << config.getGameVersion() << endl;
    cout << "难度等级: " << config.getDifficulty() << endl;
    cout << "============================" << endl;

    // 让用户选择角色类型
    int choice;
    cout << "选择角色 (1:战士, 2:法师): ";
    cin >> choice;

    // 工厂指针，根据选择指定具体工厂
    CharacterFactory* factory = nullptr;
    if (choice == 1) {
        factory = new WarriorFactory();    // 选战士，创建战士工厂
    } else if (choice == 2) {
        factory = new MageFactory();       // 选法师，创建法师工厂
    } else {
        cerr << "无效选择" << endl;        // 非法输入
        return 1;
    }

    // 用工厂创建角色对象
    Character* character = factory->createCharacter();

    // 输出角色信息并执行攻击、防御
    cout << "\n你选择了: " << character->getClassName() << endl;
    character->attack();
    character->defend();

    // 释放内存（先删角色，再删工厂）
    delete character;
    delete factory;

    return 0;
}
