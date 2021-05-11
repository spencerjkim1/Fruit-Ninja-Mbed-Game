//=================================================================
// The header file for general settings for the project
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#ifndef GLOBAL_H
#define GLOBAL_H
#include "mbed.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "MMA8452.h"
#include <math.h>

// === [global object] ===
extern uLCD_4DGL uLCD;
extern Serial pc;           // USB Console output
extern wave_player waver;
extern PwmOut speaker;

typedef struct {
    int x;
    int y;
} point;
typedef struct {
    point topLeft;
    point bottomRight;
} boundingBox;

// === [global settings] ===
#define BACKGROUND_COLOR 0x000000 //black

// === [define the macro of error handle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        uLCD.printf("\nERROR:%d\n",e); \
        pc.printf("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood
#define ERROR_FRUIT_INDEX_GET_INFO      -1  // make sure your code gives the valid index for fruit_get_info()
#define ERROR_FRUIT_INDEX_UPDATE_STATUS -2  // make sure your code gives the valid index for fruit_update_status()
#define ERROR_FRUIT_SPEED               -3  // fruit speed has to be between 1 and 8
#define ERROR_FRUIT_INTERVAL            -4  // fruit interval has to be between 1 and 100
// other fruit error code ...
#define ERROR_COMPOST_NUMBER                 -11 // number of fruits is larger than MAX_NUM_COMPOST
#define ERROR_COMPOST_INDEX_GET_INFO         -12 // make sure your code gives the valid index for compost_get_info()
// DLL
#define ERROR_DLL_INSERT_HEAD             -14 // inserting into doubly linked list at head failed
#define ERROR_DLL_DELETE                  -15 // deleting node from doubly linked list failed
// other anti-fruit error code ...

#endif //GLOBAL_H
