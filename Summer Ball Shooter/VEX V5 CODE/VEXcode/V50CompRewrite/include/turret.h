#include "defines.h"
using namespace G;
using namespace std;

void TurnTurret(double degree)
  {   
  Turret.resetRotation();
  int dir;
  if (degree>0)
    {dir=-1;}
  else
    {dir=1;}
  //degree>0 means left
  double count=5;
  double gearratio=12.0/175.0;
  while(abs(Turret.rotation(vex::rotationUnits::deg))<abs((degree/gearratio)))
    {  
      //if(LeftTurretLimit.pressing()==1){break;}
      // else if(RightTurretLimit.pressing()==1){break;}
      if ((abs(Turret.rotation(vex::rotationUnits::deg))>abs(((degree/gearratio)/2)))&&count>=5)
        {count-=1.5;}
      else{count+=1;}   
      Turret.spin(vex::directionType::fwd,(count*dir),vex::percentUnits::pct);
      wait(10);  
      //Brain.Screen.printAt(230, 20,"%f", abs(Turret.rotation(vex::rotationUnits::deg)));
      //Brain.Screen.printAt(230, 50,"%f", ((degree/gearratio)));
    }
    run(Turret,0);
  }