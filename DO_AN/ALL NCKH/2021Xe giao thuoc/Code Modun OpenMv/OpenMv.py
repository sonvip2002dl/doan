import sensor, image, time,lcd,pyb
from pyb import UART
from pyb import Pin



#uart = UART(1, 115200)
uart = UART(3, 115200)

p_out = Pin('P3', Pin.OUT_PP)

p_out.low()

sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA)
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)
clock = time.clock()


THRESHOLD = (15, 54, 1, 52, 4, 56)
FANGXIANG = (0, 30, -38, 47, -8, 27)






while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])


    line = img.get_regression([(100,100)], robust = True)


    if (line):

        cent_x = line.x1()+line.x2()
        cent_x -= 80


        #blobs=img.find_blobs([FANGXIANG],roi=[2,5,15,20],merge=True,invert=1)
        #img.draw_rectangle([2,5,15,20], size=1, color=(255,255,255))
        #for blob in blobs:
            #cent_x=100


        mag=line.magnitude()
        #print("!!!!!",mag)
        #cent_y=0
        if(mag<15):
            #cent_y=100
            p_out.high()
            pyb.delay(1)
            p_out.low()

python openmv.py
        uart.write(bytearray([cent_x]))
        #print(cent_x)
        #img.find_blobs([FANGXIANG],roi=[10,10,30,30],merge=True)

        #img.draw_rectangle([55,10,15,15], size=1, color=(255,255,255))

        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()


        img.draw_line(line.line(), color = 127)
        #print(rho_err,line.magnitude(),line.theta())
        # if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            # pass
    #print("123",clock.fps())
    lcd.display(img)
    #print()
