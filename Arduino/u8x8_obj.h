//Author:  Owen Cocjin
//Version: 1.0
//Date:    02/02/2021
//Description:  Handles u8x8 lib stuff
//Notes:
//  - This file exists for 2 main reasons:
//    + It makes the u8x8 library global/makes importing easier
//    + Can't use the lib inside isr, probably because it uses timing, like delays
#include <U8x8lib.h>

//Define the u8x8 "object"
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

//Include any functions that use u8x8
void clearRow(int rno, int front, int back){
	/*Clears row no
	front is how many chars to ignore from start
	back is how many chars to ignore from end*/
	u8x8.setCursor(0, rno);
	for(int i=front;i<u8x8.getCols()-back; ++i){
		u8x8.setCursor(i, rno);
		u8x8.print(" ");
	}//for()
	u8x8.setCursor(0, rno);
}//clearRow()

void updateArrow(int pos){
	/*Updates the position the accelerometer is detecting*/
	u8x8.drawTile(14, 0, 2, arrow_pos[pos].top);
	u8x8.drawTile(14, 1, 2, arrow_pos[pos].bottom);
}//updateArrow()

void writeContent(char *con, bool p){
	/*Writes content to screen.
	If 'p' is true, write stars instead*/
	u8x8.noInverse();
	clearRow(2, 0, 0);
	u8x8.setCursor(1, 2);  //Add padding at front
	if(!p){
		u8x8.print(con);
	}//if()
	else{
		u8x8.print("**************");
	}//else
}//writeContent()

void writePage(Page p, bool priv){
	/*Writes formatted page to screen.
	Writes starts instead of password if priv is true*/
	writeTitle(p.title);
	writeContent(p.content, priv);
}//writePage()

void writeTitle(char *title){
	/*Writes the title of the screen*/
	u8x8.inverse();
	clearRow(0, 0, 2);
	u8x8.setCursor(1, 0);  //Add padding at front
	u8x8.print(title);
	u8x8.noInverse();
}///writeTitle()
