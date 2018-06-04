//
//  common.hpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#ifndef common_hpp
#define common_hpp

#include <stdio.h>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <ctime>
#include <io.h>
#include <direct.h>
//#include <cstdlib>


static const char help[] = "face detection on image:   needs image\n" \
"face detection on video:   needs video\n"  \
"face detection on camera:  needs camera\n" \
"face recognition:  needs images\n";

/*
 功能：判断该路径指向的是文件还是文件夹
 
 函数：isFileOrFolder
 
 文件返回：   0
 文件夹返回： 1
 */
bool isFileOrFolder(const std::string fileName);

#endif
