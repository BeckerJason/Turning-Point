#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  Load,           sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LoadBall,      tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           Roller,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LM,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LY,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Flip,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RM,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RY,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Lift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Feeder,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LoadBall2,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//int LiftPow=0;
int shootball=0;
int R=4;
int FR=4;
float ddir=1.0;

task Shoot()
{
	while(1)
{
	if (shootball==1)
	{
{while (abs(SensorValue(Load))<627.2){motor[LoadBall]=127;motor[LoadBall2]=motor[LoadBall];}
	SensorValue(Load)=0;
	motor[LoadBall]=-50;motor[LoadBall2]=motor[LoadBall];
	wait1Msec(75);
	//wait1Msec(20);
//while (abs(SensorValue(Load))>0){motor[LoadBall]=-50;}
//	wait1Msec(20);
//while (abs(SensorValue(Load))>0){motor[LoadBall]=50;}

		shootball=0;

	}

}
	else {motor[LoadBall]=0;}
}
}

task main()
{SensorValue(Load)=0;
	startTask(Shoot);
	SensorValue[Load]=0;
	while (1)
	{

		if(abs(vexRT[Ch3])>15 ||abs(vexRT[Ch4])>15)//backwards
		{
			motor[LM] = (ddir*vexRT[Ch3] + vexRT[Ch4]);
			motor[LY] = (ddir*vexRT[Ch3] + vexRT[Ch4]);


			motor[RM] = (ddir*vexRT[Ch3] - vexRT[Ch4]);
			motor[RY] = (ddir*vexRT[Ch3] - vexRT[Ch4]);
		}
		else
		{
			motor[LM] = 0;
			motor[LY] = 0;

			motor[RM]=0;
			motor[RY]=0;
		}
		/*		if (abs(vexRT[Ch2])>10)
		{
		motor[port8]=-vexRT[Ch2];
		motor[port9]=-vexRT[Ch2];
		}

		else
		{

		motor[port8]=-10;
		motor[port9]=-10;


		}*/

		if (vexRT[Btn5U]==1)
		{motor[Flip]=127;
		}
		else if (vexRT[Btn5D]==1)
		{motor[Flip]=-127;
		}
		else {motor[Flip]=10;}

		if (vexRT[Btn8D]==1)
		{shootball=1;
		}
		else {}
		if (abs(vexRT[Ch2])>15){motor[Lift]=vexRT[Ch2];}
		else{motor[Lift]=10;}


		if(FR == 4 && vexRT[Btn8R] == 0){ motor[Feeder] = 0;motor[Roller] =0; FR = 1;} //Roller
else if(FR == 1 && vexRT[Btn8R] == 1){ motor[Feeder] = 120;FR = 2;R=4;}
else if(FR == 2 && vexRT[Btn8R] == 0){ motor[Feeder] = 120; FR = 3;R=4;}
else if(FR == 3 && vexRT[Btn8R] == 1){ motor[Feeder] = 0; motor[Roller] =0;FR = 4;}
else{}
		if(R == 4 && (FR == 4||FR == 3)&&vexRT[Btn8U] == 0){ motor[Roller] = -120; R = 1;} //Roller
else if(R == 1 && (FR == 4||FR == 3)&&vexRT[Btn8U] == 1){ motor[Roller] = 120; R = 2;}
else if(R == 2 && (FR == 4||FR == 3)&&vexRT[Btn8U] == 0){ motor[Roller] = 120; R = 3;}
else if(R == 3 && (FR == 4||FR == 3)&&vexRT[Btn8U] == 1){ motor[Roller] = -120; R = 4;}
else{}

		if(ddir==1.01 && vexRT[Btn6D] == 0){ ddir = 1.0;} //Roller
else if(ddir== 1.0 &&vexRT[Btn6D] == 1){ ddir = -1.01;}
else if(ddir == -1.01 && vexRT[Btn6D] == 0){ ddir= -1.0;}
else if(ddir == -1.0 && vexRT[Btn6D] == 1){ddir= 1.01;}
else{}
		}
}
