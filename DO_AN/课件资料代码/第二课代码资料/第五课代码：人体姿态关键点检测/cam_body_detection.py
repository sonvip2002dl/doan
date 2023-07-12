import cv2
import numpy as np
import openvino
# import argparse
import cv2
import numpy as np
import time

# import matplotlib.pyplot as plt
# %matplotlib inline

'''
Contains code for working with the Inference Engine.
You'll learn how to implement this code and more in
the related lesson on the topic.
'''

import os
import sys
import logging as log
from openvino.inference_engine import IENetwork, IECore

class Network:
    '''
    Load and store information for working with the Inference Engine,
    and any loaded models.
    '''

    def __init__(self):
        self.plugin = None
        self.input_blob = None
        self.exec_network = None


    def load_model(self, model, device="CPU", cpu_extension=None):
        '''
        Load the model given IR files.
        Defaults to CPU as device for use in the workspace.
        Synchronous requests made within.
        '''
        model_xml = model
        model_bin = os.path.splitext(model_xml)[0] + ".bin"

        # Initialize the plugin
        self.plugin = IECore()

        # Add a CPU extension, if applicable
        if cpu_extension and "CPU" in device:
            self.plugin.add_extension(cpu_extension, device)

        # Read the IR as a IENetwork
        # network = IENetwork(model=model_xml, weights=model_bin)
        network = self.plugin.read_network(model=model_xml, weights=model_bin)

        # Load the IENetwork into the plugin
        self.exec_network = self.plugin.load_network(network, device)

        # Get the input layer
        self.input_blob = next(iter(network.inputs))

        # Return the input shape (to determine preprocessing)
        return network.inputs[self.input_blob].shape


    def sync_inference(self, image):
        '''
        Makes a synchronous inference request, given an input image.
        '''
        self.exec_network.infer({self.input_blob: image})
        return


    def extract_output(self):
        '''
        Returns a list of the results for the output layer of the network.
        '''
        return self.exec_network.requests[0].outputs

# Create a Network for using the Inference Engine
inference_network = Network()

# CPU
n, c, h, w = inference_network.load_model('models/human-pose-estimation-0001.xml', 'CPU', None)

# 神经棒
# n, c, h, w = inference_network.load_model('models/human-pose-estimation-0001.xml', 'MYRIAD', None)

def preprocessing(input_image, height, width):
    '''
    Given an input image, height and width:
    - Resize to width and height
    - Transpose the final "channel" dimension to be first
    - Reshape the image to add a "batch" of 1 at the start 
    '''
    image = np.copy(input_image)
    image = cv2.resize(image, (width, height))
    image = image.transpose((2,0,1))
    image = image.reshape(1, 3, height, width)

    return image

def process_frame(frame):
    origin_frame = np.copy(frame)
#     image = frame
    START_TIME = time.time()
    preprocessed_image = preprocessing(frame, h, w)
    # Perform synchronous inference on the image
    inference_network.sync_inference(preprocessed_image)
    # Obtain the output of the inference request
    output = inference_network.extract_output()
    
    input_shape = frame.shape
    heatmaps = output['Mconv7_stage2_L2']
    out_heatmap = np.zeros([heatmaps.shape[1], input_shape[0], input_shape[1]])
    for j in range(len(heatmaps[0])):
        out_heatmap[j] = cv2.resize(heatmaps[0][j], input_shape[0:2][::-1])
    output = out_heatmap
    # Remove final part of output not used for heatmaps
    output = output[:-1]
    # Get only pose detections above 0.5 confidence, set to 255
    for c in range(len(output)):
        output[c] = np.where(output[c]>0.5, 255, 0)
    # Sum along the "class" axis
    # 将所有18个关键点的热力图放在一个图里
    output = np.sum(output, axis=0)
    # 获取mask，将output设置为绿色通道
    empty = np.zeros(output.shape)
    mask = np.dstack((empty, output, empty))
    
    mask /= mask.max()
    mask *= 255
    
    # Combine with original image
    assert mask.shape == origin_frame.shape
    frame = origin_frame + mask
    
    # 后处理
    frame = np.clip(frame,0,255)
    frame = frame.astype('uint8')
    # 后处理完毕
    
    FPS = 1/(time.time() - START_TIME)
    scaler = max(int(frame.shape[0] / 1000), 1)
    frame = cv2.putText(frame, 
        "FPS:{:.3f}".format(FPS), 
        (25 * scaler, 150 * scaler), cv2.FONT_HERSHEY_SIMPLEX, 
        1 * scaler, (255, 0, 0), 2 * scaler)
    
    return frame

cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)
cap.open(0)

while cap.isOpened():
    flag, frame = cap.read()
    if not flag:
        break
    key_pressed = cv2.waitKey(60)
    
    ### 对摄像头捕获的画面进行处理
    frame = process_frame(frame)
    ### 处理完毕
    cv2.imshow('body_detection',frame)
    # Break if escape key pressed
    if key_pressed == 27:
        break
    
cap.release()
cv2.destroyAllWindows()