/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jason                                                     */
/*    Created:      Sun Mar 31 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include "v5.h"
#include "v5_vcs.h"
vex::brain Brain;
#include "VisionDef.h" 
float count=0;
using namespace std;
char TrackColor = 'R';
char Alliance = 'R';
int AutoNumber = 1;//76 red 106 blue
float RPMGoal = 114,rpm = 0, rpmError = 100.0, TurnDiff = 0, TempHeight = 0, TempWidth = 0, TurnDir = 1, TempXDist = 200, GlobalFlagOffset = 160;
int  fly = 4, R = 4, Tran = 0,LiftVar=2, Shoot = 0, SnapToFlag = 0, AutoRunning = 0, FlipCount,TurretRunning=0;//flywheel//Roller//Transmission
int MoveReturn=0;
int T1 = 0, T3 = 0;
float avgSpeed = 0;
float avgError = 0;
float GlobalGyro = 0;
int FlagYDim=0;
double AutoRPM=0;
int Color=1;
float FinalObject=20,TempObject=0;
float counts=0;
#define TOTALSNAPSHOTS 7
class VisionObject {
  public: 
          int     id[TOTALSNAPSHOTS];
          int     originX[TOTALSNAPSHOTS];
          int     originY[TOTALSNAPSHOTS];         
          int     centerX[TOTALSNAPSHOTS];
          int     centerY[TOTALSNAPSHOTS];
          int     width[TOTALSNAPSHOTS];
          int     height[TOTALSNAPSHOTS];
          double  angle[TOTALSNAPSHOTS];
          bool    exists[TOTALSNAPSHOTS];
} GreenMarker;
 
int main() {
    Brain.Screen.setPenColor(vex::color::white);    
    while(1)
    {
      Vision.takeSnapshot(3,TOTALSNAPSHOTS);//take picture of green markers
      for (int i=0;i<TOTALSNAPSHOTS;i++)
      {
        GreenMarker.id[i]=Vision.objects[i].id;
        GreenMarker.originX[i]=Vision.objects[i].originX;
        GreenMarker.originY[i]=Vision.objects[i].originY;
        GreenMarker.centerX[i]=Vision.objects[i].centerX;
        GreenMarker.centerY[i]=Vision.objects[i].centerY;
        GreenMarker.width[i]=Vision.objects[i].width;
        GreenMarker.height[i]=Vision.objects[i].height;
        GreenMarker.angle[i]=Vision.objects[i].angle;
        GreenMarker.exists[i]=Vision.objects[i].exists;
      }
      //Vision.takeSnapshot(1,TOTALSNAPSHOTS);//take picture of green markers
        
        
        Brain.Screen.clearScreen(vex::color::black); 
        Brain.Screen.printAt(1,40,"Count: %f",count);
        //Brain.Screen.printAt(90,40,"Count: %f",count);
        //Brain.Screen.printAt(90,60,"Count: %f",count);
        //Brain.Screen.printAt(90,80,"Count: %f",count);
        Brain.Screen.printAt(1,80,"Sec: %f",Brain.timer(vex::timeUnits::sec));
        Brain.Screen.printAt(1,120,"Count/Sec: %f",counts);



        
        if (Brain.timer(vex::timeUnits::sec)>=1)
        {
          counts=count/Brain.timer(vex::timeUnits::sec);
          Brain.resetTimer();
          count=0;
        }

    //Brain.Screen.drawRectangle(GreenMarker.centerX[i] - (GreenMarker.width[i]/2),GreenMarker.centerY[i] - (GreenMarker.height[i]/2),GreenMarker.width[i],GreenMarker.height[i],vex::color::white); 
       
  Vision.takeSnapshot(1, TOTALSNAPSHOTS);
			//Brain.Screen.setPenColor(vex::color::red);
            int TXDist = 400; 
		GlobalFlagOffset=160;
        //GlobalFlagOffsetL=310-GlobalFlagOffset;
		for (int i = 0; Vision.objects[i].exists == 1;i++)//||VisionL.objects[i].exists == 1; i++)
		{	
			if (Vision.objects[i].exists == 1&&fabs(GlobalFlagOffset - Vision.objects[i].centerX) < fabs(TXDist)) 
      {
        for (int j = 0; GreenMarker.exists[j] == 1;j++)//||VisionL.objects[i].exists == 1; i++)
		    {	
          //if there is a green marker in close range to the flag
          if (Vision.objects[i].centerX<GreenMarker.centerX[j]+40&&Vision.objects[i].centerX>GreenMarker.centerX[j]-30&&Vision.objects[i].centerY<GreenMarker.centerY[j]+10&&Vision.objects[i].centerY>GreenMarker.centerY[j]-10)  
          {
            TXDist = GlobalFlagOffset - Vision.objects[i].centerX;
            j=TOTALSNAPSHOTS+1;
          }
          else{}
        }
        
      }
			else {}
		}        
		
    int TObject=9;
		int TWidth = 0;
		int THeight = 0;
		float TYDist=400.0;			
		for (int i = 0; Vision.objects[i].exists == 1; i++)
		{
			//if (Vision.objects[i].width > 8 && Vision.objects[i].height > 8) { Brain.Screen.printAt(230, 20 + i * 20, "X:%d,Y:%d W:%d H:%d D:%1.2f", Vision.objects[i].centerX, Vision.objects[i].centerY, Vision.objects[i].width, Vision.objects[i].height, 0.0157*pow(Vision.objects[i].height, 2) - 1.0842*Vision.objects[i].height + 19.93); }
			if ((Vision.objects[i].width > 8 && Vision.objects[i].height > 8) && (Vision.objects[i].centerX > (GlobalFlagOffset - 10 - TXDist) && Vision.objects[i].centerX < (GlobalFlagOffset + 10 - TXDist)) && Vision.objects[i].centerY < TYDist) 
      { for (int j = 0; GreenMarker.exists[j] == 1;j++)//||VisionL.objects[i].exists == 1; i++)
		    {	
          //if there is a green marker in close range to the flag
          if (Vision.objects[i].centerX<GreenMarker.centerX[j]+40&&Vision.objects[i].centerX>GreenMarker.centerX[j]-30&&Vision.objects[i].centerY<GreenMarker.centerY[j]+10&&Vision.objects[i].centerY>GreenMarker.centerY[j]-10)  
          {
            TYDist = Vision.objects[i].centerY; TWidth = GlobalFlagOffset - Vision.objects[i].centerX; THeight=Vision.objects[i].height;  TObject=i;
            j=TOTALSNAPSHOTS+1;
          }
          else{}
        }
        
         
      }
																																								   
			else {}
		}
		
             
		FinalObject=TObject;
    int i =FinalObject;
    Brain.Screen.drawRectangle(Vision.objects[i].centerX - (Vision.objects[i].width/2),Vision.objects[i].centerY - (Vision.objects[i].height/2),Vision.objects[i].width,Vision.objects[i].height,vex::color::white); 
         














        if (GreenMarker.width[0]>10){count++;}
                vex::task::sleep(17);
            }
    
}