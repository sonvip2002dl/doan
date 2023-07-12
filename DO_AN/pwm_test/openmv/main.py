##########################  哔哩哔哩 UID 373600934#####################
import sensor, image, time, pyb , json
from pid import PID
from pyb import Servo,UART

pan_servo=Servo(1)
tilt_servo=Servo(2)
pan_servo.calibration(500,2500,500)   #
tilt_servo.calibration(500,2500,500)

led_1 = pyb.LED(1)
led_2 = pyb.LED(2)
led_3 = pyb.LED(3)   #LED补光

orang_threshold = [(47, 80, 22, 98, -2, 78)]  #橙色阈值
######################################################################
pan_pid = PID(p=0.07, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
tilt_pid = PID(p=0.04, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
#pan_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID
#tilt_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID

len_flag=0
K = 90*10 #距离估算常数  直径的像素值*10
######################################################################
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(100)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
clock = time.clock()
uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)  #8位数据位，无校验位，1位停止位
######################################################################
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob
######################################################################
while(True):
    clock.tick()
    img = sensor.snapshot()
    blob = img.find_blobs(orang_threshold, pixels_threshold=200,area_threshold=300)
    led_3.on()
    led_1.on()
    led_2.on()   #三色光 进行补光
    if blob:
        for b in blob:
        #迭代找到的目标颜色区域
            b = find_max(blob)
            img.draw_cross(b.cx(), b.cy()) # cx, cy
            #img.draw_edges(b.min_corners(), color=(0,255,0))
            img.draw_rectangle(b[0:4])

            x = (int)(b.cx()/2)   #x画幅缩小  因为320大于256
            y = b.cy()
            #print('R pixel is : ',b[3])
            Lm = (b.w()+b.h())/2
            length = (int)(K/Lm)
            #print(x,length)
            data = bytearray([0xb3,0xb3,x,y,length,0x5b])  #打包要发送的数据
            uart.write(data)  #串口发送
            #print(data)

        pan_error = b.cx()-img.width()/2     #error 计算
        tilt_error = b.cy()-img.height()/2
        #print("pan_error: ", pan_error)
        pan_output=pan_pid.get_pid(pan_error,1)/2   # pid校正输出
        tilt_output=tilt_pid.get_pid(tilt_error,1)
        #print("pan_output",pan_output)
        pan_servo.angle(pan_servo.angle()+pan_output)  #注意openmv的放置方向
        tilt_servo.angle(tilt_servo.angle()+tilt_output)
    else :
        data = bytearray([0xb3,0xb3,0,0,0,0x5b])  #打包要发送的数据
        uart.write(data)  #串口发送
        #print(data)
