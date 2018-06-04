//
//  common.cpp
//  facedetection
//
//  Created by aichung on 2018/6/4.
//  Copyright © 2018年 aichung. All rights reserved.
//

#include "common.hpp"


bool isFileOrFolder(const std::string fileName)
{
    const char* path = fileName.c_str();
    struct _stat buf = { 0 };
    _stat(path, &buf);
    return buf.st_mode & _S_IFDIR;
}
