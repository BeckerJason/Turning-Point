/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature REDCOLOR = vex::vision::signature (1, 7545, 8245, 7896, -1, 835, 416, 6, 1);
vex::vision::signature BLUECOLOR = vex::vision::signature (2, -2903, -2413, -2658, 11381, 12721, 12052, 5.9, 1);
vex::vision::signature GREENFLAG = vex::vision::signature (3, -2513, -2031, -2272, -4045, -3489, -3768, 5.6, 1);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::code REDFLAG = vex::vision::code (REDCOLOR, BLUECOLOR, GREENFLAG );
vex::vision::code BLUEFLAG = vex::vision::code (BLUECOLOR, GREENFLAG );
vex::vision Vision = vex::vision (vex::PORT2, 50, REDCOLOR, BLUECOLOR, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/