//
//  face_recognition.hpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#ifndef face_recognition_hpp
#define face_recognition_hpp

#include <stdio.h>

#include "common.hpp"

void preDeal_original_img(const std::string recognitionPath, const std::string cascadeName);
std::vector<std::pair<cv::Mat, std::string >> get_CropFace_And_ImgPathName(const std::string recognitionPath, const std::string cascadeName);
bool matchFace(cv::Mat detectFace, cv::Mat dbFace);
void face_recognition(std::string recognitionPath, const std::string cascadeName);

#endif
