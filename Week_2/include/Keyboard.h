//
//  Keyboard.h
//  OpdrachtenWeek1
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//

#ifndef __OpdrachtenWeek1__Keyboard__
#define __OpdrachtenWeek1__Keyboard__

#include <iostream>
#include "Camera.h"

//bool fullScreen;
//bool rotating;

void glutSpecial(int key, int x, int y);
void glutSpecialUp(int key, int x, int y);
void glutKeyboardUp(unsigned char key, int x, int y);
void glutKeyboard(unsigned char key, int x, int y);
void glutKeyboardUp(unsigned char, int, int);
void glutKeyboard(unsigned char, int, int);
void KeyboardIdle(double const &ticks, Camera);

#endif /* defined(__OpdrachtenWeek1__Keyboard__) */
