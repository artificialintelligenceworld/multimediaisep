//
//  main.cpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#include <iostream>

#include "common.hpp"
#include "face_detection_img.hpp"
#include "face_detection_video.hpp"
#include "face_detection_camera.hpp"
#include "face_recognition.hpp"


int main(int argc, char ** argv)
{
    
    std::string cascadeFileName = "./../haarcascade_DataBase/haarcascade_frontalface_alt.xml";
    
    //bool fileOrDir = isFileOrFolder(filePath);
    
    if (argc < 2)
    {
        printf(help);
    }
    else if (strcmp(argv[1], "face_detetion_img") == 0)
    {
        std::string imgPath = "E:/1/ImagePath.txt";
        face_detetion_img(imgPath, cascadeFileName);
    }
    else if (strcmp(argv[1], "face_detetion_video") == 0)
    {
        std::string videoPath = "E:\\DeepLeaning\\codes\\FindFaceInVideo\\VGGFace\\chengshd\\IMG_3170.mp4";
        face_detetion_video(videoPath, cascadeFileName);
    }
    else if (strcmp(argv[1], "face_detetion_camera") == 0)
    {
        face_detetion_camera(cascadeFileName);
    }
    else if (strcmp(argv[1], "face_recognition") == 0)
    {
        std::string recognitionPath = "E:/camera/Path_Images.txt";
        face_recognition(recognitionPath, cascadeFileName);
    }
    else
    {
        printf(help);
    }
    
    return 0;
}
