import urllib
import cv2
import numpy as np


"""
    fetching url address from the user 
"""
address = raw_input("Enter IPWebCam Address: ")
default_port = ':8080'
url='http://' + address +  default_port ' /shot.jpg'


while True:



    """
        Load the image using urllib open 
        Convert the image to bytearray using numpy
        read() - reads the content of the image file
        dtype sets the datatype format for the
        uint8 is unsigned integer of 8 bits -> C 
    """ 
    imgCam=urllib.urlopen(url)
    imgByteArr=np.array(bytearray(imgCam.read()),dtype=np.uint8)


    """
        imdecode() takes in input arr buffer and a flag
         - buf is input array or vector of bytes 
         - flag of -1 loads the image as is   
    """
    img=cv2.imdecode(imgByteArr,-1)
   

    """
        display the decoded image 
    """
    cv2.imshow('IPWebcam',img)


    """
        cv::waitkey() function introduces a processing delay
        when rendering images on an active window 
    """
    if ord('q')==cv2.waitKey(10):
        exit(0)
