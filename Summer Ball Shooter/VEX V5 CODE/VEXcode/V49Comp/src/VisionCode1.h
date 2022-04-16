/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
/*vex-vision-config:begin*/
vex::vision::signature REDFLAG =vex::vision::signature(1, 5487, 7971, 6728, 885, 1793, 1340, 3.200000047683716, 0);
vex::vision::signature BLUEFLAG =vex::vision::signature(2, -2881, -2389, -2636, 12207, 13239, 12722, 8.699999809265137, 0);
vex::vision::signature GREENFLAG =vex::vision::signature(3, -2889, -2035, -2462, -3849, -2565, -3208, 3, 0);
vex::vision::signature SIG_4 =vex::vision::signature(4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 =vex::vision::signature(5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 =vex::vision::signature(6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 =vex::vision::signature(7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision = vex::vision (vex::PORT11, 58, REDFLAG, BLUEFLAG, GREENFLAG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/