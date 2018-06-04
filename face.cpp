//
//  face.cpp
//  Multimedia
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#include "face.hpp"
#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;

void Pic2Gray(Mat camerFrame,Mat &gray)
{
    //普通台式机3通道BGR,移动设备为4通道
    if (camerFrame.channels() == 3)
    {
        cvtColor(camerFrame, gray, CV_BGR2GRAY);
    }
    else if (camerFrame.channels() == 4)
    {
        cvtColor(camerFrame, gray, CV_BGRA2GRAY);
    }
    else
        gray = camerFrame;
}


int main()
{
    //加载Haar或LBP对象或人脸检测器
    CascadeClassifier faceDetector;
    std::string faceCascadeFilename = "haarcascade_frontalface_default.xml";
    
    //友好错误信息提示
    try{
        faceDetector.load(faceCascadeFilename);
    }
    catch (cv::Exception e){}
    if (faceDetector.empty())
    {
        std::cerr << "Face detection can't be loaded (";
        std::cerr << faceCascadeFilename << ")!" << std::endl;
        exit(1);
    }
    
    //打开摄像头
    VideoCapture camera(0);
    while (true)
    {
        Mat camerFrame;
        camera >> camerFrame;
        if (camerFrame.empty())
        {
            std::cerr << "Can't catch image in camera" << std::endl;
            getchar();
            exit(1);
        }
        Mat displayedFrame(camerFrame.size(),CV_8UC3);
        
        
        //人脸检测只试用于灰度图像
        Mat gray;
        Pic2Gray(camerFrame, gray);
        
        
        
        //直方图均匀化(改善图像的对比度和亮度)
        Mat equalizedImg;
        equalizeHist(gray, equalizedImg);
        
        //人脸检测用Cascade Classifier::detectMultiScale来进行人脸检测
        
        int flags = CASCADE_FIND_BIGGEST_OBJECT|CASCADE_DO_ROUGH_SEARCH;    //只检测脸最大的人
        //int flags = CASCADE_SCALE_IMAGE;    //检测多个人
        Size minFeatureSize(30, 30);
        float searchScaleFactor = 1.1f;
        int minNeighbors = 4;
        std::vector<Rect> faces;
        faceDetector.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);
        
        //画矩形框
        cv::Mat face;
        cv::Point text_lb;
        for (size_t i = 0; i < faces.size(); i++)
        {
            if (faces[i].height > 0 && faces[i].width > 0)
            {
                face = gray(faces[i]);
                text_lb = cv::Point(faces[i].x, faces[i].y);
                cv::rectangle(equalizedImg, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
                cv::rectangle(gray, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
                cv::rectangle(camerFrame, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
            }
        }
        
        
        imshow("Histogram homogenization", equalizedImg);
        imshow("Grayscale", gray);
        imshow("Original", camerFrame);
        
        waitKey(20);
    }
    
    getchar();
    return 0;
}
