//
//  Camera.h
//  OpdrachtenWeek1
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//

#ifndef __OpdrachtenWeek1__Camera__
#define __OpdrachtenWeek1__Camera__

#include <iostream>

class Camera
{
private:
    float eyeposVer = 1.2f; //In vertical plane: y          //Part of: camera
    float eyeposHor = 0.0f; //In horizontal plane: x and z  //Part of: camera
    float cameraCenterX = 0.0f;                             //Part of: camera
    float cameraCenterY = 0.0f;                             //Part of: camera
    float cameraCenterZ = 0.0f;                             //Part of: camera
    
public:
    Camera(void);
    float getEyeposHor(void);
    float getEyeposVer(void);
    float getCameraCenterX(void);
    float getCameraCenterY(void);
    float getCameraCenterZ(void);
    void setEyeposHor(float);
    void setEyeposVer(float);
    void setCameraCenterX(float);
    void setCameraCenterY(float);
    void setCameraCenterZ(float);
};



#endif /* defined(__OpdrachtenWeek1__Camera__) */
