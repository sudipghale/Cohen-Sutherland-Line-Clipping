# Cohen-Sutherland-Line-Clipping

To Compile
$ gcc -o hmwk_03 hmwk_03.c line.c view.c
$ ./hmwk_03 Tests/pyramid_01.line Tests/pyramid_01.view

#- View parameters ---------------------
 Bézier resolution :     0
 Euler angles      :      0.000000,      0.000000,      0.000000
 World limits      :     -1.000000,     -1.000000,      1.000000,      1.000000
 Camera distance   :      0.000000
 Canvas width      :   500
 Canvas height     :   400
 Screen limits     :      0.100000,      0.100000,      0.900000,      0.900000
 Portal pixels     :   50,  450,   40,  360
#---------------------------------------
c  500  400
l     50.0     40.0    450.0     40.0
l    450.0     40.0    450.0    360.0
l    450.0    360.0     50.0    360.0
l     50.0    360.0     50.0     40.0
l    410.0    328.0    410.0    200.0
l    410.0    200.0    250.0    200.0
l    250.0    200.0    410.0    328.0
l    250.0    328.0    410.0    328.0
l    410.0    328.0    250.0    200.0
l    250.0    200.0    250.0    328.0
l    410.0    200.0    330.0    264.0
l    330.0    264.0    250.0    200.0
l    250.0    200.0    410.0    200.0
l    330.0    264.0    250.0    328.0
l    250.0    328.0    250.0    200.0
l    250.0    200.0    330.0    264.0
l    410.0    200.0    410.0    328.0
l    410.0    328.0    330.0    264.0
l    330.0    264.0    410.0    200.0
l    250.0    328.0    330.0    264.0
l    330.0    264.0    410.0    328.0
l    410.0    328.0    250.0    328.0
#- Line statistics ---------------------
#     22 lines drawn.
#      0 lines rejected.
#---------------------------------------
