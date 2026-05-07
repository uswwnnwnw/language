# 模块一：核心逻辑 - 递归函数定义
def fibonacci(n):
    """
    计算第 n 个月的兔子总数
    逻辑：第 n 个月的数量 = 第 n-1 个月 + 第 n-2 个月
    """
    # 边界条件（Base Case）：第一个月和第二个月都只有 1 对兔子
    if n <= 0:
        return 0
    elif n == 1 or n == 2:
        return 1
    else:
        # 递归公式：f(n) = f(n-1) + f(n-2)
        return fibonacci(n - 1) + fibonacci(n - 2)

# 模块二：用户交互 - 输入与处理
def main():
    try:
        # 获取用户输入的月份数 n
        user_input = input("请输入您想查询的月份 n: ")
        n = int(user_input)
        
        if n < 1:
            print("月份必须是正整数，请重新运行程序。")
        else:
            # 模块三：执行计算并输出结果报告
            total_rabbits = fibonacci(n)
            print("-" * 30)
            print(f"在第 {n} 个月时，总共有 {total_rabbits} 对兔子。")
            print(f"任务报告：计算已完成，数据源于斐波那契递归方程。")
            print("-" * 30)
            
    except ValueError:
        print("错误：请输入有效的整数月份！")

# 模块四：程序入口点
if __name__ == "__main__":
    main()
