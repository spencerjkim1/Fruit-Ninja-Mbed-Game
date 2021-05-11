//=================================================================
// The file is for module "compost pile"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

#include "compost_pile_private.h"

COMPOST compost_record[NUM_PILE];
int tallest_pile_height;

// See the comments in compost_pile_public.h
void compost_pile_init() {
    tallest_pile_height = 0;
    for (int j = 0; j < NUM_PILE-1; j++) {
        compost_record[j].x = (j+1)*PILE_WIDTH;  
        compost_record[j].y = 128;
        compost_record[j].width = PILE_WIDTH;
        compost_record[j].height = 0;
        pc.printf("width: %d", compost_record[j].width);
    }
}

COMPOST compost_get_info(int index){
    if(index < MAX_NUM_COMPOST_PILES){
        return compost_record[index];
    }
}

void compost_add(int index) {
    compost_record[index].height+=11;
}

void draw_compost(void){
    for (int i = 0; i < NUM_PILE-1; i++) {
        uLCD.filled_rectangle(compost_record[i].x - compost_record[i].width, compost_record[i].y - compost_record[i].height, compost_record[i].x, compost_record[i].y, PILE_COLOR);
        
        if(compost_record[i].height > 0){
            
//            pc.printf("height: %d     x,y: %d,%d\r\n", compost_record[i].height, compost_record[i].x, compost_record[i].y);
        }
    }
}

int get_compost_tallest_height() {
    int tallest = 0;
    for (int i = 0; i < NUM_PILE - 1; i++) {
        if(compost_record[i].height > tallest) {
            tallest = compost_record[i].height;
        }
    }
    pc.printf("tallest: %d\r\n", tallest);
    return tallest;
}

int get_compost_height(int index) {
    return compost_record[index].height;
}