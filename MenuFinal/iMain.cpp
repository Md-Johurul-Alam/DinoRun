#include "iGraphics.h"
#include "bitmap_loader.h"
#include <iostream>
#include <fstream>
using namespace std;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 720

ofstream wFile;
ifstream rFile;
int fscore,temp;
bool point = true;

/*Menu Loading*/

int load = 0;
int menu_option = 0;
int level = 0;
int counter = 0;


/*Menu Image */

char menu_image_location[][23] = { "menu\\menu.bmp", "menu\\start.bmp", "menu\\high_scores.bmp", "menu\\story.bmp", "menu\\controls.bmp", "menu\\about.bmp" };
int menu_image[7];


/*Controling Menu's 5 icon Highlighting*/
int highlight_index = 6;
int back_highlight_index = 5;
char menu_highlight_image_location[7][25] = { "menu\\highlight\\1.bmp", "menu\\highlight\\2.bmp", "menu\\highlight\\3.bmp", "menu\\highlight\\4.bmp", "menu\\highlight\\5.bmp", "menu\\highlight\\6.bmp" };
int menu_highlight_image[7];



/*declaring for pause-resume*/
int index1, index2, index3, index4;    
int paused = 0;






int back_highlight_image[6];


int player_rank = 0;
int star_image[6];
int star_index;

bool field_active = false;
int name_index = 0;




char dino[10][100] = { "w1.bmp", "w2.bmp", "w3.bmp", "w4.bmp", "w5.bmp", "w6.bmp", "w7.bmp" };
char dinoj[10][100] = { "j1.bmp", "j2.bmp", "j3.bmp", "j4.bmp", "j5.bmp", "j6.bmp", "j7.bmp" };
char dinodeath[20][100] = { "1.bmp", "1.bmp", "1.bmp", "1.bmp", "1.bmp", "2.bmp", "2.bmp", "2.bmp", "2.bmp", "2.bmp", "3.bmp", "3.bmp", "3.bmp", "3.bmp", "3.bmp", "4.bmp", "4.bmp", "4.bmp", "4.bmp", "4.bmp" };
char points[10][300] = { "zero.bmp", "one.bmp", "two.bmp", "three.bmp", "four.bmp", "five.bmp", "six.bmp", "seven.bmp", "eight.bmp", "nine.bmp" };
int deathindex =0;
int background[32][200];
int bkindex = 0;
char dinoIndex = 0;
int dinojIndex = 0;
int jflag = 0;
int dinocordinatex = 0;
int dinocordinatey = 100;
int dinocordinateJump = 0;
int score = 0;
int obx = SCREEN_WIDTH;
int oby = 100;
int obstacle;
bool isCollison = false;
bool jumpMusic = false;
bool menuMusic = true;
int obspeed=0;
int obspeedControl = 100;
void saveScore();
void highScore();
void GameOverScore(int num);
void MenuHighScore(int num);
void GameOverHighScore(int num);
int HScore;

void showMenu()
{
	//cout << "Menu codes running!" << endl;

	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menu_image[menu_option]); /*Shows all the menu pages from an arry of images.
																			The image index changes due to calling int selectOption() from void iMouse().*/

	if (menu_option == 0 && highlight_index <= 5 && highlight_index >= 0)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menu_highlight_image[highlight_index]);
	}

	if (menu_option >= 1 && menu_option <= 5 && back_highlight_index >= 0 && back_highlight_index <= 4)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, back_highlight_image[back_highlight_index]);
	}

}
int collison(){

	if (isCollison == true){
		deathindex++;
		///counter++;
		if (deathindex > 19){
			deathindex = 0;
			isCollison = false;
			load = 0;
			////menu_option = 0;
		} iShowBMP2(dinocordinatex, dinocordinatey, dinodeath[deathindex], 0);
		
	}
	return 1;
}



