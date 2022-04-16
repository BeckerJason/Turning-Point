task FourBar()
{
	while(1)
	{
	//Bring Roller Up
		if(fbStatus==1)
		{
			while(FBControl(1));
			//{
				//if(vexRT[
			//}
		}

		//Bring Roller Down//
		if(fbStatus==0)
		{
			while(FBControl(0));
		}

		//UPDATE GYROSCOPE VALUE TO SEE IN GLOBAL VARIABLES WINDOWS
		gyroVal = SensorValue[gyro];
		//UPDATE BATTERY SCALLER
		if(nImmediateBatteryLevel!=0)
		bs1 = 8.0/(nImmediateBatteryLevel/1000.0);
		if(SensorValue[BackUpBattery]!=0)
		bs2 = 8.0/(SensorValue[BackUpBattery]/280.0);
		wait1Msec(25);
	}
}

task autoStack()
{
	while(1)
	{
		gyroVal = SensorValue[gyro];
		bs1 = 8.0/(nImmediateBatteryLevel/1000.0);
		wait1Msec(50);
	}
	/*
	int cones = 0;
	float Kc = 0.01;
	while(1)
	{
		if(SensorValue[LiftLimit])	SensorValue[LiEnc]=0;
		//Intake
		if(vexRT[Btn5U] == 1)
		{

			//Stage 1 (lift control)
			if(cones == 0)
			{
				motor[L1] = -30;
				motor[R1] = -30;
			}
			else
			{
				while(abs(SensorValue[LiEnc]) < cones*Kc)
				{
					motor[L1] = 127;
					motor[R1] = 127;
				}
				motor[L1] = 0;
				motor[R1] = 0;

			}
			motor[roller]=127;

			if(SensorValue[IRFB]<1500){

			}

		}
		else if (motor[roller] == 127)
		{
			motor[roller] = 20;
		}
		//OutTake
		if(vexRT[Btn5D] == 1)
		{
			motor[roller]=-127;
		}
		else if(motor[roller] == -127)
		{
			motor[roller] = 0;
		}
		//////////////////////////

		wait1Msec(25);
	}
	*/
}
