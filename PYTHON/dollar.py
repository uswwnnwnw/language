i = input('输入数字+单位')
if i[-1]=="&":
    usd = 0.1453 * eval(i[:-1])
    print(F'{i}人民币={usd:.2f}美元')
elif i[-1]=="$":
    cny = 6.8797 * eval(i[:-1])
    print(F'{i}美元={cny:.2f}人民币')
else:
    print('输入错误')