/*vex-vision-config:begin*/
#include "v5.h" 
#include "v5_vcs.h"
vex::vision::signature REDCOLOR = vex::vision::signature (1, 4000, 7000, 5500, 100, 1000, 500, 1.6, 1);
vex::vision::signature BLUECOLOR = vex::vision::signature (2, -3200, -1100, -2100, 6000, 10000, 8000, 1.4, 1);
vex::vision::signature GREENFLAG = vex::vision::signature (3, -1800, -1000, -1400, -5261, -4053, -4657, 3.4, 1);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT2, 50, REDCOLOR, BLUECOLOR, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/