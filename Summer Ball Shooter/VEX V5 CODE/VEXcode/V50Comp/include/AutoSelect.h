//WILL EDIT LATER TO SELECT MULTIPLE DIFFERENT AUTOS


#include "defines.h"
using namespace G; 
#ifndef DEBUG //if DEBUG is defined earlier this section will not compile
void AllianceSelect() 
{   //screen 480x272

	Brain.Screen.clearScreen(vex::color::black);//show red blue and confirm
	int selection = 0;
	while (selection < 4)
	{
		Brain.Screen.setPenWidth(1);
		Brain.Screen.setPenColor(vex::color::black);
		if (bRight == 1 || (Brain.Screen.xPosition() > 300 && Brain.Screen.xPosition() < 420 && Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 60)) { selection = 1; Controller.Screen.print("Blue"); }//if Touch within blue box:: selection=1
		else if (bLeft == 1 || (Brain.Screen.xPosition() > 60 && Brain.Screen.xPosition() < 180 && Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 60)) { selection = 2;  Controller.Screen.clearLine(1); Controller.Screen.print("Red"); } //else if Touch within red box:: selection=2
		else if (selection == 3 && Brain.Screen.pressing() == 0) { selection = 4; } //else if Touch within select box&& Selection >0 :: selection=3
		else if ((bA && selection > 0) || (Brain.Screen.xPosition() > 180 && Brain.Screen.xPosition() < 300 && Brain.Screen.yPosition() > 100 && Brain.Screen.yPosition() < 140 && selection > 0)) { selection = 3; } //else if Touch within select box&& Selection >0 :: selection=3


		if (selection == 1) { TrackColor = 'B'; Brain.Screen.drawRectangle(297, 17, 126, 46, vex::color::green); Brain.Screen.drawRectangle(57, 17, 126, 46, vex::color::black); }  //if selection==1 draw green box around Blue and Black Box around red
		else if (selection == 2) { TrackColor = 'R'; Brain.Screen.drawRectangle(297, 17, 126, 46, vex::color::black); Brain.Screen.drawRectangle(57, 17, 126, 46, vex::color::green); }//else if selection==2 draw green box around red and Black Box around blue
		else if (selection == 3) { Brain.Screen.drawRectangle(177, 97, 126, 46, vex::color::green); }//else if selection==3 draw green box around select


		Brain.Screen.drawRectangle(60, 20, 120, 40, vex::color::red);
		Brain.Screen.drawRectangle(300, 20, 120, 40, vex::color::blue);
		Brain.Screen.drawRectangle(180, 100, 120, 40, vex::color::white);
		Brain.Screen.setPenWidth(10);
		Brain.Screen.setPenColor(vex::color::white);
		Brain.Screen.printAt(105, 45, false, "RED");
		Brain.Screen.printAt(340, 45, false, "BLUE");
		Brain.Screen.setPenColor(vex::color::black);
		Brain.Screen.printAt(210, 125, false, "SELECT");
		wait(100);
		Alliance = TrackColor;
	}
    if (TrackColor=='B'){
        Color=1;
    }
    else {
      Color=2; 
    }
}
#endif