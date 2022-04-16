//#define LEFT_ENCODER    myEncoder
//#define PID_MOTOR_SCALE     1
///////////////////////////////////////////////////////////////////////////////////
//#define PID_MOTOR_MAX       127
//#define PID_MOTOR_MIN     (-127)
//#define PID_INTEGRAL_LIMIT  50
float  pid_Kp = 0.59;
float  pid_Ki = 0.09;//0.05;
float  pid_Kd = 0;//.05;
int   pidRunning = 0; //TURN ON OR OFF PID
float  RequestedAngle = 0, pidDriveR;
int angleSentinel = 1;
//////////////////////////////////////////////////////////////////////////////////////

void motorPower(float power)
{
	motor[LiftR]=power;
	motor[LiftL]=power;
}

task anglePIDControl()
{
    float  pidSensorCurrentValue;
    float  pidError;
    float  pidLastError;
    float  pidIntegral;
    float  pidDerivative;
    // Init the variables
    pidLastError  = 0;
    pidIntegral   = 0;
    while( true )
        {
        // Is PID control active ?
        if( pidRunning )
            {
            // calculate error
            //pidError = ((1100+nMotorEncoder[Angle])/47.64) - RequestedAngle;
            pidError = RequestedAngle-(-1)*SensorValue[LiEnc];// - (RequestedAngle);
            // integral - if Ki is not 0
            if( pid_Ki != 0 )
                {
                // If we are inside controlable window then integrate the error
                if( abs(pidError) < PID_INTEGRAL_LIMIT )
                    pidIntegral = pidIntegral + pidError;
                else
                    pidIntegral = 0;
                }
            else
                pidIntegral = 0;
            // calculate the derivative
            pidDerivative = pidError - pidLastError;
            pidLastError  = pidError;
            // calculate drive
            pidDriveR = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
            // limit drive
            if( pidDriveR > PID_MOTOR_MAX )
                pidDriveR = PID_MOTOR_MAX;
            if( pidDriveR < PID_MOTOR_MIN )
                pidDriveR = PID_MOTOR_MIN;
            // send to motor
            motorPower(pidDriveR * PID_MOTOR_SCALE);

            if(abs(pidError)<15) angleSentinel = 0;
       			else angleSentinel = 1;
            }
        else
            {
            // clear all
            pidError      = 0;
            pidLastError  = 0;
            pidIntegral   = 0;
            pidDerivative = 0;
            motorPower(0);
            }
        // Run at 50Hz
        wait1Msec( 25 );
        }
}
