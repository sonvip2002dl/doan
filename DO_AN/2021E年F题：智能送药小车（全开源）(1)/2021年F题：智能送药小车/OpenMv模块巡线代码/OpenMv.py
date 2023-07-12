import sensor, image, time,lcd,pyb
from pyb import UART
from pyb import Pin


                           #          T    R
#uart = UART(1, 115200)  # 串口配置 P1   P0
uart = UART(3, 115200)   #          P4   P5

p_out = Pin('P3', Pin.OUT_PP)#设置p_out为输出引脚

p_out.low()#设置p_out引脚为低

sensor.reset()  # 初始化感光原件
sensor.set_vflip(True)  # 设置为彩色
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565) # 设置为彩色
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     #警告：如果使用QVGA，可能需要几秒钟
clock = time.clock()                # 帧时间


THRESHOLD = (15, 54, 1, 52, 4, 56) # 黑暗事物的灰度阈值
FANGXIANG = (0, 30, -38, 47, -8, 27)






while(True):
    clock.tick()  # 计时
    img = sensor.snapshot().binary([THRESHOLD])  # 二值化

    # 函数返回回归后的线段对象line，有x1(), y1(), x2(), y2(), length(), theta(), rho(), magnitude()参数。
    # x1 y1 x2 y2分别代表线段的两个顶点坐标，length是线段长度，theta是线段的角度。
    # magnitude表示线性回归的效果，它是（0，+∞）范围内的一个数字，其中0代表一个圆。如果场景线性回归的越好，这个值越大。
    line = img.get_regression([(100,100)], robust = True)  # 快速线性回归


    if (line):
        # 串口发送 中点值 （循迹用）
        cent_x = line.x1()+line.x2()
        cent_x -= 80


        #blobs=img.find_blobs([FANGXIANG],roi=[2,5,15,20],merge=True,invert=1)  # 寻找色块
        #img.draw_rectangle([2,5,15,20], size=1, color=(255,255,255))
        #for blob in blobs:
            #cent_x=100

        # 交叉路口
        mag=line.magnitude()
        #print("!!!!!",mag)
        #cent_y=0
        if(mag<15):
            #cent_y=100
            p_out.high()  #设置p_out引脚为高
            pyb.delay(1)
            p_out.low()   #设置p_out引脚为低



        uart.write(bytearray([cent_x]))  # 串口发送数据
        #print(cent_x)
        #img.find_blobs([FANGXIANG],roi=[10,10,30,30],merge=True)

        #img.draw_rectangle([55,10,15,15], size=1, color=(255,255,255))

        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()


        img.draw_line(line.line(), color = 127)  # 画线
        #print(rho_err,line.magnitude(),line.theta())
        # if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            # pass
    #print("123",clock.fps())
    lcd.display(img)     #LCD显示图片
    #print()
