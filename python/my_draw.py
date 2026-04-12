for i in range(10):
    print(f'book.douban.com/top250?star={i*25}')
import turtle as t
t.speed(i%10)
c = ['blue','red','yellow']
#x = eval(input('边数'))
for i in range(500):
    t.color(c[i%3])
    t.forward(i*2+250)
    t.left(170)
t.done()