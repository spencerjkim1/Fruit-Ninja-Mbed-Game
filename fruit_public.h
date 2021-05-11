//=================================================================
// The header file defining the fruit module
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
/** @file fruit_public.h */
#ifndef FRUIT_PUBLIC_H
#define FRUIT_PUBLIC_H

#include "doubly_linked_list.h"
#include "graphics.h"

typedef enum {
    FRUIT_SLICED=0,
    FRUIT_ACTIVE=1,
} FRUIT_STATUS;

typedef void (*DrawFunc)(boundingBox b);

/// The structure to store the information of a fruit
typedef struct {
    boundingBox box;
    double delta_x;         // moving unit in x dir
    double delta_y;         // moving unit in y dir
    double source;           ///< The x or y-coordinate of the fruit's origin
    double target;           ///< The x or y-coordinate of the fruit's target
    int direction;              // 0: N->S, 1: E->W, 2: W->E
    int type;                   // Orange, Banana, etc
    int tick;                  ///< The fruit's internal tick
    FRUIT_STATUS status;   ///< The fruit status, see FRUIT_STATUS
    DrawFunc draw;
} FRUIT;

/** Call fruit_init() only once at the begining of your code */
void fruit_init(void);

/** This function draw the fruits onto the screen
    Call fruit_generator() repeatedly in your game-loop. ex: main()
*/
void fruit_generator(void);

/** This function will return a linked-list of all active fruit structures.
    This can be used to modify the active fruits. Marking fruits with status
    FRUIT_SLICED will cue their erasure from the screen and removal from the
    list at the next fruit_generator() call.
*/
DLinkedList* get_fruit_list();

#endif //FRUIT_PUBLIC_H
