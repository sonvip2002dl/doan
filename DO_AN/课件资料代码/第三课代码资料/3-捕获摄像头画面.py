# 获取、处理、展示摄像头捕获的画面
# 同济子豪兄 2020-07-29

# 导入opencv-python
import cv2

# 捕获摄像头，传入摄像头索引号，默认摄像头索引为0
cap = cv2.VideoCapture(0)

# 校验摄像头是否捕获成功，如果未成功则输出提示
if not cap.isOpened():
    print("无法打开摄像头")
    exit()

# 无限循环，直到触发break跳出
while True:
    # 获取摄像头捕获的画面帧，返回ret和frame
    # ret的True/False反映是否捕获成功，frame是画面
    ret, frame = cap.read()
    
    # 校验画面帧是否正确捕获，如果未成功则输出提示，跳出循环
    if not ret:
        print("无法获取画面帧")
        break
    
    # 对画面帧进行处理
    # 这里是将画面转为灰度图
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # 在窗口中显示处理之后的画面
    cv2.imshow('frame_window', gray)

    # 获取键盘按键动作，如果按下q键，就跳出循环
    if cv2.waitKey(1) == ord('q'):
        break
    
# 关闭摄像头
cap.release()

# 关闭所有窗口
cv2.destroyAllWindows()
