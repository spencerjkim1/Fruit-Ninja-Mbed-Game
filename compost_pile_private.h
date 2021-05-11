//=================================================================
// The header file is for module "compost pile"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#ifndef COMPOST_PILE_PRIVATE_H
#define COMPOST_PILE_PRIVATE_H

#include "mbed.h"
#include "globals.h"
#include "compost_pile_public.h"

//==== [private type] ====
// N/A


//==== [private function] ====
// N/A


//==== [private macros] ====


//==== [private settings] ====
// You could modify these settings, but try to keep them be used only inside compost_pile.cpp
// Here are the settings to define the looking of your compost pile
#define COMPOST_TO_SCREEN_MARGIN 25 // pixel on the screen
#define COMPOST_WIDTH 121 // pixel on the screen
#define PILE_WIDTH 11 // pixel on the screen
#define NUM_PILE (COMPOST_WIDTH/PILE_WIDTH)
#define PILE_COLOR 0x00FF00

#endif //COMPOST_PILE_PRIVATE_H