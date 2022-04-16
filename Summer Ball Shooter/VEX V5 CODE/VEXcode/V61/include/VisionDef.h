/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature REDCOLOR = vex::vision::signature (1, 4000, 10000, 7000, -1000, 1000, 0, 1.2, 0);
vex::vision::signature BLUECOLOR = vex::vision::signature (2, -4100, -1100, -2600, 6000, 14000, 10000, 1.6, 0);
vex::vision::signature GREENFLAG = vex::vision::signature (3, -1800, -1000, -1400, -5261, -4053, -4657, 4.4, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 3031, 3243, 3136, -119, 117, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision = vex::vision (vex::PORT2, 49, REDCOLOR, BLUECOLOR, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/