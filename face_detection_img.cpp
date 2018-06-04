//
//  face_detection_img.cpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#include "face_detection_img.hpp"
void face_detetion_img(const std::string imgPath, const std::string cascadeName)
{
    //bool fileOrFolder = isFileOrFolder(imgPath);
    
    std::ifstream fin;
    fin.open(imgPath);
    
    cv::CascadeClassifier cascade;
    double scale = 1.3;
    std::vector<cv::Rect> faces;
    cv::Mat gray;
    
    // --Detection
    cascade.load(cascadeName);
    std::string name;
    while (getline(fin, name)){
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        
        // Read Image
        cv::Mat_<uchar> image = cv::imread(name, 0);
        if (image.empty())
        {
            continue;
        }
        
        // Read Opencv Detection Bbx
        cv::Mat smallImg(cvRound(image.rows / scale), cvRound(image.cols / scale), CV_8UC1); //cvRound对double型数据进行四舍五入
        cv::resize(image, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
        cv::equalizeHist(smallImg, smallImg);                                              //equalizeHist提高图像的亮度和对比度
        // --Detection
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
            
            cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 3, 8);
        }
        
        cv::imshow("test", image);
        char s = cv::waitKey(0);
        if ('s' == s )
        {
            size_t pos = name.find_last_of('.');
            std::string filename = name.substr(0, pos);
            
            filename = filename + ".bmp";
            std::cout << filename << std::endl;
            cv::imwrite(filename, image);
        }
    }
    fin.close();
}  
