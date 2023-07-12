import sensor,image,lcd,time
import KPU as kpu
from machine import UART
from fpioa_manager import fm

# 显示屏
lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(1)     # 水平翻转
sensor.set_vflip(0)         # 垂直翻转
sensor.run(1)

# 加载模型
task = kpu.load("/sd/yolov4.kmodel")
f=open("anchors.txt","r")
anchor_txt=f.read()
L=[]  # L 为描点

for i in anchor_txt.split(","):
    L.append(float(i))

anchor=tuple(L)
f.close()

# 加载标签
f=open("lable.txt","r")
lable_txt=f.read()
lable = lable_txt.split(",")
f.close()

# 串口
fm.register(25, fm.fpioa.UART1_TX, force=True)
fm.register(24, fm.fpioa.UART1_RX, force=True)
uart_A = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096)

anchor = (0.3691, 0.2575, 0.4528, 0.4739, 0.6996, 0.5839, 0.9164, 0.9705, 2.3887, 1.7223)
sensor.set_windowing((224, 224))
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)
classes=["9","1","4","2","3","8","5","6","7" ]  # 标签







mubiao=0
t=1
ii=0
jj=0
# 识别并记录目标数字
while(t==1):
     img = sensor.snapshot()  # 拍照
     code = kpu.run_yolo2(task, img)
     lcd.display(img)
     if code:
         for i in code:
             a=img.draw_rectangle(i.rect())
             a = lcd.display(img)
             list1=list(i.rect())
             b=(list1[0]+list1[2])/2
             c=(list1[1]+list1[3])/2
             # print("物体是：",classes[i.classid()])
             # print("概率为：",100.00*i.value())
             # print("坐标为：",b,c)
             #uart_A.write(bytearray([mubiao]))
             if (int(classes[i.classid()])==mubiao or ii==0):
                #print(ii,int(classes[i.classid()]))
                if (ii==0):
                    mubiao=int(classes[i.classid()])
                ii+=1
                jj+=1
                #print(ii)
             else:
                print("AA")
                ii=0

             if(ii==10):
                t=0

             # for i in code:
                 # lcd.draw_string(i.x(), i.y(), classes[i.classid()], lcd.RED, lcd.WHITE)
                 # lcd.draw_string(i.x(), i.y()+12, '%f'%i.value(), lcd.RED, lcd.WHITE)
                 # lcd.draw_string(50, 200,str(b), lcd.RED, lcd.WHITE)
                 # lcd.draw_string(110, 200,str(c), lcd.RED, lcd.WHITE)
                 # uart_A.write(classes[i.classid()]+'\r\n')
                 # uart_A.write(str(b)+'\r\n')
                 # uart_A.write(str(c)+'\r\n')
     else:
         a = lcd.display(img)
# uart_A.deinit()
# del uart_A  # 删除变量
# a = kpu.deinit(task)

print(mubiao)
uart_A.write(bytearray([mubiao]))
uart_A.write(bytearray([mubiao]))
uart_A.write(bytearray([mubiao]))
uart_A.write(bytearray([mubiao]))
uart_A.write(bytearray([mubiao]))


while(True):
    t=0
    stm32=0
    stm32_r=0
    ii=0
    jj=0
    while(1):
         b=0
         img = sensor.snapshot()  # 拍照
         code = kpu.run_yolo2(task, img)
         if code:
             print("AAA")
             jj+=1
             for i in code:
                 print('BBB')
                 if mubiao == int(classes[i.classid()]):
                    ii+=1


             if(ii>=3):
                 stm32_r=11
                 stm32=1
                 print(11)
                 break
             elif jj>20:
                 stm32_r=10
                 stm32=1
                 print(10)
                 break
             #uart_A.write(bytearray([stm32_r]))
                 #a=img.draw_rectangle(i.rect())
                 #a = lcd.display(img)

                 # print("物体是：",classes[i.classid()])
                 # print("概率为：",100.00*i.value())
                 # print("坐标为：",b,c)
                 #for i in code:
                     #lcd.draw_string(i.x(), i.y(), classes[i.classid()], lcd.RED, lcd.WHITE)
                     #lcd.draw_string(i.x(), i.y()+12, '%f'%i.value(), lcd.RED, lcd.WHITE)
                     #lcd.draw_string(50, 200,str(b), lcd.RED, lcd.WHITE)
                     #lcd.draw_string(110, 200,str(c), lcd.RED, lcd.WHITE)
                     #uart_A.write(classes[i.classid()]+'\r\n')
                     #uart_A.write(str(b)+'\r\n')
                     #uart_A.write(str(c)+'\r\n')

            #uart_A.write(bytearray([stm32_r]))
            #a = lcd.display(img)
    if(stm32_r!=0):
        uart_A.write(bytearray([stm32_r]))
        uart_A.write(bytearray([stm32_r]))









uart_A.deinit()
del uart_A  # 删除变量
a = kpu.deinit(task)
