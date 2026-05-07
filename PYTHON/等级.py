score = float(input('输入成绩'))
if score < 0 or score > 100:
    print('输入错误')
elif score >=90:
    print('A')
elif score >=80 and score < 90:
    print('B')
elif score >=70 and score < 80:
    print('C')
elif score >=60 and score < 70:
    print('D')
else:
    print('不及格')
