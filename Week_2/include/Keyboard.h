//
//  Keyboard.h
//
//  Created by Guus Beckett and Julian West on 15/06/14.
//  Copyright (c) 2014 reupload.nl. All rights reserved.
//

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

void kb_init();
void kb_idle(double const &);
void kb_glutSpecial(int, int, int);
void kb_glutSpecialUp(int, int, int);
void kb_glutKeyboardUp(unsigned char, int, int);
void kb_glutKeyboard(unsigned char, int, int);

#endif
