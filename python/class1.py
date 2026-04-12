f = eval(input('输入华氏度'))
c = ((f - 32) * 5) / 9
print('%.3f华氏度=%.3f摄氏度'%(f,c))
print('{:.3f}华氏度={:.3f}摄氏度'.format(f,c))
print(f'{f:.3f}华氏度={c:.3f}摄氏度')