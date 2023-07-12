# 保存处理后的视频
# 同济子豪兄 2020-07-29

# 导入科学计算库numpy
import numpy as np

# 导入opencv-python
import cv2 as cv

# 获取摄像头
cap = cv.VideoCapture(0)

# 指定VideoWriter的fourCC视频编码
fourcc = cv.VideoWriter_fourcc(*'DIVX')

# 指定输出文件、fourCC视频编码、FPS帧率、画面大小
out = cv.VideoWriter('output.avi', fourcc, 20.0, (640,  480))

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("无法打开摄像头")
        break

    # 对画面帧进行处理
    # 这里是将画面翻转   
    frame = cv.flip(frame, 0)
    
    # 将处理后的画面逐帧保存至output文件中
    out.write(frame)
    # 将处理后的画面逐帧显示在窗口中
    cv.imshow('frame', frame)
    # 获取键盘按键动作，如果按下q键，就跳出循环
    if cv.waitKey(1) == ord('q'):
        break
    
# 关闭摄像头、视频保存器、窗口
cap.release()
# out.release()
cv.destroyAllWindows()
