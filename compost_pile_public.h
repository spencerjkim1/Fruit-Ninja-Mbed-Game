// =================================================================
// The header file is for module "compost pile"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
/** @file compost_pile_public.h */
#ifndef COMPOST_PILE_PUBLIC_H
#define COMPOST_PILE_PUBLIC_H

// The structure to store the information of a compost
typedef struct {
    int x;        ///< Bottom-left corner of the compost. x coordinate on the screen.
    int y;        ///< Bottom-left corner of the compost. y coordinate on the screen.
    int width;    ///< The width of the compost. The shape of the compost is a rectangle.
    int height;   ///< The height of the compost
} COMPOST;

#define MAX_NUM_COMPOST_PILES 11

/** Call compost_pile_init() only once at the begining of your code
    Initialize every compost entry in the compost_record array, and also variable tallest_pile_height.
    These two things are defined in the compost_pile.cpp
*/
void compost_pile_init();

/** Get the information of compost
    @param index The index in compost_record. It must be smaller than MAX_NUM_COMPOST_PILES.
    @return The structure of compost information
*/
COMPOST compost_get_info(int index);

/** Make a pile of compost one unit taller
    @param index The index in compost_record. It must be smaller than MAX_NUM_COMPOST_PILES.
*/
void compost_add(int index);

/** Draw all existing piles onto the screen (Iterate through the compost_record array)
    @brief You might not need to use this function, but you could still use it if you want.
*/
void draw_compost(void);

/** Get height of tallest compost pile
    @brief You will need this function to determine the end of the game
    @return height of tallest compost pile as an int
*/
int get_compost_tallest_height(void);

/** Get height of compost pile at given index
    @brief You will need this function to add fruits to compost
    @return height of tallest compost pile as an int
*/
int get_compost_height(int index);

#endif //COMPOST_PILE_PUBLIC_H