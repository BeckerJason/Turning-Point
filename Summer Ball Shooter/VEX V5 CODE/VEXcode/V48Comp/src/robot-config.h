vex::controller Controller = vex::controller();
vex::digital_out Lift = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out Trans = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_in IR = vex::digital_in(Brain.ThreeWirePort.C);
vex::line BallBottom = vex::line(Brain.ThreeWirePort.D);
vex::limit BallLoaded = vex::limit(Brain.ThreeWirePort.E);
vex::line RLine = vex::line(Brain.ThreeWirePort.F);
vex::line LLine = vex::line(Brain.ThreeWirePort.G);
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.H);

vex::motor Hood = vex::motor(vex::PORT1,vex::gearSetting::ratio36_1,false);
vex::motor FlyL = vex::motor(vex::PORT6,vex::gearSetting::ratio6_1,true);
vex::motor FlyR = vex::motor(vex::PORT7,vex::gearSetting::ratio6_1,true);

vex::motor Turret = vex::motor(vex::PORT12,vex::gearSetting::ratio6_1,false);
vex::motor BallFeed = vex::motor(vex::PORT13,vex::gearSetting::ratio18_1,true);
vex::motor LF = vex::motor(vex::PORT14,vex::gearSetting::ratio18_1,true);
vex::motor LB = vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,false);
vex::motor LM = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,true);
vex::motor RB = vex::motor(vex::PORT17,vex::gearSetting::ratio18_1,true);
vex::motor RM = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,false);
vex::motor RF = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor Roll = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,false);


vex::motor Roller2 = vex::motor(vex::PORT21,vex::gearSetting::ratio18_1,true);