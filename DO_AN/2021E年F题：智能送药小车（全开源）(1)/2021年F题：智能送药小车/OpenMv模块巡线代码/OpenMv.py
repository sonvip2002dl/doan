import sensor, image, time,lcd,pyb
from pyb import UART
from pyb import Pin


                           #          T    R
#uart = UART(1, 115200)  # �������� P1   P0
uart = UART(3, 115200)   #          P4   P5

p_out = Pin('P3', Pin.OUT_PP)#����p_outΪ�������

p_out.low()#����p_out����Ϊ��

sensor.reset()  # ��ʼ���й�ԭ��
sensor.set_vflip(True)  # ����Ϊ��ɫ
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565) # ����Ϊ��ɫ
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     #���棺���ʹ��QVGA��������Ҫ������
clock = time.clock()                # ֡ʱ��


THRESHOLD = (15, 54, 1, 52, 4, 56) # �ڰ�����ĻҶ���ֵ
FANGXIANG = (0, 30, -38, 47, -8, 27)






while(True):
    clock.tick()  # ��ʱ
    img = sensor.snapshot().binary([THRESHOLD])  # ��ֵ��

    # �������ػع����߶ζ���line����x1(), y1(), x2(), y2(), length(), theta(), rho(), magnitude()������
    # x1 y1 x2 y2�ֱ�����߶ε������������꣬length���߶γ��ȣ�theta���߶εĽǶȡ�
    # magnitude��ʾ���Իع��Ч�������ǣ�0��+�ޣ���Χ�ڵ�һ�����֣�����0����һ��Բ������������Իع��Խ�ã����ֵԽ��
    line = img.get_regression([(100,100)], robust = True)  # �������Իع�


    if (line):
        # ���ڷ��� �е�ֵ ��ѭ���ã�
        cent_x = line.x1()+line.x2()
        cent_x -= 80


        #blobs=img.find_blobs([FANGXIANG],roi=[2,5,15,20],merge=True,invert=1)  # Ѱ��ɫ��
        #img.draw_rectangle([2,5,15,20], size=1, color=(255,255,255))
        #for blob in blobs:
            #cent_x=100

        # ����·��
        mag=line.magnitude()
        #print("!!!!!",mag)
        #cent_y=0
        if(mag<15):
            #cent_y=100
            p_out.high()  #����p_out����Ϊ��
            pyb.delay(1)
            p_out.low()   #����p_out����Ϊ��



        uart.write(bytearray([cent_x]))  # ���ڷ�������
        #print(cent_x)
        #img.find_blobs([FANGXIANG],roi=[10,10,30,30],merge=True)

        #img.draw_rectangle([55,10,15,15], size=1, color=(255,255,255))

        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()


        img.draw_line(line.line(), color = 127)  # ����
        #print(rho_err,line.magnitude(),line.theta())
        # if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            # pass
    #print("123",clock.fps())
    lcd.display(img)     #LCD��ʾͼƬ
    #print()
