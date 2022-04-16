task LCDSpeed()
{bLCDBacklight = true;
	string rpmvalue;
	while(1)
	{
		///////////////////////
		clearLCDLine(0);
		clearLCDLine(1);
		///////////////////////
sprintf(rpmvalue, "<-> %f <+>",rpm); //Build the value to be displayed

		if (nLCDButtons == 1||vexRT[Btn8D]==1)
		{
			if (RPMGoal == 50)
			{
				//DO Nothing
			}
			else
			{
				RPMGoal-=10;
			}
		}
		else if (nLCDButtons == 2)
		{
			//Do nothing
		}
		else if (nLCDButtons == 4||vexRT[Btn8U]==1)
		{
			if (RPMGoal == 130)
			{
				//DO NOTHING
			}
			else
			{
				RPMGoal+=10;
			}
		}

		/////////////////////////
		if (RPMGoal == 50)
		{
			displayLCDCenteredString(0, " RPM GOAL: 50");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 60)
		{
			displayLCDCenteredString(0, " RPM GOAL: 60");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 70)
		{
			displayLCDCenteredString(0, " RPM GOAL: 70");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 80)
		{
			displayLCDCenteredString(0, " RPM GOAL: 80");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 90)
		{
			displayLCDCenteredString(0, " RPM GOAL: 90");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 100)
		{
			displayLCDCenteredString(0, " RPM GOAL: 100");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 110)
		{
			displayLCDCenteredString(0, " RPM GOAL: 110");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		else if (RPMGoal == 120)
		{
			displayLCDCenteredString(0, " RPM GOAL: 120");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
				else if (RPMGoal == 130)
		{
			displayLCDCenteredString(0, " RPM GOAL: 130");
			displayLCDString(1, 0, "");
			displayNextLCDString(rpmvalue);
		}
		wait1Msec(100);
	}

	////////////////////////////////////////////////////////////////
}
