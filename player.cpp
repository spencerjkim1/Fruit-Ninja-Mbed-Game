//=================================================================
// Implementation for the player module
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#include "player_private.h"

PLAYER player; // structure of player

PLAYER player_get_info(void){
    return player;
}

void player_init(void) {
    player.y = 0;                          // The y-coordinate of player current position
    player.knifeY = 0;                    // The y coordniate of the knife
    player.height = 4;                     //player height
    player.score = 0;                      // Current score
    player.knife_length = 4;
    player.knife_height = 1;
    player.knife_boundingBox.topLeft.x = 0;
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.x = player.knife_boundingBox.topLeft.x + player.knife_length;
    player.knife_boundingBox.bottomRight.y = player.knife_boundingBox.topLeft.y + player.knife_length;
    player.player_has_knife = true;   
}

void player_moveUp(void) { 
    uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, BLACK); 
    player.y -= 4;
}

void player_moveDown(void) {
    if ((player.y + player.height) < (125 - get_compost_tallest_height())) {
        uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, BLACK); 
        player.y += 4;
    }
}

void player_throw(void) { 
    if(player.player_has_knife){
        player.knife_boundingBox.topLeft.x = 0;
        player.knife_boundingBox.topLeft.y = player.y;
        player.knife_boundingBox.bottomRight.x = player.knife_boundingBox.topLeft.x + player.knife_length;
        player.knife_boundingBox.bottomRight.y = player.knife_boundingBox.topLeft.y + player.knife_height;
        player.player_has_knife = false;
//        pc.printf("THROWN KNIFE\r\n");
    }
}

void player_knife_draw(void) {
    if (!player.player_has_knife) {
        uLCD.rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.topLeft.y , player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y, BLACK);
        player.knife_boundingBox.topLeft.x+=6;
        player.knife_boundingBox.bottomRight.x+=6;
        uLCD.rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.topLeft.y , player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y, WHITE);
        player.knifeX = player.knife_boundingBox.topLeft.x;
//        pc.printf("Bottom Right: %d, %d\r\n", player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y);
    }
    if(player.knifeX >= 128){
        player_knife_return();
        player.knifeX = 0;
    }
}

void player_knife_return(void) {
    player.player_has_knife = true;
    player.knife_boundingBox.topLeft.x = 0;
    player.knife_boundingBox.topLeft.y = 0;
    player.knife_boundingBox.bottomRight.x = 0;
    player.knife_boundingBox.bottomRight.y = 0;
    
}

// ==== player_private.h implementation ====
void player_draw(int color) {
//    wait(0.1);
    uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, color);
    
    if ( player.y <= 8 ) {
            player.y = 8;
        } else if ( player.y >= 128 - player.height ) {
            player.y = 126 - player.height;
        }
    uLCD.locate(0,0);
    uLCD.printf("Score: %d", player.score);
}

void player_score_inc(void) {
    player.score += 1; 
    //Implement display score
}
