//=================================================================
// The header file defining the fruit module
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#ifndef FRUIT_PRIVATE_H
#define FRUIT_PRIVATE_H

#include "mbed.h"
#include "globals.h"
#include "fruit_public.h"

//==== [private settings] ====
int FRUIT_INTERVAL = 10;
int FRUIT_SPEED = 5;
int FRUIT_SIZE = 15;
int PLAYER_SPACE = 20;

//==== [private type] ====

//==== [private function] ====
/** Generate a random fruit and add it to the fruit DLL
*/
void fruit_create(void);
/** Iterate over all fruit and update their positions using the rate of motion
 *  and the deltaX and deltaY generated by fruit create
*/
void fruit_update_position(void);

#endif //FRUIT_PRIVATE_H