void show(long int a)
{
	char p[1000];
	long int i, rem, count = 0, f;
	f = a;
	while (f != 0) {
		count++;
		f /= 10;
	}
	for (i = 0; i < count; i++) {
		rem = a % 10;
		a = a / 10;
		p[count - (i + 1)] = rem + '0';
	}
	p[count] = '\0';
	for (int i = 0; i < count; i++){
		if (p[i] == '0'){
			iShowBMP2((500 + (i * 65)), 600, "zero.bmp", 0);
		}
		else if (p[i] == '1'){
			iShowBMP2((500 + (i * 65)), 600, "one.bmp", 0);
		}
		else if (p[i] == '2'){
			iShowBMP2((500 + (i * 65)), 600, "two.bmp", 0);
		}
		else if (p[i] == '3'){
			iShowBMP2((500 + (i * 65)), 600, "three.bmp", 0);
		}
		else if (p[i] == '4'){
			iShowBMP2((500 + (i * 65)), 600, "four.bmp", 0);
		}
		else if (p[i] == '5'){
			iShowBMP2((500 + (i * 65)), 600, "five.bmp", 0);
		}
		else if (p[i] == '6'){
			iShowBMP2((500 + (i * 65)), 600, "six.bmp", 0);
		}
		else if (p[i] == '7'){
			iShowBMP2((500 + (i * 65)), 600, "seven.bmp", 0);
		}
		else if (p[i] == '8'){
			iShowBMP2((500 + (i * 65)), 600, "eight.bmp", 0);
		}
		else if (p[i] == '9'){
			iShowBMP2((500 + (i * 65)), 600, "nine.bmp", 0);
		}
		

	}
}





void iDraw()
{
	iClear();

	/*_____________________________________________________Showing menu pages._________________________________________________________*/

	if (menu_option >= 0 && menu_option <= 5)
	{
		
		showMenu(); //This function runs all the codes for menu.
		menuMusic = true;
		if (menu_option == 2){
			highScore();
			MenuHighScore(fscore);
		}
	}
	else if (load == 1){
		iShowImage(0, 0, 1366, 720, background[bkindex][200]);
		if (dinocordinatex + 50 > obx && dinocordinatey + dinocordinateJump <= 130){
			isCollison = true;
			HScore = score;
		}

		///Dinosaur
		if (isCollison == false){
			if (jflag == 0){
				iShowBMP2(dinocordinatex, dinocordinatey, dino[dinoIndex], 0);
			}
			else if (jflag == 1){
				iShowBMP2(dinocordinatex, dinocordinatey + dinocordinateJump, dinoj[dinojIndex], 0);

			}
		}
		else {
			collison();			

			
			
			
		}
		


		///obstacle
		///iShowImage(obx, oby, 60, 60, obstacle);
		iShowBMP2(obx, oby, "obstacle.bmp", 0);

		///Score
		iShowBMP2(200,570,"score.bmp", 0);
		iSetColor(255, 0, 0);
		show(score);

		




	}
	else if (load == 0){
		iShowBMP2(0, 0, "gameOver.bmp", 0);

		highScore();
		
		GameOverScore(HScore);
		GameOverHighScore(fscore);
	}
	
	
	

	///printf("%d\n",score);
}

