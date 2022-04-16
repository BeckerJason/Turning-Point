vex::controller extern Controller = vex::controller();
vex::digital_out extern Lift = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out extern Trans = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_in extern IR = vex::digital_in(Brain.ThreeWirePort.C);
vex::line extern BallBottom = vex::line(Brain.ThreeWirePort.D);
vex::limit extern BallLoaded = vex::limit(Brain.ThreeWirePort.E);
vex::line extern RLine = vex::line(Brain.ThreeWirePort.F);
vex::line extern LLine = vex::line(Brain.ThreeWirePort.G);
vex::gyro extern Gyro = vex::gyro(Brain.ThreeWirePort.H);
 
vex::motor extern Hood = vex::motor(vex::PORT1,vex::gearSetting::ratio36_1,false);
vex::motor extern FlyL = vex::motor(vex::PORT6,vex::gearSetting::ratio6_1,true);
vex::motor extern FlyR = vex::motor(vex::PORT7,vex::gearSetting::ratio6_1,true);

vex::motor extern Turret = vex::motor(vex::PORT12,vex::gearSetting::ratio6_1,false);
vex::motor extern BallFeed = vex::motor(vex::PORT13,vex::gearSetting::ratio18_1,true);
vex::motor extern LF = vex::motor(vex::PORT14,vex::gearSetting::ratio18_1,true);
vex::motor extern LB = vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,false);
vex::motor extern LM = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,true);
vex::motor extern RB = vex::motor(vex::PORT17,vex::gearSetting::ratio18_1,false);
vex::motor extern RM = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,true);
vex::motor extern RF = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor extern Roll = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,false);


vex::motor extern Roller2 = vex::motor(vex::PORT21,vex::gearSetting::ratio18_1,true);