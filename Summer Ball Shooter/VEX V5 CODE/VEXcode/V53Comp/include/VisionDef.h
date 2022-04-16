/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature REDFLAG = vex::vision::signature (1, 7545, 8245, 7896, -1, 835, 416, 6.9, 0);
vex::vision::signature BLUEFLAG = vex::vision::signature (2, -2621, -1819, -2220, 8121, 9161, 8642, 7, 0);
vex::vision::signature GREENFLAG = vex::vision::signature (3, -2513, -2031, -2272, -4045, -3489, -3768, 8.7, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT2, 50, REDFLAG, BLUEFLAG, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/