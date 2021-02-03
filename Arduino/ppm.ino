//Author:  Owen Cocjin
//Version: 1.0
//Date:    02/02/2021
//Description:  Main code for PPM
//Notes:
//  - Lots of optimization! Specifically in isr_core
#include <Wire.h>
#include <Keyboard.h>
#include <string.h>
#include "arrows.h"
#include "menus.h"
#include "accelerometer.h"
#include "u8x8_obj.h"

//Debounce delay in milliseconds
//This also defines how quickly you can press the button
//Note that the button might bounce on falling edge! Button shouldn't be held down
#define DEBOUNCE 230
//Sensitivity of tilts
#define SNSTVTY 5000
//Starred passwords
#define PRIVACY **************

const int button=0;  //Using interrupts
//Arrow
unsigned long prev_arrow_millis;
unsigned long cur_arrow_millis;
int cur_arrow_pos;  //Current arrow position
//Debouncing
volatile unsigned long isr_millis_prev=0;
volatile unsigned long isr_millis_cur=0;
//Menu pages
int cur_page=0;
volatile int des_page=0;  //Desired
volatile bool privacy=true;  //Hides passwords from screen
volatile bool update_page=false;  //Mark the page to update if true
//Keyboard
//Keyboard (probably) uses timing to type, meaning it can't be used in an interrupt.
volatile char to_type[20];

//-------------//
//    SETUP    //
//-------------//
void setup(){
	pinMode(button, INPUT);
	//Setup all
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(button), isr_update, RISING);
	Keyboard.begin();
  u8x8.begin();
	Wire.begin();
	setupMPU();
	//Flip screen (required for desired orientation)
	u8x8.setFlipMode(1);
	//Print login
	u8x8.setFont(u8x8_font_8x13B_1x2_r);
	u8x8.clear();
	writePage(Login, false);
	//Show all arrow positions
	for(int i=0;i<sizeof(arrow_pos)/sizeof(Big_Arrow);++i){
		updateArrow(i);
		delay(100);
	}//for()
}//setup()

//------------//
//    LOOP    //
//------------//
void loop(){
	//I think u8x8 and Keyboard uses delay, which stalls the interrupt :/
	//Write a password BEFORE updating page
	if(strcmp(to_type, "")!=0){
		writePassword(to_type);
	}//if()
	//The loop must constantly check the page value to determine which page to print
	Serial.print("cur_page: ");
	Serial.print(cur_page);
	Serial.print(" | des_page: ");
	Serial.println(des_page);
	if(des_page!=cur_page||update_page){
		cur_page=des_page;
		update_page=false;
		writePage(Menu[cur_page], privacy);
	}//if()
	//Check if there is anything to write to keyboard
	//Read data from mpu6500
	getAccel();  //Gives us tilt value
	//Handle arrow
	cur_arrow_millis=millis();
	if(cur_arrow_millis-prev_arrow_millis>=150){  //Refresh rate of 100ms
		if(aRawX>=SNSTVTY){  //Up
			cur_arrow_pos=5;
		}//if()
		else if(aRawX<=-SNSTVTY){  //Down
			cur_arrow_pos=7;
		}//else if()
		else if(aRawY>=SNSTVTY){  //Left
			cur_arrow_pos=4;
		}//else if()
		else if(aRawY<=-SNSTVTY){  //Right
			cur_arrow_pos=6;
		}//else if()
		updateArrow(cur_arrow_pos);
		prev_arrow_millis=cur_arrow_millis;
	}//if()
}//loop()


//-----------------//
//    FUNCTIONS    //
//-----------------//
void isr_core(){
	/*Core code to run during interrupt*/
	//Write out password as HID
	if(cur_arrow_pos==4){
		strcpy(to_type, Menu[cur_page].content);
	}//if()
	//Flip the privacy state
	else if(cur_arrow_pos==6){
		privacy=!privacy;
		update_page=true;  //Update the current page
	}//else if
	//Read arrow_pos as des_page
	else if(cur_arrow_pos==5){
		des_page=(cur_page+pages_noof-1)%pages_noof;
	}//if()
	else if(cur_arrow_pos==7){
		des_page=(cur_page+1)%pages_noof;
	}//else if
}//isr_core()

void isr_update(){
	/*Handles interrupt.
	This function is mostly a button debounce*/
	isr_millis_cur=millis();
	if(isr_millis_cur-isr_millis_prev>DEBOUNCE){  //Debounce
		isr_millis_prev=isr_millis_cur;  //"Reset" millis counter
		//Code to execute goes here
		isr_core();
	}//if()
	//Stalls while button is held down
	while(digitalRead(button)==HIGH);
}///ISR to update arrow

void writePassword(char *p){
	/*Write password via HID*/
	//Should already be on the correct page.
	//Just write content
	writeContent("Writing...", false);
	Keyboard.println(Menu[cur_page].content);
	delay(500);
	//Display original contents when done writing
	writeContent(Menu[cur_page].content, privacy);
	//Clear to_type
	strcpy(to_type, "");
}//writePassword()
