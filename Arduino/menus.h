//Author:  Owen Cocjin
//Version: 1.0
//Date:    02/02/2021
//Description:  Handles menu stuff
//Notes:
//  - This is where the passwords are stored. Preferabbly the passwords will be moved elsewhere in the future...
#define COLS 16

void clearRow(int rnom, int front, int back);
void writeTitle(char *title);
void writeContent(char *content);

//struct for menu pages
struct Page{
	//The max chars per line is 15 (16 chars -1 for beginning padding)
	char title[20];
	char content[20];
};//Page

//Menu is where the passwords and titles are stored....
//Need to figure out the most secure way to store the passwords
//Maybe encode them with the login password?
Page Login={"Login", "Press button..."};
Page Menu[]={
{"Generic", "All5!t3$"},
{"Youtube", "#Movies2n8ght%"},
{"Windows VM", "Passw0rd!"},  //This is the real default pass lol!
{"Website", "5ecretPassw0rd!"}
};

//Menu size to be used by counter functions
int pages_noof=sizeof(Menu)/sizeof(Menu[0]);

//Setup login pattern here
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