void GameOverScore(int num){
	int replacenum = num;
	int digit1 = replacenum % 10;
	int digit2 = (replacenum / 10) % 10;
	int digit3 = (replacenum / 100) % 10;
	int digit4 = (replacenum / 1000) % 10;
	int digit5 = (replacenum / 10000) % 10;

	///////////////////////////////////////////////////
	switch (digit1) {
	case 0:
		iShowBMP2(970, 390, points[0], 0);
		break;
	case 1:
		iShowBMP2(970, 390, points[1], 0);
		break;
	case 2:
		iShowBMP2(970, 390, points[2], 0);
		break;
	case 3:
		iShowBMP2(970, 390, points[3], 0);
		break;
	case 4:
		iShowBMP2(970, 390, points[4], 0);
		break;
	case 5:
		iShowBMP2(970, 390, points[5], 0);
		break;
	case 6:
		iShowBMP2(970, 390, points[6], 0);
		break;
	case 7:
		iShowBMP2(970, 390, points[7], 0);
		break;
	case 8:
		iShowBMP2(970, 390, points[8], 0);
		break;
	case 9:
		iShowBMP2(970, 390, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit2) {
	case 0:
		iShowBMP2(900, 390, points[0], 0);
		break;
	case 1:
		iShowBMP2(900, 390, points[1], 0);
		break;
	case 2:
		iShowBMP2(900, 390, points[2], 0);
		break;
	case 3:
		iShowBMP2(900, 390, points[3], 0);
		break;
	case 4:
		iShowBMP2(900, 390, points[4], 0);
		break;
	case 5:
		iShowBMP2(900, 390, points[5], 0);
		break;
	case 6:
		iShowBMP2(900, 390, points[6], 0);
		break;
	case 7:
		iShowBMP2(900, 390, points[7], 0);
		break;
	case 8:
		iShowBMP2(900, 390, points[8], 0);
		break;
	case 9:
		iShowBMP2(900, 390, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	//////////////////////////////////////////////
	switch (digit3) {
	case 0:
		iShowBMP2(830, 390, points[0], 0);
		break;
	case 1:
		iShowBMP2(830, 390, points[1], 0);
		break;
	case 2:
		iShowBMP2(830, 390, points[2], 0);
		break;
	case 3:
		iShowBMP2(830, 390, points[3], 0);
		break;
	case 4:
		iShowBMP2(830, 390, points[4], 0);
		break;
	case 5:
		iShowBMP2(830, 390, points[5], 0);
		break;
	case 6:
		iShowBMP2(830, 390, points[6], 0);
		break;
	case 7:
		iShowBMP2(830, 390, points[7], 0);
		break;
	case 8:
		iShowBMP2(830, 390, points[8], 0);
		break;
	case 9:
		iShowBMP2(830, 390, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit4) {
	case 0:
		iShowBMP2(760, 390, points[0], 0);
		break;
	case 1:
		iShowBMP2(760, 390, points[1], 0);
		break;
	case 2:
		iShowBMP2(760, 390, points[2], 0);
		break;
	case 3:
		iShowBMP2(760, 390, points[3], 0);
		break;
	case 4:
		iShowBMP2(760, 390, points[4], 0);
		break;
	case 5:
		iShowBMP2(760, 390, points[5], 0);
		break;
	case 6:
		iShowBMP2(760, 390, points[6], 0);
		break;
	case 7:
		iShowBMP2(760, 390, points[7], 0);
		break;
	case 8:
		iShowBMP2(760, 390, points[8], 0);
		break;
	case 9:
		iShowBMP2(760, 390, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	///////////////////////////////////////////////////
	switch (digit5) {
	case 0:
		iShowBMP2(690, 390, points[0], 0);
		break;
	case 1:
		iShowBMP2(690, 390, points[1], 0);
		break;
	case 2:
		iShowBMP2(690, 390, points[2], 0);
		break;
	case 3:
		iShowBMP2(690, 390, points[3], 0);
		break;
	case 4:
		iShowBMP2(690, 390, points[4], 0);
		break;
	case 5:
		iShowBMP2(690, 390, points[5], 0);
		break;
	case 6:
		iShowBMP2(690, 390, points[6], 0);
		break;
	case 7:
		iShowBMP2(690, 390, points[7], 0);
		break;
	case 8:
		iShowBMP2(690, 390, points[8], 0);
		break;
	case 9:
		iShowBMP2(690, 390, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}



}


void GameOverHighScore(int num){
	int replacenum = num;
	int digit1 = replacenum % 10;
	int digit2 = (replacenum / 10) % 10;
	int digit3 = (replacenum / 100) % 10;
	int digit4 = (replacenum / 1000) % 10;
	int digit5 = (replacenum / 10000) % 10;

	///////////////////////////////////////////////////
	switch (digit1) {
	case 0:
		iShowBMP2(970, 265, points[0], 0);
		break;
	case 1:
		iShowBMP2(970, 265, points[1], 0);
		break;
	case 2:
		iShowBMP2(970, 265, points[2], 0);
		break;
	case 3:
		iShowBMP2(970, 265, points[3], 0);
		break;
	case 4:
		iShowBMP2(970, 265, points[4], 0);
		break;
	case 5:
		iShowBMP2(970, 265, points[5], 0);
		break;
	case 6:
		iShowBMP2(970, 265, points[6], 0);
		break;
	case 7:
		iShowBMP2(970, 265, points[7], 0);
		break;
	case 8:
		iShowBMP2(970, 265, points[8], 0);
		break;
	case 9:
		iShowBMP2(970, 265, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit2) {
	case 0:
		iShowBMP2(900, 265, points[0], 0);
		break;
	case 1:
		iShowBMP2(900, 265, points[1], 0);
		break;
	case 2:
		iShowBMP2(900, 265, points[2], 0);
		break;
	case 3:
		iShowBMP2(900, 265, points[3], 0);
		break;
	case 4:
		iShowBMP2(900, 265, points[4], 0);
		break;
	case 5:
		iShowBMP2(900, 265, points[5], 0);
		break;
	case 6:
		iShowBMP2(900, 265, points[6], 0);
		break;
	case 7:
		iShowBMP2(900, 265, points[7], 0);
		break;
	case 8:
		iShowBMP2(900, 265, points[8], 0);
		break;
	case 9:
		iShowBMP2(900, 265, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	//////////////////////////////////////////////
	switch (digit3) {
	case 0:
		iShowBMP2(830, 265, points[0], 0);
		break;
	case 1:
		iShowBMP2(830, 265, points[1], 0);
		break;
	case 2:
		iShowBMP2(830, 265, points[2], 0);
		break;
	case 3:
		iShowBMP2(830, 265, points[3], 0);
		break;
	case 4:
		iShowBMP2(830, 265, points[4], 0);
		break;
	case 5:
		iShowBMP2(830, 265, points[5], 0);
		break;
	case 6:
		iShowBMP2(830, 265, points[6], 0);
		break;
	case 7:
		iShowBMP2(830, 265, points[7], 0);
		break;
	case 8:
		iShowBMP2(830, 265, points[8], 0);
		break;
	case 9:
		iShowBMP2(830, 265, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit4) {
	case 0:
		iShowBMP2(760, 265, points[0], 0);
		break;
	case 1:
		iShowBMP2(760, 265, points[1], 0);
		break;
	case 2:
		iShowBMP2(760, 265, points[2], 0);
		break;
	case 3:
		iShowBMP2(760, 265, points[3], 0);
		break;
	case 4:
		iShowBMP2(760, 265, points[4], 0);
		break;
	case 5:
		iShowBMP2(760, 265, points[5], 0);
		break;
	case 6:
		iShowBMP2(760, 265, points[6], 0);
		break;
	case 7:
		iShowBMP2(760, 265, points[7], 0);
		break;
	case 8:
		iShowBMP2(760, 265, points[8], 0);
		break;
	case 9:
		iShowBMP2(760, 265, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	///////////////////////////////////////////////////
	switch (digit5) {
	case 0:
		iShowBMP2(690, 265, points[0], 0);
		break;
	case 1:
		iShowBMP2(690, 265, points[1], 0);
		break;
	case 2:
		iShowBMP2(690, 265, points[2], 0);
		break;
	case 3:
		iShowBMP2(690, 265, points[3], 0);
		break;
	case 4:
		iShowBMP2(690, 265, points[4], 0);
		break;
	case 5:
		iShowBMP2(690, 265, points[5], 0);
		break;
	case 6:
		iShowBMP2(690, 265, points[6], 0);
		break;
	case 7:
		iShowBMP2(690, 265, points[7], 0);
		break;
	case 8:
		iShowBMP2(690, 265, points[8], 0);
		break;
	case 9:
		iShowBMP2(690, 265, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}



}

void MenuHighScore(int num){
	int replacenum = num;
	int digit1 = replacenum % 10;
	int digit2 = (replacenum / 10) % 10;
	int digit3 = (replacenum / 100) % 10;
	int digit4 = (replacenum / 1000) % 10;
	int digit5 = (replacenum / 10000) % 10;

	///////////////////////////////////////////////////
	switch (digit1) {
	case 0:
		iShowBMP2(795, 290, points[0], 0);
		break;
	case 1:
		iShowBMP2(795, 290, points[1], 0);
		break;
	case 2:
		iShowBMP2(795, 290, points[2], 0);
		break;
	case 3:
		iShowBMP2(795, 290, points[3], 0);
		break;
	case 4:
		iShowBMP2(795, 290, points[4], 0);
		break;
	case 5:
		iShowBMP2(795, 290, points[5], 0);
		break;
	case 6:
		iShowBMP2(795, 290, points[6], 0);
		break;
	case 7:
		iShowBMP2(795, 290, points[7], 0);
		break;
	case 8:
		iShowBMP2(795, 290, points[8], 0);
		break;
	case 9:
		iShowBMP2(795, 290, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit2) {
	case 0:
		iShowBMP2(725, 290, points[0], 0);
		break;
	case 1:
		iShowBMP2(725, 290, points[1], 0);
		break;
	case 2:
		iShowBMP2(725, 290, points[2], 0);
		break;
	case 3:
		iShowBMP2(725, 290, points[3], 0);
		break;
	case 4:
		iShowBMP2(725, 290, points[4], 0);
		break;
	case 5:
		iShowBMP2(725, 290, points[5], 0);
		break;
	case 6:
		iShowBMP2(725, 290, points[6], 0);
		break;
	case 7:
		iShowBMP2(725, 290, points[7], 0);
		break;
	case 8:
		iShowBMP2(725, 290, points[8], 0);
		break;
	case 9:
		iShowBMP2(725, 290, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	//////////////////////////////////////////////
	switch (digit3) {
	case 0:
		iShowBMP2(655, 290, points[0], 0);
		break;
	case 1:
		iShowBMP2(655, 290, points[1], 0);
		break;
	case 2:
		iShowBMP2(655, 290, points[2], 0);
		break;
	case 3:
		iShowBMP2(655, 290, points[3], 0);
		break;
	case 4:
		iShowBMP2(655, 290, points[4], 0);
		break;
	case 5:
		iShowBMP2(655, 290, points[5], 0);
		break;
	case 6:
		iShowBMP2(655, 290, points[6], 0);
		break;
	case 7:
		iShowBMP2(655, 290, points[7], 0);
		break;
	case 8:
		iShowBMP2(655, 290, points[8], 0);
		break;
	case 9:
		iShowBMP2(655, 290, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	/////////////////////////////////////////////////////////////////////////
	switch (digit4) {
	case 0:
		iShowBMP2(585, 290, points[0], 0);
		break;
	case 1:
		iShowBMP2(585, 290, points[1], 0);
		break;
	case 2:
		iShowBMP2(585, 290, points[2], 0);
		break;
	case 3:
		iShowBMP2(585, 290, points[3], 0);
		break;
	case 4:
		iShowBMP2(585, 290, points[4], 0);
		break;
	case 5:
		iShowBMP2(585, 290, points[5], 0);
		break;
	case 6:
		iShowBMP2(585, 290, points[6], 0);
		break;
	case 7:
		iShowBMP2(585, 290, points[7], 0);
		break;
	case 8:
		iShowBMP2(585, 290, points[8], 0);
		break;
	case 9:
		iShowBMP2(585, 290, points[9], 0);
		break;

	default:
		cout << "Invalid " << endl;
	}
	///////////////////////////////////////////////////
	switch (digit5) {
	case 0:
		iShowBMP2(515, 290, points[0], 0);
		break;
	case 1:
		iShowBMP2(515, 290, points[1], 0);
		break;
	case 2:
		iShowBMP2(515, 290, points[2], 0);
		break;
	case 3:
		iShowBMP2(515, 290, points[3], 0);
		break;
	case 4:
		iShowBMP2(515, 290, points[4], 0);
		break;
	case 5:
		iShowBMP2(515, 290, points[5], 0);
		break;
	case 6:
		iShowBMP2(515, 290, points[6], 0);
		break;
	case 7:
		iShowBMP2(515, 290, points[7], 0);
		break;
	case 8:
		iShowBMP2(515, 290, points[8], 0);
		break;
	case 9:
		iShowBMP2(515, 290, points[9], 0);
		break;

	default:
		cout << "Invalid  digit 1" << digit1 << endl;
	}



}




void selectMenuOption(int menu_x, int menu_y)
{
	if (menu_option == 0)
	{
		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 550 && menu_y <= 603)
		{
			menu_option = 6; //To stop running menu codes & Start Game
			load = 1;
			obx = SCREEN_WIDTH;
		}

		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 465 && menu_y <= 513)
		{
			
			menu_option = 2; //For high scores.
			
		}

		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 380 && menu_y <= 426)
		{
			menu_option = 3; //For instructions.
		}

		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 290 && menu_y <= 340)
		{
			menu_option = 4; //For options.
		}

		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 195 && menu_y <= 245)
		{
			menu_option = 5; //For about.
		}

		if (menu_x >= 480 && menu_x <= 887 && menu_y >= 105 && menu_y <= 158)
		{
			exit(0); //For exit.
		}
	}


	if(menu_option >= 1 && menu_option <= 5)
	{
		if (menu_option == 2){
			if (menu_x >= 474 && menu_x <= 890 && menu_y >= 35 && menu_y <= 85)
			{
				menu_option = 0;	//To go back.
			}
		}
		if (menu_x >= 486 && menu_x <= 878 && menu_y >= 39 && menu_y <= 86)
		{
			menu_option = 0;	//To go back.
		}
	}
}



void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{

		/*HighLight Menu Option*/

		if (menu_option >= 0 && menu_option <= 5)
		{
			if      (mx >= 480 && mx <= 887 && my >= 550 && my <= 603)
			{
				highlight_index = 0;
			}
			else if (mx >= 480 && mx <= 887 && my >= 465 && my <= 513)
			{
				highlight_index = 1;
			}
			else if (mx >= 480 && mx <= 887 && my >= 380 && my <= 426)
			{
				highlight_index = 2;
			}
			else if (mx >= 480 && mx <= 887 && my >= 290 && my <= 340)
			{
				highlight_index = 3;
			}
			else if (mx >= 480 && mx <= 887 && my >= 195 && my <= 245)
			{
				highlight_index = 4;
			}
			else if (mx >= 480 && mx <= 887 && my >= 105 && my <= 158)
			{
				highlight_index = 5;
			}
			else
			{
				highlight_index = 6;
			}
			if (menu_option == 2){
				if (mx >= 474 && mx <= 890 && my >= 35 && my <= 85)
				{
					back_highlight_index = menu_option - 1;
				}
			}

			/*Highlighting back button*/

			if (mx >= 486 && mx <= 878 && my >= 39 && my <= 86)
			{
				back_highlight_index = menu_option - 1;
			}
			else{
				back_highlight_index = 5;
			}

		}
	}


void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

		if (menu_option >= 0 && menu_option <= 5) //Take axis for select Menu
		{
			selectMenuOption(mx, my);
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		printf("%d %d\n", mx, my);
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}



void iKeyboard(unsigned char key)
{

	if (key == 'a')
	{
		dinocordinateJump = 0;
		jflag = 1;
		dinoIndex = 0;
		dinojIndex = 0;

		if (dinojIndex == 7){
			jflag = 0;
			dinojIndex = 0;
		}

		if (jumpMusic)
			PlaySound("Music\\Dino_Jump.wav", NULL, SND_ASYNC);


	}

	if (key == 's' && load == 0){
		showMenu();
		menu_option = 0;
	}


	if (key == 'p')
	{
		paused = 1;
		iPauseTimer(index1);
		iPauseTimer(index2);
		iPauseTimer(index3);
		iPauseTimer(index4);


	}
	if (key == 'r'){

		iResumeTimer(index1);
		iResumeTimer(index2);
		iResumeTimer(index3);
		iResumeTimer(index4);
	}
	if (key == 'm'){
		if (menuMusic){
			menuMusic = false;
			PlaySound(0, 0, 0);
		}
		else{
			menuMusic = true;
			PlaySound("Music\\DinoBgM.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}

}
void iSpecialKeyboard(unsigned char key)
{
	

}



void increment(){
	score++;
	if (load == 0){
		score = 0;
	}
}
/* saveScore(){
	if (point){

		wFile.open("Highscore.txt");
		wFile << HScore;
		wFile.close();
		point = false;
	}
*/

void highScore(){
	rFile.open("Highscore.txt");
	while (!rFile.eof())
	{
		rFile >> fscore;
	}
	rFile.close();
	wFile.open("Highscore.txt");
	if (HScore>fscore){
		fscore = HScore;
	}
	wFile << fscore;
	wFile.close();
}

void change(){
	///Dino walking
	dinoIndex++;
	if (dinoIndex >= 7)
		dinoIndex = 0;
	///Dino Jumping
	dinojIndex++;
	if (dinojIndex >= 7){
		dinojIndex = 0;
		jflag = 0;
	}
	///Jumping Animation
	if (jflag == 1){
		if (dinoIndex == 0){
			dinocordinateJump += 25;
		}
		else if (dinoIndex == 1){
			dinocordinateJump += 25;
		}
		else if (dinoIndex == 2){
			dinocordinateJump += 25;
		}
		else if (dinoIndex == 3){
			dinocordinateJump += 25;
		}
		else if (dinoIndex == 4){
			dinocordinateJump -= 25;
		}
		else if (dinoIndex == 5){
			dinocordinateJump -= 15;
		}
		else if (dinoIndex == 6){
			dinocordinateJump = 0;
		}

	}
}

///Obstacle Animation
void obchange(){
	if (score > obspeedControl){
		obspeedControl += 100;
		obspeed += 5;
	}

	obx = obx - 20-obspeed;
	if (obx <= 0){
		obx = SCREEN_WIDTH;
	}

}
///Background Animation
void bkchange(){
	bkindex++;
	if (bkindex > 30)
		bkindex = 0;

}




void loadImage()
{
	/*Menu Image*/
	for (int i = 0; i <= 5; i++)
	{
		menu_image[i] = iLoadImage(menu_image_location[i]);
	}

	/*Menu Highlight Image*/

	for (int i = 0; i <= 5; i++)
	{
		menu_highlight_image[i] = iLoadImage(menu_highlight_image_location[i]);
	}

	/*Back Highlight Image*/
	back_highlight_image[0] = iLoadImage("menu\\highlight\\back\\1.bmp");
	back_highlight_image[1] = iLoadImage("menu\\highlight\\back\\2.bmp");
	back_highlight_image[2] = iLoadImage("menu\\highlight\\back\\3.bmp");
	back_highlight_image[3] = iLoadImage("menu\\highlight\\back\\4.bmp");
	back_highlight_image[4] = iLoadImage("menu\\highlight\\back\\5.bmp");


}




int main()
{
	//jumpMusic
	if (jumpMusic){
		jumpMusic = true;
		PlaySound("Music\\Dino_Jump.wav", NULL, SND_ASYNC);
}
	if (menuMusic){
		///menuMusic = false;
		PlaySound("Music\\DinoBgM.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "DINORUN");

	//Menu Import
	loadImage();


	///Background Import
	background[0][200] = iLoadImage("bk1.bmp"); background[1][200] = iLoadImage("bk2.bmp"); background[2][200] = iLoadImage("bk3.bmp"); background[3][200] = iLoadImage("bk4.bmp"); background[4][200] = iLoadImage("bk5.bmp"); background[5][200] = iLoadImage("bk6.bmp"); background[6][200] = iLoadImage("bk7.bmp"); background[7][200] = iLoadImage("bk8.bmp"); background[8][200] = iLoadImage("bk9.bmp"); background[9][200] = iLoadImage("bk10.bmp");
	background[10][200] = iLoadImage("bk11.bmp"); background[11][200] = iLoadImage("bk12.bmp"); background[12][200] = iLoadImage("bk13.bmp"); background[13][200] = iLoadImage("bk14.bmp"); background[14][200] = iLoadImage("bk15.bmp"); background[15][200] = iLoadImage("bk16.bmp"); background[16][200] = iLoadImage("bk17.bmp"); background[17][200] = iLoadImage("bk18.bmp"); background[18][200] = iLoadImage("bk19.bmp"); background[19][200] = iLoadImage("bk20.bmp");
	background[20][200] = iLoadImage("bk21.bmp"); background[21][200] = iLoadImage("bk22.bmp"); background[22][200] = iLoadImage("bk23.bmp"); background[23][200] = iLoadImage("bk24.bmp"); background[24][200] = iLoadImage("bk25.bmp"); background[25][200] = iLoadImage("bk26.bmp"); background[26][200] = iLoadImage("bk27.bmp"); background[27][200] = iLoadImage("bk28.bmp"); background[28][200] = iLoadImage("bk29.bmp"); background[29][200] = iLoadImage("bk30.bmp"); background[30][200] = iLoadImage("bk31.bmp");
	///obstacle = iLoadImage("obstacle.bmp");
	////srand((unsigned)time(NULL));

	index1 = iSetTimer(200, bkchange);
	index2 = iSetTimer(60, obchange);
	index3 = iSetTimer(150, change);
	index4 = iSetTimer(150, increment);

	////iSetTimer(150, collison);
	


	///updated see the documentations
	iStart();
	return 0;
}
