//
//  face_detection_video.cpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#include "face_detection_video.hpp"
void face_detetion_video(const std::string videoPath, const std::string cascadeName)
{
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened())
    {
        std::cout << "不能打开该视频文件！" << std::endl;
        return;
    }
    
    double scale = 2;
    cv::CascadeClassifier cascade;
    cascade.load(cascadeName);
    std::vector<cv::Rect> faces;
    
    double fps = cap.get(CV_CAP_PROP_FPS);  //获取帧率
    
    bool isVideoRewriteFile = true; // 是否把视频重新写入文件, 默认是false：不重新写入文件
    double dWidth = 0;
    double dHeight = 0;
    cv::Size frameSize;
    cv::VideoWriter vdWr;
    if (isVideoRewriteFile)
    {
        dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        frameSize = cv::Size(static_cast<int>(dWidth), static_cast<int>(dHeight));
        
        size_t pos = videoPath.find_last_of('.');
        std::string videoWritePath = videoPath.substr(0, pos);
        videoWritePath = videoWritePath + "_Result.avi";
        vdWr = cv::VideoWriter(videoWritePath, CV_FOURCC('M', 'J', 'P', 'G'), fps, frameSize, true);
        if (!vdWr.isOpened())
        {
            std::cout << "不能写入视频！" << std::endl;
            isVideoRewriteFile = false;
        }
    }
    
    while (1)
    {
        cv::Mat_<uchar> frame;
        bool bSuccess = cap.read(frame);
        if (!bSuccess)
        {
            break;
        }
        
        cv::Mat smallImg(cvRound(frame.rows / scale), cvRound(frame.cols / scale), CV_8UC1);  //cvRound对double型数据进行四舍五入
        cv::resize(frame, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
        cvtColor(smallImg, smallImg, CV_RGB2GRAY);
        cv::equalizeHist(smallImg, smallImg);                                                 //equalizeHist提高图像的亮度和对比度
        
        cascade.detectMultiScale(smallImg, faces,
                                 1.1, 2, 0
                                 /*|CV_HAAR_FIND_BIGGEST_OBJECT
                                  |CV_HAAR_DO_ROUGH_SEARCH*/
                                 | CV_HAAR_SCALE_IMAGE
                                 ,
                                 cv::Size(30, 30));
        
        for (std::vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++){
            cv::Rect rect(0, 0, 0, 0);
            
            rect.x = int(r->x*scale);
            rect.y = int(r->y*scale);
            rect.width = int((r->width - 1)*scale);
            rect.height = int((r->height - 1)*scale);
            
            cv::rectangle(frame, rect, cv::Scalar(0, 0, 0), 3, 8);
        }
        
        //是否把检测结果写入文件
        if (isVideoRewriteFile)
        {
            vdWr.write(frame);
        }
        
        cv::imshow("Video", frame);
        cv::waitKey((int)(1000 / fps));
        
    }
    
    cap.release();
    vdWr.release();
}  
