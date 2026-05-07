name = input('输入姓名')
ps = eval(input('输入平时成绩占比:'))
qm = eval(input('输入期末成绩占比'))
chinese_ps = eval(input('输入语文平时成绩'))
chinese_qm = eval(input('输入语文期末成绩'))
math_ps = eval(input('输入数学平时成绩'))
math_qm = eval(input('输入数学期末成绩'))
english_ps = eval(input('输入英语平时成绩'))
english_qm = eval(input('输入英语期末成绩'))
chinese_cj = chinese_ps * ps + chinese_qm * qm
math_cj = math_ps * ps + math_qm * qm
english_cj = english_ps * ps + english_qm * qm
total = chinese_cj + math_cj + english_cj

title1 = '+' + '-' * 12 + '+' + '-' * 15 + '+' + '-' * 15 + '+' + '-' * 15 + '+'
title2 = '|' + 'name' .center(12) + '|' + 'chinese' .center(15) + '|' + 'math' .center(15) + 'english' .center(15) + '|'
title3 = F"|{'name':^12}|{'chiniese':^15}|{'math':^15}|{'english':^15}|{'total':^15}|"
title4 = F"|{name:^12}|{chinese_cj:^15}|{math_cj:^15}|{english_cj:^15}|{total:^15}|"

print(title1)
print(title2)
print(title4)
print(title4)
print(title1)


