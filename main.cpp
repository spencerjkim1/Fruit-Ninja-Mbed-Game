//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "compost_pile_public.h"
#include "fruit_public.h"
#include "player_public.h"

//For sound components
////AnalogOut DACout(p18);
//PwmOut pwmout(p26);
////PwmOut speaker(p25);

////wave_player waver(&DACout);
//SDFileSystem sd(p5, p6, p7, p8, "sd"); // mosi, miso, sck, cs

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

// ===User implementations start===
int fruit_contact(void); // iterate through fruits and see if any collided
void compost_pile_update(void);

void playSound(char * wav);
void playNotes(void);
void set_random_seed(Timer);

int main()
{
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting\n");
    MMA8452 acc(p28, p27, 100000);        // Accelerometer (sda, sdc, rate)
    acc.setBitDepth(MMA8452::BIT_DEPTH_12);
    acc.setDynamicRange(MMA8452::DYNAMIC_RANGE_4G);
    acc.setDataRate(MMA8452::RATE_100);
    // ===User implementations start===
    // Game state variables
    
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    set_random_seed(t);
 
    //pwmout.period(1.0/4000.0);
    //playSound("/sd/wavfiles/BUZZER.wav");//test the sound convert to thread
    //wait(0.1);
    //playNotes();
    
    
    //initialize functions
    compost_pile_init();
    fruit_init();
    player_init();        
    pc.printf("Initialization complete\n");
    
    while(1)
    {
        t.start();
        uLCD.baudrate(3000000); 
        // Draw fruits first
//        pc.printf("fruit_generator\n");
        fruit_generator();
        
        //Put score on screen
        // NOTE: Text is 8 pixels tall

        //pc.printf("player_fruit_draw\n");
        
        
        player_draw(0x0000FF);
        player_knife_draw();
        
        
        
        //pc.printf("Reading inputs\n");
        inputs = read_inputs();

        //pc.printf("player motions\n");
        if (inputs.b1 || inputs.ay>=0.3) player_moveUp();            
        if (inputs.b2 || inputs.ay<= -0.3) player_moveDown();                
        if (inputs.b3) player_throw();
        
        //pc.printf("compost_pile_update\n");
        compost_pile_update();
        draw_compost();
        
        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        if (is_bomb == 1) {
            pc.printf("check endgame\n");
            break;
        }
        // TODO: Check end of the game        
        //pc.printf("check endgame\n");
        if(get_compost_tallest_height() > 64){
            uLCD.cls();
            uLCD.printf("GAME OVER");
            break;
        }
        
        // TODO: Check if game won

        // Compute update time
        t.stop();
        dt = t.read_ms();
        
        if (dt < 100) wait_ms(100 - dt);
    }
    pc.printf("out of main loop\n");
    destroyList(get_fruit_list());
    
    return 0;
    // ===User implementations end===
}

// ===User implementations start===

/* This function iterate through the fruit list, checking if anyone one of them is contacting 
*  with the player's knife. Don't forget to check if the "fruit" is the bomb, since we 
*  generated bombs using the fruit_generator. 
*/
int fruit_contact(void) {
    DLinkedList *tempDLL = get_fruit_list();
    LLNode *temp = getHead(tempDLL);
    FRUIT* newFruit;
    PLAYER player = player_get_info();
    while (temp) {
        newFruit = (FRUIT*) temp->data;
        if (newFruit->status == FRUIT_ACTIVE){
            if((newFruit->box.topLeft.y <= player.knife_boundingBox.bottomRight.y) && (player.knife_boundingBox.bottomRight.y <= newFruit->box.bottomRight.y)){
                if ((newFruit->box.topLeft.x <= player.knife_boundingBox.bottomRight.x) && (player.knife_boundingBox.bottomRight.x <= newFruit->box.bottomRight.x)){
                    if (newFruit->type == 0) {
                        pc.printf("BOMB\r\n");
                        return 1;
                    }
                    newFruit->status = FRUIT_SLICED;
                    pc.printf("SLICE\r\n");
                    player_score_inc();
                    return 0;
                }
                else{
//                    newFruit->status = FRUIT_SLICED;
                    return 0;
                }
            }
            else{
//                newFruit->status = FRUIT_SLICED;
                return 0;
            }
        }
        //if ( is in Knife Bound Box) {
//            player_score_inc;
//        }
        //Change the pointer for the next one in Linked List
        temp = temp->next;
    }
}

/** Call compost_pile_update() repeatedly in your game-loop. ex: main()
    This function iterate through the fruit list. Add fruits that reach the bottom of the screen
    to the compost pile.
    @return  Number of remaining cities. You might end the game when all cities are demolished.
*/
void compost_pile_update(void){
    DLinkedList *tempDLL = get_fruit_list();
    LLNode *temp = getHead(tempDLL);
    FRUIT* newFruit;
    while(temp) {
        newFruit = (FRUIT*) temp->data;
        if ((newFruit->direction == 0) && (newFruit->box.topLeft.y > 127) && (newFruit->type != 0)) {
            int index = newFruit->box.bottomRight.x / 11;
//            pc.printf("index %d" , index);
            compost_add(index);
        }
        temp = temp->next;
    }

}

//fcn to play a wav
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
        return;
}

/* Wanna hear some annoying sounds?*/
void playNotes(void)
{
    int i;
// generate a 500Hz tone using PWM hardware output
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(3);
    speaker=0.0; // turn off audio
    wait(2);
// generate a short 150Hz tone using PWM hardware output
// something like this can be used for a button click effect for feedback
    for (i=0; i<10; i++) {
        speaker.period(1.0/150.0); // 500hz period
        speaker =0.25; //25% duty cycle - mid range volume
        wait(.02);
        speaker=0.0; // turn off audio
        wait(0.5);
    }

// sweep up in frequency by changing the PWM period
    for (i=0; i<8000; i=i+100) {
        speaker.period(1.0/float(i));
        speaker=0.25;
        wait(.1);
    }
    wait(2);

// two tone police siren effect -  two periods or two frequencies
// increase volume - by changing the PWM duty cycle
    for (i=0; i<26; i=i+2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    // decrease volume
    for (i=25; i>=0; i=i-2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    speaker =0.0;
    wait(2);
}

void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();
    uLCD.printf("Push any button to start.\n");
    while(1){
      inputs = read_inputs();
      if (inputs.b1 || inputs.b2 || inputs.b3) break;
      }
    uLCD.cls();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
    }
// ===User implementations end===
