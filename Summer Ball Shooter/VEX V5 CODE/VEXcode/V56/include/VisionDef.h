/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature REDCOLOR = vex::vision::signature (1, 8935, 10649, 9792, -885, 851, -18, 6.3, 1);
vex::vision::signature BLUECOLOR = vex::vision::signature (2, -2955, -2359, -2656, 10921, 12219, 11570, 7.4, 1);
vex::vision::signature GREENFLAG = vex::vision::signature (3, -3171, -2107, -2638, -4529, -3337, -3934, 2.9, 1);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::code BLUEFLAG = vex::vision::code (BLUECOLOR, GREENFLAG );
vex::vision::code REDFLAG = vex::vision::code (REDCOLOR, GREENFLAG );
vex::vision Vision = vex::vision (vex::PORT2, 52, REDCOLOR, BLUECOLOR, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/