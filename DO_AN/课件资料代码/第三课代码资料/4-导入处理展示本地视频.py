# 获取、处理、展示本地视频
# 同济子豪兄 2020-07-29

# 导入opencv-python
import cv2

# 传入本地视频
cap = cv2.VideoCapture('test.mp4')

# 校验本地视频是否捕获成功，如果未成功则输出提示
if not cap.isOpened():
    print("无法打开视频")
    exit()

# 获取视频的宽、高信息，cap.get()传入的参数可以是0-18的整数，也可以设置宽高等信息
print('WIDTH',cap.get(3))
print('HEIGHT',cap.get(4))

# 无限循环，直到触发break跳出
while True:
    # 逐帧获取视频画面，返回ret和frame
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
    # 25毫秒是恰好的，如果太小，播放速度会很快，如果太大，播放速度会很慢
    if cv2.waitKey(200) == ord('q'):
        break
    
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
