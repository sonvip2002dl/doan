# 载入、显示，并保存图片
# 同济子豪兄 2020-07-29

# 导入opencv-python
import cv2

# 读入本地图像文件
img = cv2.imread('logo.png')

# 在窗口中显示图像
cv2.imshow("Display window", img)

# 获取键盘按键动作，如果按下s键，就将图像保存至本地
k = cv2.waitKey(0) # 0表示永久等待键盘按键，15表示等待15毫秒

if k == ord("s"):
    cv2.imwrite("saved_img.png", img)
    
cv2.destroyAllWindows()
