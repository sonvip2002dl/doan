from turtle import *
from random import *
from math import *
 
def tree(n,l):
    pd()
    t=cos(radians(heading()+45))/8+0.25
    pencolor(t,t,t)
    pensize(n/4)
    forward(l)
    if n>0:
        b=random()*15+shape
        c=random()*15+shape
        d=l*(random()*0.35+0.6)
        right(b)
        tree(n-1,d)        
        left(b+c)
        tree(n-1,d)        
        right(c)
    else:
        right(90)
        n=cos(radians(heading()-45))/4+0.5
        pencolor(0.5+n*0.5,0.4+n*0.4,0.4+n*0.4)
        fillcolor(0.5+n*0.5,0.4+n*0.4,0.4+n*0.4)
        begin_fill()
        circle(2)
        end_fill()
        left(90)
        if(random()>0.75):
            pu()
            #飘落
            t = heading()
            an = -40 +random()*40
            setheading(an)
            dis = int(800*random()*0.5 + 400*random()*0.3 + 200*random()*0.2)
            forward(dis)
            setheading(t)
            #画叶子
            pd()
            right(90)
            n = cos(radians(heading()-45))/4+0.5
            pencolor(0.5+n*0.5,0.4+n*0.4,0.4+n*0.4)
            circle(2)
            left(90)
            pu()
            #返回
            t=heading()
            setheading(an)
            backward(dis)
            setheading(t)
    pu()
    backward(l)
 
shape=5
 
setup(1024,576)
bgcolor(0.5,0.5,0.5)
ht()
tracer(0,0)
speed(0)
pu()
left(90)
 
zongldis=0
 
for i in range(12):
    x1=25+2*i*i
    x2=-x1
    x3=175+2*i*i
    x4=-x3
    x5=325+2*i*i
    x6=-x5
    y=80-3.4*i*i
    length=20+8*i
    
    key=6+round(i/3)
    pu()
    print('n=',str(i+1)+' ('+str(x1)+','+str(round(y))+') key='+str(key)+' l='+str(length))
    goto(x1,y)
    tree(key,length)
    goto(x2,y)
    tree(key,length)
    goto(x3,y)
    tree(key,length)
    goto(x4,y)
    tree(key,length)
    goto(x5,y)
    tree(key,length)
    goto(x6,y)
    tree(key,length)
    
done()
