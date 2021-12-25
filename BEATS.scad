// MIDI Beat Counter 
// Case and assemble
// Author Georg Zieger
// g.zi@gmx.de
// 
// neopixel ring von 1820 nach 1850 um 5 mil (0.127mm) nach unten geschoben


_W = 55.88;   // PCB width
_L = 99.949;  // PCB lenght
_gap = 0.15;  // gap between PCB anc case, will decrease wall thickness
_Hb = 47;     // case height back
_Hf = 14.4;   // case height front
_sp = 2;      // sphere radius
_wt = 2-_sp;  // wall thickness
_top = 3.2;   // top wall thickness
_btn = 3;     // bottom wall thickness
_pcbt = 1.6;  // PCB thickness
_dispt = 9.2; // total display height over PCB
_disph = 7.6; // display height over PCB
_sc = 0.4;    // screen thickness foliage over rgb keys
_kh = 9.5;    // key height over PCB
_shift = 0.3; // space for shift switch 
$fn = 100;    // circle fragments 

/*
rotate([180,0,90]) color("DimGray") case();
rotate([180,0,90]) pcb(_hole);
rotate([180,0,90]) usb();
rotate([180,0,90]) audio();
rotate([180,0,90]) dmx();
*/

rotate([0,0,90]) color("DimGray") case();
//rotate([0,0,90]) display();
//rotate([180,0,90]) color("DimGray") bottom();
//rotate([162.45 ,0 ,90]) translate([0,0,-17.1764]) color("DimGray") bottom(); 
//rotate([0,0,90]) color("DimGray") shift();
//rotate([0,0,90]) pcb();
//rotate([0,0,90]) flex_led();
//rotate([0,0,90]) bolt_case();

//rotate([180,0,90]) inner(); // activate this for animation 
_cutx  = 50;    // cut case in x direction, no cut = 0, range 0-116
_cuty  = 0;   // cut case in y direction, no cut = 0, range 0-206
_hole = 0 ;      // view holes in PCB
_explode = 0; // height of explosion (10 shows text), values higher 100 for animation (300)
                // for animation activate View-Animate (FPS:5, Steps:200, _hole=0)

                // create GIF with brew install ImageMagick
                // convert *.png screens.gif

_t0 = 0     ;
_t1 = 0.04  ;
_t2 = 0.08  ;
_t3 = 0.12  ;
_t4 = 0.16  ;
_t5 = 0.2   ;
_t6 = 0.24  ;
_t7 = 0.28  ;
_t8 = 0.32  ;
_t9 = 0.36  ;
_t10 = 0.4  ;
_t11 = 0.44 ;
_t12 = 0.48 ;
_t13 = 0.52 ;
_t14 = 0.56 ;
_t15 = 0.6  ;
_t16 = 0.64 ;
_t17 = 0.68 ;
_t18 = 0.72 ;
_t19 = 0.76 ;
_t20 = 0.8  ;
_t21 = 0.84 ;
_t22 = 0.88 ;
_t23 = 0.92 ;
_t24 = 0.96 ;
_t25 = 1    ;

module inner() {
// color("red") 

if(_explode>=100) {
  translate([0,0,0]) pcb(_hole);
  if($t>_t0 && $t<=_t1)   translate([0,0,-($t-_t1)*_explode*2]) audio();
  else if($t>_t1)                                               audio();

  if($t>_t1 && $t<=_t2)     translate([0,0, ($t-_t2)*_explode]) usb_wire();
  else if($t>_t2)                                               usb_wire();
  if($t>_t1 && $t<=_t2)     translate([0,0, ($t-_t2)*_explode]) mic();
  else if($t>_t2)                                               mic();

  if($t>_t2 && $t<=_t3)     translate([0,0, ($t-_t3)*_explode]) teensy();
  else if($t>_t3)                                               teensy();
  if($t>_t3 && $t<=_t4)     translate([0,0, ($t-_t4)*_explode]) encoder();
  else if($t>_t4)                                               encoder();
  if($t>_t4 && $t<=_t5)     translate([0,0, ($t-_t5)*_explode]) keyboard();
  else if($t>_t5)                                               keyboard();
  if($t>_t5 && $t<=_t6)     translate([0,0, ($t-_t6)*_explode]) connect();
  else if($t>_t6)                                               connect();
  if($t>_t6 && $t<=_t7) translate([0,0,-($t-_t7)*_explode*2.5]) usb();
  else if($t>_t7)                                               usb();
  if($t>_t7 && $t<=_t8)     translate([0,0,-($t-_t8)*_explode]) dmx();
  else if($t>_t8)                                               dmx();
  if($t>_t8 && $t<=_t9)     translate([0,0, ($t-_t9)*_explode]) display();
  else if($t>_t9)                                               display();
  if($t>_t9 && $t<=_t10)   translate([0,0, ($t-_t10)*_explode]) flex_wire();
  else if($t>_t10)                                              flex_wire();
  if($t>_t10 && $t<=_t11)  translate([0,0, ($t-_t11)*_explode]) fsr();
  else if($t>_t11)                                              fsr();
  if($t>_t11 && $t<=_t12)  translate([0,0, ($t-_t12)*_explode]) neopixel_data();
  else if($t>_t12)                                              neopixel_data();
  if($t>_t12 && $t<=_t13)  translate([0,0, ($t-_t13)*_explode]) flex_led();
  else if($t>_t13)                                              flex_led();
  if($t>_t13 && $t<=_t14)  translate([0,0, ($t-_t14)*_explode]) neopixel_wire();
  else if($t>_t14)                                              neopixel_wire();
  if($t>_t14 && $t<=_t15)  translate([0,0, ($t-_t15)*_explode]) neopixel_ring();
  else if($t>_t15)                                              neopixel_ring();

  if($t>_t15 && $t<=_t16) translate([0,0, ($t-_t16)*_explode*3]) color("DimGray") case();
  else if($t>_t16)                                               color("DimGray") case();
  if($t>_t15 && $t<=_t16) translate([0,0, ($t-_t16)*_explode*3]) folio();
  else if($t>_t16)                                               folio();
  if($t>_t15 && $t<=_t16) translate([0,0, ($t-_t16)*_explode*1]) shift();
  else if($t>_t16)                                               shift();

  if($t>_t16 && $t<=_t17) translate([0,0, ($t-_t17)*_explode]*2) nut_top();
  else if($t>_t17)                                               nut_top();

  if($t>_t17 && $t<=_t18) translate([0,-($t-_t18)*_explode]*2,0) nut_dmx();
  else if($t>_t18)                                               nut_dmx();

  if($t>_t18 && $t<=_t19) translate([0,0,-($t-_t19)*_explode*2.7]) washer_top();
  else if($t>_t18)                                                 washer_top();
  if($t>_t18 && $t<=_t19) translate([0,0,-($t-_t19)*_explode*3])   bolt_top();
  else if($t>_t18)                                                 bolt_top();
  if($t>_t18 && $t<=_t19) translate([0,0,-($t-_t19)*_explode*1])   washer_bottom();
  else if($t>_t18)                                                 washer_bottom();
  if($t>_t18 && $t<=_t19) translate([0,0,-($t-_t19)*_explode*3])   nut_bottom();
  else if($t>_t18)                                                 nut_bottom();

  if($t>_t19 && $t<=_t20)     translate([0,0,-($t-_t20)*_explode]) color("DimGray") bottom();
  else if($t>_t20)                                                 color("DimGray") bottom();

  if($t>_t20 && $t<=_t21)     translate([0,-($t-_t21)*_explode*1.5, 0]) MIDI_DIN_conn();
  else if($t>_t21)                                                      MIDI_DIN_conn();
  if($t>_t21 && $t<=_t22)     translate([0,-($t-_t22)*_explode*3.5, 0]) nut_MIDI();
  else if($t>_t22)                                                      nut_MIDI();

  if($t>_t23 && $t<=_t24)  bolt_case(-($t-_t24)*_explode*2);
  else if($t>_t24)                           bolt_case(0);

  }

else {
  translate([0,0,0]) pcb(_hole);
  translate([0,0,-_explode*0.8]) usb_wire();
  translate([0,0,-_explode*1.6]) teensy();
  translate([0,0,-_explode*1]) mic();
  translate([0,0,-_explode*2]) keyboard();
  translate([0,0,-_explode*1]) connect();
  translate([0,0, _explode*1]) usb();
  translate([0,0, _explode*1]) audio();
  translate([0,0, _explode*1]) dmx();
  translate([0,0,-_explode*2]) encoder();
  translate([0,0,-_explode*3]) display();
  translate([0,0,-_explode*3]) flex_wire();
  translate([0,0,-_explode*4]) fsr();
  translate([0,0,-_explode*5]) flex_led();
  translate([0,0,-_explode*5]) neopixel_data();
  translate([0,0,-_explode*5]) neopixel_wire();
  translate([0,0,-_explode*6]) neopixel_ring();
  translate([0,0,-_explode*10.5]) nut_top();
  translate([0,0, _explode*1.1]) washer_top();
  translate([0,0, _explode*2 ]) bolt_top();
  translate([0,0, _explode*2.2]) nut_bottom();
  translate([0,0, _explode*0.6]) washer_bottom();
  translate([0,0,-_explode*8]) color("DimGray") case();
  translate([0,0,-_explode*2]) shift();
  translate([0,_explode*1.5,-_explode*8]) nut_dmx();
  translate([0,-_explode*0.685, _explode*2.5]) color("DimGray") bottom();
  translate([0, _explode*1.5, _explode*2.5]) MIDI_DIN_conn();
  translate([0, _explode*3.5, _explode*2.5]) nut_MIDI();
  bolt_case(_explode*5);
  translate([0,0,-_explode*8]) folio();
  if(_explode==10) color("red") doku(4);
}}



module case() {

//      translate([ _W/2+10.1, -6.1/2 + 2.413, 12.3]) rotate([15.5,0,0]) cube([ 4.7, 7, 2.6],center=true);

// Stiffener   
  difference() {  
    union(){
      translate([_W-1.97, 1.3, _sc+9.2]) rotate([0,0,45]) cube([5.8, 2.9, 14],center=true); 
      translate([1.97, 1.3, _sc+9.2]) rotate([0,0,-45]) cube([5.8, 2.9, 14],center=true);
    } 
    translate([_W-1.97, 1.3, _sc+1.4]) rotate([-45,0,45]) cube([5.8, 2.9, 8],center=true); 
    translate([1.97, 1.3, _sc+1.4]) rotate([-45,0,-45]) cube([5.8, 2.9, 14],center=true); 
    // screw holes for M2
    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);
    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);
    bottom_case_cut();
    pcb_cutout();
    translate([ 0, 0, 0]) cube([_cutx, _cuty, 126],center=true); // cut model
  }

  difference() {  
    union(){
      translate([_W-1, 21, _sc-0.285 ]) cube([0.55, 40, 0.23],center=true); // 6x4 rgb leiste links
      translate([1, 21, _sc-0.285 ]) cube([0.55, 40, 0.23],center=true);    // 6x4 rgb leiste rechts
      translate([0.6, 21, _sc+0.2 ]) rotate([0,40,0]) cube([1.5, 40, 0.3],center=true);    // 6x4 rgb leiste rechts
      translate([_W-0.6, 21, _sc+0.2 ]) rotate([0,-40,0]) cube([1.5, 40, 0.3],center=true);    // 6x4 rgb leiste rechts
    }
    translate([ 0, 0, 0]) cube([_cutx, _cuty, 126],center=true); // cut model
  }
  
  difference() {  
// case  
    hull(){
      translate([_W+_wt, -_wt+0.5, _sp ]) sphere(_sp);
      translate([-_wt, -_wt+0.5, _sp ]) sphere(_sp);
      translate([_W+_wt, -_wt-3, _Hf+_dispt-9.2 ]) sphere(_sp);
      translate([-_wt, -_wt-3, _Hf+_dispt-9.2 ]) sphere(_sp);
      translate([_W+_wt, _L+_wt+1, _sp ]) sphere(_sp);
      translate([-_wt, _L+_wt+1, _sp ]) sphere(_sp);
      translate([_W+_wt, _L+_wt+1, _Hb+_dispt-9.2 ]) sphere(_sp);
      translate([-_wt, _L+_wt+1, _Hb+_dispt-9.2 ]) sphere(_sp);
    }

// cut out left and right for foil 
    hull(){
      translate([1, 3.33, _sc+0.65 ]) sphere(0.75);
      translate([1, 38.6, _sc+0.65 ]) sphere(0.75);
      translate([1, 0.7, _sc+2.85 ]) sphere(0.75);
      translate([1, 41.6, _sc+2.85 ]) sphere(0.75); }
    hull(){
      translate([_W-1, 3.33, _sc+0.65 ]) sphere(0.75);
      translate([_W-1, 38.6, _sc+0.65 ]) sphere(0.75);
      translate([_W-1, 0.7, _sc+2.85 ]) sphere(0.75);
      translate([_W-1, 41.6, _sc+2.85 ]) sphere(0.75); }
    
    pcb_cutout();

// Teensy cut out on end of PCB
    translate([_W-35.3, _L-1.5, _top+_dispt-4.5 ]) cube([ 18, 1, 10]);
    translate([_W-35.3+3, _L-1.5, _top+_dispt-5.5  ]) cube([ 12, 10, 1]);
// SD-card cut out  
    translate([_W-35.3+3, _L-1.3, _top+_dispt-5 ]) rotate([-50,0,0]) cube([ 12, 10, 1]);
    hull(){
      translate([_W-35.3+3, _L+2.5, _top+_dispt-8.7  ]) cube([ 12, 1, 3.5]);
      translate([_W-35.3+3, _L+2.5, _top+_dispt-8.7  ]) rotate([40,0,0]) cube([ 12, 0.5, 4]); }

// NeoPixel Ring
    translate([27.94, 71.5, -5]) cylinder(h=10,r=22.3, $fn=500);
    translate([27.94, 71.5, _top-1 ]) cylinder(h=5,r1=22.3,r2=24, $fn=500);

// mic
    translate([_W-52.832, 79.248,-1]) cylinder(h=50, r=0.5);
    translate([_W-52.832, 79.248,_top]) cylinder(h=50, r=3.2);

// encoder
    translate([_W-7.62, 47.752, -5]) cylinder(h=10,r=3.1);
    translate([_W-48.26, 47.752, -5]) cylinder(h=10,r=3.1);
    translate([_W-7.62, 47.752, 0.35+_dispt-9.2]) cylinder(h=5,r=3.6);
    translate([_W-48.26, 47.752, 0.35+_dispt-9.2]) cylinder(h=5,r=3.6);

// shift
    translate([_W-7.62, 93.98, -5]) cylinder(h=10,r=3.1);
    translate([_W-48.36, 93.98, -5]) cylinder(h=10,r=3.1);

// 6x4 rgb cut out
    translate([_W/2, 35.56/2+3.175, -1]) cube([53.34, 35.56, 50],center=true); // top
//    translate([_W/2, 37.3/2+2.4, _sc]) cube([55.34, 37.3, 0.3],center=true); // foliage cut
/*    hull(){ // entrance for foliage
        translate([_W/2, 51.4, _sc+8.6]) rotate([36,0,0]) cube([55.34, 29, 0.1],center=true); 
        translate([_W/2, 50.6, _sc+8.6]) rotate([36,0,0]) cube([55.34, 29, 0.1],center=true); }
    hull(){
        translate([_W/2, 50.6, _sc+8.6]) rotate([36,0,0]) cube([53.34, 29, 0.1],center=true); 
        translate([_W/2, 45, _sc+8.6]) rotate([36,0,0]) cube([53.34, 29, 0.1],center=true); } 
    translate([_W/2, 42, _sc+3]) rotate([36,0,0]) cube([53.88, 2, 2],center=true); 
*/
    translate([_W/2, 38.3, _sc+2.6]) rotate([36,0,0]) cube([53.9, 10, 5],center=true); 
    translate([_W/2, 4.97, _sc+1.54]) rotate([50,0,0]) cube([53.9, 5, 8],center=true); 
    translate([_W/2, 21, _sc+1.54]) cube([53.9, 32, 5],center=true); 


// DMX  
    translate([ _W - 40.64, _L+10, _top + _dispt + _pcbt + 12.5 ]) rotate([90,0,0]) {
      cylinder(h=20,r=11, $fn=200);
      translate([9.9, 9.9, 0]) cylinder(h=20,r=1.6);
      translate([-9.9, -9.9, 0]) cylinder(h=20,r=1.6); } // r 2.6
      
// USB
    translate([ _W - 9.017, _L, _top + _dispt + 5.5 + _pcbt ]) 
      cube([12.5, 20, 11],center=true);
      
// Audio in
    translate([ _W - 24.257, _L+10, _top + _dispt + 3 + _pcbt ]) 
      rotate([90,0,0]) cylinder(h=20,r=3.1);

// cut lower USB/DMX/Audio
    translate([  _W - 27.356, _L, _top + _dispt + 3 + _pcbt ]) cube([24.59, 20, 50]);
    translate([  _W - 53.12, _L, _top + _dispt + 12.51 + _pcbt ]) cube([30, 20, 40]);
//    translate([  _W - 35, _L, _top + _dispt + 14 + _pcbt ]) rotate([0,55,0]) cube([15, 10, 20]);

// extend hole for PCB screw
    translate([ _W - 5.1, 58.55, 1]) cylinder(h=20, r=1.5);
    translate([ _W - 5.1, 58.55, -1.5]) cylinder(h=5, r1=4, r2=0);

// Neopixel 6x4
    translate([ _W-54.75-0.2, 0.5-0.2, 2.6]) cube([ 53.594+0.4, 40.767+0.2, 50]); // LEDs
//    translate([0, 0, 2.25+_dispt-9.8]) linear_extrude(height = 50) 
    offset(delta = 0.1) polygon(points=[
    [1.143, 4.572], [5.207, 0.508], [50.673, 0.508], [54.737, 4.572], 
    [54.737, 41.275], [1.143, 41.275], [1.143, 4.572] ]);

    translate([ 4.572, 3.3, 2.5+_dispt-_kh ]) sphere(r=1.2); 
    translate([ 50.673, 3.3, 2.5+_dispt-_kh ]) sphere(r=1.2); 

    bottom_case_cut();

// screw holes for M2
    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);
    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);
    translate([ 1.5, _L, _top+25]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);
    translate([ _W-1.5, _L, _top+25]) rotate([15.5,0,0]) cylinder(h=50, r=0.9);

// connector NeoPixel, RX3 & TX3
    translate([ 0, 0, _dispt-9.2]) {
      translate([ _W/2+0.125, -6.1/2 + 2.413, 10.3]) rotate([15.5,0,0]) cube([ 6*2.54+0.5+0.1, 7, 2.6],center=true);
      translate([ _W/2+0.125, -6.1/2 + 2.413, 15]) rotate([15.5,0,0]) cube([ 6*2.54+0.5+0.1, 10, 7],center=true);
// connector SDA & SCL
      translate([ _W-11.5+2.54/2-0.125, -6.1/2 + 2.413, 10.3]) rotate([15.5,0,0]) cube([ 4*2.54+0.5+0.1, 7, 2.6],center=true);
      translate([ _W-11.5+2.54/2-0.125, -6.1/2 + 2.413, 15]) rotate([15.5,0,0]) cube([ 4*2.54+0.5+0.1, 10, 7],center=true);
      translate([ _W-15, -6.1/2 + 2.413, 15.25]) rotate([15.5,0,0]) cube([ 4*2.54+0.25+0.1, 10, 7],center=true); }

// cut model ################################################# 
    translate([ 0, 0, 0]) cube([_cutx, _cuty, 126],center=true);
  }

  // PCB screw placement
  difference() { union() {
    translate([ _W - 5.1, 58.55, _top]) cylinder(h=_dispt-_disph, r=3);
    translate([ _W - 5.1, 58.55 -3, _top]) cube([5, 6, _dispt-_disph]);
    translate([ _W - 49.85, 58.55, _top]) cylinder(h=_dispt, r=3);
    translate([ _W - 49.85 -6, 58.55 -3, _top]) cube([6, 6, _dispt]); }
    
    translate([ _W - 5.1, 58.55, _top-1]) cylinder(h=20, r=1.5);
    translate([ _W - 49.85, 58.55, _top-1]) cylinder(h=20, r=1.3);
    translate([ _W - 49.85, 58.55 + 3.5, _top+_dispt]) cube([4,2,2],center=true);

    translate([ _W - 53.1, 57.15, _top + _dispt ]) sphere(0.8);
    translate([ _W - 53.1, 59.7, _top + _dispt ]) sphere(0.8);
  }
}


module bottom_case_cut() {
// bottom case cut
  hull() {
    translate([_W+_wt+_gap, -_wt-2, _Hf+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn+1]);
    translate([-_wt-_gap, -_wt-2, _Hf+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn+1]);
    translate([_W+_wt+_gap, _L+_wt+1.2, _Hb+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn+1]);
    translate([-_wt-_gap, _L+_wt+1.2, _Hb+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn+1]); }
}


module bottom() translate([ 0, 0, _dispt - 9.2]) {
// bottom case
  difference() {
    hull() {
      translate([_W+_wt+_gap, -_wt-2, _Hf+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn]);
      translate([-_wt-_gap, -_wt-2, _Hf+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn]);
      translate([_W+_wt+_gap, _L+_wt+1.2, _Hb+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn]);
      translate([-_wt-_gap, _L+_wt+1.2, _Hb+_sp-_btn ]) rotate([15.5,0,0]) cube([ 0.01, 0.01, _btn]);
    }

    // screw holes for M2
    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=1.05);
    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) cylinder(h=50, r=1.05);
    translate([ 1.5, _L, _top+25]) rotate([15.5,0,0]) cylinder(h=50, r=1.05);
    translate([ _W-1.5, _L, _top+25]) rotate([15.5,0,0]) cylinder(h=50, r=1.05);

    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) translate([ 0, 0, 13.1]) cylinder(h=5, r=1.95);
    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) translate([ 0, 0, 13.1]) cylinder(h=5, r=1.95);
    translate([ 1.5, _L, _top+25]) rotate([15.5,0,0]) translate([ 0, 0, 18.6]) cylinder(h=5, r=1.95);
    translate([ _W-1.5, _L, _top+25]) rotate([15.5,0,0])  translate([ 0, 0, 18.6]) cylinder(h=5, r=1.95);
  }

  // stiffener below buttons
  translate([ -(_wt+_sp)/2+_gap*2, 0, 0 ]) {
    hull() {
      translate([ 5.715, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 5.715, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
    hull() {
      translate([ 14.605, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 14.605, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
    hull() {
      translate([ 23.495, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 23.495, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
    hull() {
      translate([ 32.385, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 32.385, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
    hull() {
      translate([ 41.275, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 41.275, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
    hull() {
      translate([ 50.165, 38, _top+_pcbt+9.2 ]) cube([2, 1, 13]);
      translate([ 50.165, 3, _top+_pcbt+9.2 ]) cube([2, 1, 2]); }
  }
    
// below connect
  translate([_W/2, -_wt-3, _Hf ]) rotate([0,90,0]) cylinder(h=6*2.54+0.25, r=_sp, center=true);
  translate([ _W/2, -2.55, 12.8]) rotate([15.7,0,0]) cube([ 6*2.54+0.25, 4, 3.25],center=true);

  translate([_W-14.04+2.54/2  , -_wt-3, _Hf ]) rotate([0,90,0]) cylinder(h=6*2.54+0.25, r=_sp, center=true);
  translate([ _W-14.04+2.54/2 , -2.55, 12.8]) rotate([15.7,0,0]) cube([ 6*2.54+0.25, 4, 3.25],center=true);

// USB/DMX/Audio
  hull() 
  {
    translate([-_wt+2.78, _L+_wt+1, _Hb+_dispt-9.2 ]) rotate([0,90,0]) cylinder(h=1 ,r=_sp);
    translate([_W+_wt-3.79, _L+_wt+1, _Hb+_dispt-9.2 ]) rotate([0,90,0]) cylinder(h=1 ,r=_sp);
  }
  difference() { union() {
      translate([ -_wt+2.78, _L+_wt+_gap, _Hb+_dispt-29.67 ]) cube([50.31, _btn-_gap, 20.5]);
      translate([ -_wt+28.55, _L+_wt+_gap, _Hb+_dispt-39.18 ]) cube([12.063, _btn-_gap, 20.5]);
      translate([ -_wt+28.78, _L+_wt+_gap-5, _Hb+_dispt-31.20 ]) rotate([17.45,0,0]) cube([24.31, _btn-_gap+5, 19]);
      translate([ -_wt+28.78, _L+_wt+_gap-5, _Hb+_dispt-31.20 ]) cube([24.31, _btn-_gap+5, 20.5]); 

      translate([ -_wt+2.78, _L+_wt+_gap, _Hb+_dispt-16 ]) rotate([45,0,0]) cube([50.31, 4, 6]);
  }
    // DMX  
    translate([ _W - 40.64, _L+10, _top + _dispt + _pcbt + 12.5 ]) rotate([90,0,0]) {
      cylinder(h=20,r=11);
      translate([9.9, 9.9, 0]) cylinder(h=20,r=1.6);
      translate([-9.9, -9.9, 0]) cylinder(h=20,r=1.6); } // r 2.6
    // Audio in
    translate([ _W - 24.257, _L+10, _top + _dispt + 3 + _pcbt ]) 
      rotate([90,0,0]) cylinder(h=20,r=3.1);
    // MIDI
    translate([41, 105, 35]) rotate([90,56,0]) {
      cylinder(h=20,r=7.7);
      translate([0, 11.175, 0]) cylinder(h=20,r=1.3);
      translate([0, -11.175, 0]) cylinder(h=20,r=1.3);}
  }
}


module MIDI_DIN_conn() {
  // MIDI
  color("grey") 
    translate([41, 105, 35]) rotate([90,56,0]) {
      difference() { union() { hull() { 
        translate([0, 0, 0.2]) cylinder(h=1.8,r=9.5);
        translate([0, 11.175, 0.2]) cylinder(h=1.8,r=3.2);
        translate([0, -11.175, 0.2]) cylinder(h=1.8,r=3.2);}
        translate([0, 0, 0.2]) cylinder(h=12,r=7.7);        
      }
      cylinder(h=10,r=7.3);
      translate([0, 11.175, 0]) cylinder(h=20,r=1.3);
      translate([0, -11.175, 0]) cylinder(h=20,r=1.3);
    }
    difference() { 
      translate([0, 0, 0.2]) cylinder(h=13.5,r=6);
      translate([0, 4, 0]) cylinder(h=6,r=0.9);
      translate([0, -4, 0]) cylinder(h=6,r=0.9);
      translate([-4, 0, 0]) cylinder(h=6,r=0.9);
      translate([-2.85, 2.85, 0]) cylinder(h=6,r=0.9);
      translate([-2.85, -2.85, 0]) cylinder(h=6,r=0.9);
      translate([5.5, 0, 5]) cube([2,2.2,10],center=true);
    }
    translate([0, 4, 12]) cylinder(h=6,r=0.9);
    translate([0, -4, 12]) cylinder(h=6,r=0.9);
    translate([-4, 0, 12]) cylinder(h=6,r=0.9);
    translate([-2.85, 2.85, 12]) cylinder(h=6,r=0.9);
    translate([-2.85, -2.85, 12]) cylinder(h=6,r=0.9);
    translate([5.5, 0, 15]) cube([1,2.2,6],center=true);
  }
}


module pcb_cutout() {
// beat counter PCB
  translate([0, 0, _top + _dispt ]) linear_extrude(height = 50) 
  offset(delta = _gap) polygon(points=[
  [4.57, 0], [1.65, 2.92], [1.65, 33.91], [0, 35.56], 
  [0, 92.2], [2.92, 95.123], [2.92, 99.95], [52.96, 99.95], 
  [52.96, 95.123], [55.88, 92.2], [55.88, 35.56], [54.23, 33.91], 
  [54.23, 2.92], [51.31, 0], [4.57, 0]]);
// beat counter PCB -1
  translate([0, 0, _top]) linear_extrude(height = 50) 
  offset(delta = -1) polygon(points=[
  [4.57, 0], [1.65, 2.92], [1.65, 33.91], [0, 35.56], 
  [0, 92.2], [2.92, 95.123], [2.92, 99.95], [52.96, 99.95], 
  [52.96, 95.123], [55.88, 92.2], [55.88, 35.56], [54.23, 33.91], 
  [54.23, 2.92], [51.31, 0], [4.57, 0]]);
}


module pcb(hole) {
// beat counter PCB
  difference() { union() { 
    color("lightgreen")   
    translate([0, 0, _top + _dispt]) linear_extrude(height = _pcbt)
    offset(delta = _gap) polygon(points=[
    [4.57, 0], [1.65, 2.92], [1.65, 33.91], [0, 35.56], 
    [0, 92.2], [2.92, 95.123], [2.92, 99.95], [52.96, 99.95], 
    [52.96, 95.123], [55.88, 92.2], [55.88, 35.56], [54.23, 33.91], 
    [54.23, 2.92], [51.31, 0], [4.57, 0]]);

    if(hole==1) {
      color("yellow") { 
        translate([ _W-23.495, 42.291, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-26.035, 42.291, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-28.575, 42.291, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-31.115, 42.291, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 39.751, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 42.291, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 47.371, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 49.911, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 57.531, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 60.071, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 62.611, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 65.151, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 67.691, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 70.231, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 72.771, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 75.311, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 77.851, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 80.391, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 95.631, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-16.637, 98.171, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ _W-35.941, 75.311, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 72.771, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 70.231, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 62.611, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 60.071, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 57.531, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 54.991, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-35.941, 52.451, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ _W-53.086, 75.692, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 73.152, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 70.612, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 68.072, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 65.532, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 62.992, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 60.452, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-53.086, 57.912, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ _W-6.35, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-8.89, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-11.43, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-13.97, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ _W-21.59, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-24.13, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-26.67, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-29.21, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-31.75, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-34.29, 2.413, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ _W-27.94, 66.04, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W-27.94, 68.58, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        
        translate([ _W - 10.5, 83.4, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W - 48.6, 67.6, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ _W - 16.2, 54.2, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        translate([ 17.3, 2.4, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ 38.8, 2.4, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ 13.5, 39.37, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 
        translate([ 42.5, 39.37, _top + _dispt-0.05 ]) cylinder(h=_pcbt+0.1,r=1); 

        for( i = [ 62.6: 2.54: 82]) { 
          translate([ _W - 4.5, i, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); }

        for( i = [ 39.8: 2.54: 100]) {
          translate([ _W - 18.7, i, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); 
          translate([ _W - 33.9, i, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); }

          translate([ _W - 21.24, 47.37, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); 
          translate([ _W - 21.24, 49.9, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); 
          translate([ _W - 21.24, 52.45, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); 

        for( i = [ 46.1: 2.54: 58]) {
          translate([ _W - 28.7, i, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1);
          translate([ _W - 30.74, i, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=1); }

        for( i = [ 5.13 : 2.5 : 12]) { 
          translate([ _W-i, 40.2, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.9); }
        for( i = [ 3.6 : 2.025 : 12]) { 
          translate([ _W-i, 54.7, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.9); }
        for( i = [ 45.77 : 2.5 : 52]) { 
          translate([ _W-i, 40.2, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.9); }
        for( i = [ 44.2 : 2.025 : 53]) { 
          translate([ _W-i, 54.7, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.9); }

        for( j = [ 5.715+8.89: 8.89: 50]) for( i = [ 7.62: 8.89: 35]) 
          translate([ j, i, _top + _dispt-0.01]) {
          translate([ 3.25, 2.3, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ 3.25, -2.3, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ -3.25, 2.3, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ -3.25, -2.3, 0 ]) cylinder(h=_pcbt+0.1, r=1); }
        for( j = [ 5.715: 44.45: 55]) for( i = [ 7.62: 8.89: 35]) 
          translate([ j, i, _top + _dispt]) {
          translate([ 2.3, 3.25, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ -2.3, 3.25, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ 2.3, -3.25, 0 ]) cylinder(h=_pcbt+0.1, r=1); 
          translate([ -2.3, -3.25, 0 ]) cylinder(h=_pcbt+0.1, r=1); }

        translate([ _W-52.578, 80.9, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.8);
        translate([ _W-52.578, 79.1, _top + _dispt-0.01 ]) cylinder(h=_pcbt+0.1,r=0.8);

        }
      }        
    }
    
    if(hole==1) {
      translate([ _W-49.85, 58.5, _top + _dispt-8 ]) cylinder(h=10,r=1.5); 
      translate([ _W-44.4, 58.5, _top + _dispt-8 ]) cylinder(h=10,r=1.5); 
      translate([ _W-4.4, 58.5, _top + _dispt-8 ]) cylinder(h=10,r=1.5); 
      translate([ _W-44.4, 84.5, _top + _dispt-8 ]) cylinder(h=10,r=1.5); 
      translate([ _W-4.4, 84.5, _top + _dispt-8 ]) cylinder(h=10,r=1.5); 

      translate([ _W-23.495, 42.291, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-26.035, 42.291, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-28.575, 42.291, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-31.115, 42.291, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 39.751, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 42.291, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 47.371, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 49.911, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 57.531, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 60.071, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 62.611, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 65.151, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 67.691, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 70.231, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 72.771, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 75.311, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 77.851, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 80.391, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 95.631, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-16.637, 98.171, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      translate([ _W-35.941, 75.311, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 72.771, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 70.231, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 62.611, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 60.071, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 57.531, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 54.991, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-35.941, 52.451, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      translate([ _W-53.086, 75.692, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 73.152, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 70.612, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 68.072, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 65.532, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 62.992, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 60.452, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-53.086, 57.912, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      translate([ _W-6.35, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-8.89, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-11.43, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-13.97, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      translate([ _W-21.59, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-24.13, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-26.67, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-29.21, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-31.75, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-34.29, 2.413, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      translate([ _W-27.94, 66.04, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W-27.94, 68.58, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      
      translate([ _W - 10.5, 83.4, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W - 48.6, 67.6, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W - 16.2, 54.2, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
     
      translate([ 17.3, 2.4, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ 38.8, 2.4, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ 13.5, 39.37, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ 42.5, 39.37, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      for( i = [ 62.6: 2.54: 82]) { 
        translate([ _W - 4.5, i, _top + _dispt-8 ]) cylinder(h=10,r=0.5); }

      for( i = [ 39.8: 2.54: 100]) {
        translate([ _W - 18.7, i, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
        translate([ _W - 33.9, i, _top + _dispt-8 ]) cylinder(h=10,r=0.5); }

      translate([ _W - 21.24, 47.37, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W - 21.24, 49.9, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 
      translate([ _W - 21.24, 52.45, _top + _dispt-8 ]) cylinder(h=10,r=0.5); 

      for( i = [ 46.1: 2.54: 58]) {
        translate([ _W - 28.7, i, _top + _dispt-6 ]) cylinder(h=8,r=0.5);
        translate([ _W - 30.74, i, _top + _dispt-6 ]) cylinder(h=8,r=0.5); }

      for( i = [ 5.13 : 2.5 : 12]) { 
        translate([ _W-i, 40.2, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
      for( i = [ 3.6 : 2.025 : 12]) { 
        translate([ _W-i, 54.7, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
      for( i = [ 45.77 : 2.5 : 52]) { 
        translate([ _W-i, 40.2, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
      for( i = [ 44.2 : 2.025 : 53]) { 
        translate([ _W-i, 54.7, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }

      for( j = [ 5.715+8.89: 8.89: 50]) for( i = [ 7.62: 8.89: 35]) 
        translate([ j, i, _top + _dispt]) {
        translate([ 3.25, 2.3, -2 ]) cylinder(h=4, r=0.5); 
        translate([ 3.25, -2.3, -2 ]) cylinder(h=4, r=0.5); 
        translate([ -3.25, 2.3, -2 ]) cylinder(h=4, r=0.5); 
        translate([ -3.25, -2.3, -2 ]) cylinder(h=4, r=0.5); }
      for( j = [ 5.715: 44.45: 55]) for( i = [ 7.62: 8.89: 35]) 
        translate([ j, i, _top + _dispt]) {
        translate([ 2.3, 3.25, -2 ]) cylinder(h=4, r=0.5); 
        translate([ -2.3, 3.25, -2 ]) cylinder(h=4, r=0.5); 
        translate([ 2.3, -3.25, -2 ]) cylinder(h=4, r=0.5); 
        translate([ -2.3, -3.25, -2 ]) cylinder(h=4, r=0.5); }
        
      translate([ _W-52.578, 80.9, _top + _dispt -2 ]) cylinder(h=5,r=0.5);
      translate([ _W-52.578, 79.1, _top + _dispt -2 ]) cylinder(h=5,r=0.5);
        
    }
  }
}

module teensy() {  
// Teensy
  color("green") 
  translate([ _W - 35.3, 38.4,  _top + _dispt -3 -2.5 ]) cube([17.9, 61, 3]);
  
  for( i = [ 39.8: 2.54: 100]) {
    translate([ _W - 18.7, i, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 
    translate([ _W - 33.9, i, _top + _dispt-6 ]) cylinder(h=8,r=0.5); }
  
    translate([ _W - 21.24, 47.37, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 
    translate([ _W - 21.24, 49.9, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 
    translate([ _W - 21.24, 52.45, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 

  for( i = [ 46.1: 2.54: 58]) {
    translate([ _W - 30.74, i, _top + _dispt-6 ]) cylinder(h=8,r=0.5); }
    
  color("lightgrey") 
    translate([ _W - 30.15, 37.2,  _top + _dispt -3 -2.6 ]) cube([7.6, 5, 2]);

  translate([ _W - 25.8, 39.6,  _top + _dispt -3 ]) cube([1.2, 2.8, 0.55]); // D-
  translate([ _W - 28.1, 39.6,  _top + _dispt -3 ]) cube([1.2, 2.8, 0.55]); // D+
}

module usb_wire() { 
  color("lightgrey") {
    translate([ _W-27.94, 66.04, _top + _dispt-1.3 ]) cylinder(h=3.3,r=0.5); // D-
    translate([ _W-25.2,  44.5, _top + _dispt-1.3 ]) rotate([90,0,0]) cylinder(h=2,r=0.5); // D-
    translate([ _W-25.2,  42.5, _top + _dispt-1.3 ]) rotate([90,0,0]) sphere(0.5); // D-
    translate([ _W-25.2,  41.7, _top + _dispt-2.1 ]) rotate([-45,0,0]) cylinder(h=1.15,r=0.5); // D-
    translate([ _W-25.2,  41.7, _top + _dispt-2.1 ]) rotate([90,0,0]) sphere(0.5); // D-
    translate([ _W-25.2,  41.7, _top + _dispt-2.1 ]) rotate([90,0,0]) cylinder(h=2,r=0.5); // D-
    translate([ _W-27.94, 68.58, _top + _dispt-1.3 ]) cylinder(h=3.3,r=0.5); // D+
    translate([ _W-27.5,  44.5, _top + _dispt-1.3 ]) rotate([90,0,0]) cylinder(h=2,r=0.5); // D-
    translate([ _W-27.5,  42.5, _top + _dispt-1.3 ]) rotate([90,0,0]) sphere(0.5); // D-
    translate([ _W-27.5,  41.7, _top + _dispt-2.1 ]) rotate([-45,0,0]) cylinder(h=1.15,r=0.5); // D-
    translate([ _W-27.5,  41.7, _top + _dispt-2.1 ]) rotate([90,0,0]) sphere(0.5); // D-
    translate([ _W-27.5,  41.7, _top + _dispt-2.1 ]) rotate([90,0,0]) cylinder(h=2,r=0.5); // D- 
  }
  color("brown") {
    translate([ _W-27.94, 66.04, _top + _dispt-1.3 ]) cylinder(h=1,r=0.7); // D-
    translate([ _W-27.94, 66.04, _top + _dispt-1.3 ]) sphere(0.7); // D-
    translate([ _W-27.94, 66.04, _top + _dispt-1.3 ]) rotate([45,90,0]) cylinder(h=3.87,r=0.7); // D-
    translate([ _W-25.2,  63.3, _top + _dispt-1.3 ]) sphere(0.7); // D-
    translate([ _W-25.2,  63.3, _top + _dispt-1.3 ]) rotate([90,0,0]) cylinder(h=20,r=0.7); // D-
    translate([ _W-27.94, 68.58, _top + _dispt-1.3 ]) cylinder(h=1,r=0.7); // D+
    translate([ _W-27.94, 68.58, _top + _dispt-1.3 ]) sphere(0.7); // D-
    translate([ _W-27.94, 68.58, _top + _dispt-1.3 ]) rotate([134.8,90,0]) cylinder(h=3.9,r=0.7); // D-
    translate([ _W-30.7,  65.8, _top + _dispt-1.3 ]) sphere(0.7); // D-
    translate([ _W-30.7,  65.8, _top + _dispt-1.3 ]) rotate([45,90,0]) cylinder(h=4.53,r=0.7); // D-
    translate([ _W-27.5,  62.6, _top + _dispt-1.3 ]) sphere(0.7); // D-
    translate([ _W-27.5,  62.6, _top + _dispt-1.3 ]) rotate([90,0,0]) cylinder(h=19.3,r=0.7); // D- 
  }
}
  
module mic() {
  translate([ _W-52.578, 80.01, _top + _dispt -4 ]) color("lightgrey") cylinder(h=4,r=3);
  translate([ _W-52.578, 80.01, _top + _dispt -4.5]) color("black") cylinder(h=0.5, r=3);
  translate([ _W-52.578, 80.9, _top + _dispt -3 ]) color("lightgrey") cylinder(h=5,r=0.5);
  translate([ _W-52.578, 79.1, _top + _dispt -3 ]) color("lightgrey") cylinder(h=5,r=0.5);
}

module display() {  
// Display
  difference() { color("lightblue") {
    translate([ _W - 4.4, 58.5, _top + _dispt -7.2 ]) cylinder(h=7.2,r=2.5);
    translate([ _W - 4.4, 84.5, _top + _dispt -9.2 ]) cylinder(h=9.2,r=2.5);
    translate([ _W - 44.4, 58.5, _top + _dispt -9.2 ]) cylinder(h=9.2,r=2.5);
    translate([ _W - 44.4, 84.5, _top + _dispt -9.2 ]) cylinder(h=9.2,r=2.5);
    translate([ _W - 47.1, 55.8,  _top + _dispt -1.6 -6 ]) cube([45.5, 31.4, 1.6]);
    translate([ _W - 40.9, 58.5,  _top + _dispt -1.7 -1.6 -5.99 ]) cube([29.2, 26.1, 1.7]); }
    translate([ _W - 4.4, 58.5, _top + _dispt -13 ]) cylinder(h=15.5,r=1.5);
    translate([ _W - 10.5, 83.4, _top + _dispt -13 ]) cylinder(h=15.5,r=1); }
  color("blue") translate([ _W - 40.9, 58.5,  _top + _dispt -1.7 -1.6 -6 ]) cube([26.1, 26.1, 1.7]);
  for( i = [ 62.6: 2.54: 82]) { translate([ _W - 4.5, i, _top + _dispt-8 ]) cylinder(h=10,r=0.5); }
}
 
 module neopixel_ring() { 
// NeoPixel Ring
  difference() { union() {
    translate([ _W - 27.94, 71.5, _top + _dispt -1.1 -9.5 ]) {
    color("LightSeaGreen") cylinder(h=1.1,r=22.2);
    for( i = [ 0: 22.5: 360]) rotate(i) translate([0, 19, 0.7 ]) difference() { 
      color("white") translate([ 0, 0, -1.65]) cube([ 5, 5, 2.1],center=true);
      color("yellow") translate([ 0, 0, -4.5]) cylinder(h=2,r=2); }}
    color("yellow") {
    translate([ _W - 10.5, 83.3, _top + _dispt -10.7 ]) cylinder(h=1.3,r=1); 
    translate([ _W - 48.6, 67.5, _top + _dispt -10.7 ]) cylinder(h=1.3,r=1); 
    translate([ _W - 16.2, 54.1, _top + _dispt -10.7 ]) cylinder(h=1.3,r=1); 
    translate([ _W - 23.9, 92.2, _top + _dispt -10.7 ]) cylinder(h=1.3,r=1); }}
    translate([ _W - 27.94, 71.5, _top + _dispt -15 ]) cylinder(h=10,r=16);  
    translate([ _W - 10.5, 83.3, _top + _dispt -13 ]) cylinder(h=15,r=0.5); 
    translate([ _W - 48.6, 67.5, _top + _dispt -13 ]) cylinder(h=15,r=0.5); 
    translate([ _W - 16.2, 54.1, _top + _dispt -13 ]) cylinder(h=15,r=0.5); 
    translate([ _W - 23.9, 92.2, _top + _dispt -13 ]) cylinder(h=4.6,r=0.5); 
  } 
}

module neopixel_wire() {
  translate([ _W - 10.5, 83.3, _top + _dispt -11.4 ]) cylinder(h=13.5,r=0.5); 
  translate([ _W - 48.6, 67.5, _top + _dispt -11.4 ]) cylinder(h=13.5,r=0.5); 
  translate([ _W - 16.2, 54.1, _top + _dispt -11.4 ]) cylinder(h=13.5,r=0.5); 
}

module neopixel_data() {
// Neopixel data wire 
  color("lightgrey") {
    translate([ _W - 23.9, 92.2, _top + _dispt -11.4 ]) cylinder(h=3,r=0.5); 
    translate([ _W - 2.5, 39.37, _top + _dispt -11 ]) cylinder(h=2.6 ,r=0.5); }
  color("brown") {
    translate([ _W - 23.9, 92.3, _top + _dispt -9.25 ]) cylinder(h=0.8,r=0.7); 
    translate([ _W - 23.9, 92.3, _top + _dispt -8.4 ]) sphere(0.7);
    translate([ _W - 23.9, 92.3, _top + _dispt -8.4 ]) rotate([25,90,0]) cylinder(h=17.55,r=0.7); 
    translate([ _W - 8, 84.88, _top + _dispt -8.4 ]) sphere(0.7);
    translate([ _W - 8, 84.9, _top + _dispt -8.4 ]) rotate([90,0,-6.2]) cylinder(h=39.6 ,r=0.7); 
    translate([ _W - 12.28, 45.5, _top + _dispt -8.4 ]) sphere(0.7);
    translate([ _W - 12.28, 45.5, _top + _dispt -8.4 ]) rotate([32.078,90,0]) cylinder(h=11.55 ,r=0.7); 
    translate([ _W - 2.5, 39.37, _top + _dispt -8.4 ]) sphere(0.7);
    translate([ _W - 2.5, 39.37, _top + _dispt -9.4 ]) cylinder(h=1 ,r=0.7); }
}

module encoder() {
// Encoder
  color("lightgrey") {
    translate([_W-7.62, 47.752, _top + _dispt + _pcbt - 25 ]) cylinder(h=20,r=3);
    translate([_W-7.62, 47.752, _top + _dispt - 12 ]) cylinder(h=12,r=3.45);
    translate([_W-7.62, 47.752-0.35, _top + _dispt + _pcbt - 5 ]) cube([12.6, 14, 6.5],center=true);
    for( i = [ 5.13 : 2.5 : 12]) { 
      translate([ _W-i, 40.2, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
    for( i = [ 3.6 : 2.025 : 12]) { 
      translate([ _W-i, 54.7, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
  
    translate([_W-48.26, 47.752, _top + _dispt + _pcbt - 25 ]) cylinder(h=20,r=3);
    translate([_W-48.26, 47.752, _top + _dispt - 12 ]) cylinder(h=12,r=3.45);
    translate([_W-48.26, 47.752-0.35, _top + _dispt + _pcbt - 5 ]) cube([12.6, 14, 6.5],center=true); 
    for( i = [ 45.77 : 2.5 : 52]) { 
      translate([ _W-i, 40.2, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
    for( i = [ 44.2 : 2.025 : 53]) { 
      translate([ _W-i, 54.7, _top + _dispt-4 ]) cylinder(h=6,r=0.5); }
    }
}

module dmx() {
// DMX  
  color("grey") 
  translate([ _W - 40.64, _L+3.15, _top + _dispt + _pcbt + 12.5 ]) rotate([90,0,0]) {
    difference() { union() {
      cylinder(h=23,r=10.85);
      translate([ 0, 0, 13.3]) cube([12,25,20.8],center=true); 
      difference() { hull(){
        translate([9.9, 9.9, 3]) cylinder(h=6.4,r=2.6);
        translate([-9.9, -9.9, 3]) cylinder(h=6.4,r=2.6); }
        translate([9.9, 9.9, 2]) cylinder(h=8,r=1.5);
        translate([-9.9, -9.9, 2]) cylinder(h=8,r=1.5); }}
      translate([ 0,0,-2 ]) cylinder(h=14,r=9.5); }
    difference() {
      translate([ 0,0,0 ]) cylinder(h=14,r=8);
      translate([ 4.5,0,-1 ]) cylinder(h=20,r=1.5);
      translate([ -4.5,0,-1 ]) cylinder(h=20,r=1.5);
      translate([ 0,-4.5,-1 ]) cylinder(h=20,r=1.5);
    }
  }
}

module usb() {      
// USB
  color("grey") translate([ _W - 9.017, _L-16.6/2+1, 17.9 + _pcbt ]) 
  difference() {
    cube([12.5, 16.6, 11],center=true);
    translate([ 0,2,0 ]) cube([10, 14, 8.6],center=true); }
}

module audio() {
// Audio in
  color("grey")difference() { union() {
    translate([ _W - 24.257, _L-6, 15.4 + _pcbt ]) cube([6.8, 12.4, 6],center=true); 
    translate([ _W - 24.257, _L+3.2, 15.4 + _pcbt ]) rotate([90,0,0]) cylinder(h=12.6,r=3); }
    translate([ _W - 24.257, _L+3.5, 15.4 + _pcbt ]) rotate([90,0,0]) cylinder(h=10,r=1.8); }
}

module flex_led() {
// flex PCB
  difference() { union() {
  color("orange") translate([0, 0, 2.6+_dispt-_kh]) linear_extrude(height = 0.1) 
  offset(delta = 0.2) polygon(points=[
  [1.143, 4.572], [5.207, 0.508], [50.673, 0.508], [54.737, 4.572], 
  [54.737, 41.275], [1.143, 41.275], [1.143, 4.572] ]);
  color("yellow") { 
  translate([ 4.5, 3.3, 2.5+_dispt-_kh ]) cylinder(h=0.3,r=1); 
  translate([ 51.2, 3.3, 2.5+_dispt-_kh ]) cylinder(h=0.3,r=1); 
  translate([ 4.5, 39.37, 2.5+_dispt-_kh ]) cylinder(h=0.3,r=1); 
  translate([ 51.2, 39.37, 2.5+_dispt-_kh ]) cylinder(h=0.3,r=1);   
  translate([ _W - 2.5, 39.37, 2.5+_dispt-_kh  ]) cylinder(h=0.3 ,r=1); }}
  translate([ 4.5, 3.3, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 51.2, 3.3, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 4.5, 39.37, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 51.2, 39.37, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5);   
  translate([ _W - 2.5, 39.37, _top + _dispt -11 ]) cylinder(h=2.6 ,r=0.5); }
  for( j = [ 5.715: 8.89: 55]) for( i = [ 7.62: 8.89: 35]) translate([ j, i, _top + _dispt]) {
    difference() { 
      color("white") translate([ 0, 0, -1.65-_kh]) cube([ 5, 5, 2.1],center=true); // LEDs
      color("yellow") translate([ 0, 0, -4.5-_kh]) cylinder(h=2,r=2); // LEDs
    }
  }
}

module flex_wire() {
  translate([ 4.5, 3.3, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 4.5, 3.3, _top + _dispt -8.5 ]) sphere(0.5);
  translate([ 4.5, 3.3, _top + _dispt -8.5 ]) rotate([3.45, 59.63, 0]) cylinder(h=14.86, r=0.5); 
  translate([ 17.3, 2.4, _top + _dispt -1 ]) sphere(0.5);
  translate([ 17.3, 2.4, _top + _dispt-1 ]) cylinder(h=3,r=0.5); 

  translate([ 51.2, 3.3, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 51.2, 3.3, _top + _dispt -8.5 ]) sphere(0.5);
  translate([ 51.2, 3.3, _top + _dispt -8.5 ]) rotate([3.82, -66.85, 0]) cylinder(h=13.5, r=0.5); 
  translate([ 38.8, 2.4, _top + _dispt -3.2 ]) sphere(0.5);
  translate([ 38.8, 2.4, _top + _dispt-3.2 ]) cylinder(h=5.5,r=0.5); 

  translate([ 4.5, 39.37, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 4.5, 39.37, _top + _dispt -8.5 ]) sphere(0.5);
  translate([ 4.5, 39.37, _top + _dispt -8.5 ]) rotate([0, 50.193, 0]) cylinder(h=11.7, r=0.5); 
  translate([ 13.5, 39.37, _top + _dispt -1 ]) sphere(0.5);
  translate([ 13.5, 39.37, _top + _dispt-1 ]) cylinder(h=3,r=0.5); 

  translate([ 51.2, 39.37, _top + _dispt -11 ]) cylinder(h=2.5,r=0.5); 
  translate([ 51.2, 39.37, _top + _dispt -8.5 ]) sphere(0.5);
  translate([ 51.2, 39.37, _top + _dispt -8.5 ]) rotate([0, -49.2, 0]) cylinder(h=11.5, r=0.5); 
  translate([ 42.5, 39.37, _top + _dispt -1 ]) sphere(0.5);
  translate([ 42.5, 39.37, _top + _dispt-1 ]) cylinder(h=3,r=0.5); 
}
  
module keyboard() {
// Keyboard
  for( j = [ 5.715: 8.89: 55]) for( i = [ 7.62: 8.89: 35]) 
    color("lightgrey") translate([ j, i, _top + _dispt]) {
    translate([ 0, 0, -1.75]) cube([6,6,3.5],center=true); // keys
    translate([ 0, 0, -_kh]) cylinder(h=_kh, r=1.8); }
  for( j = [ 5.715+8.89: 8.89: 50]) for( i = [ 7.62: 8.89: 35]) 
    color("lightgrey") translate([ j, i, _top + _dispt]) {
    translate([ 3.25, 2.3, -2 ]) cylinder(h=4, r=0.5); 
    translate([ 3.25, -2.3, -2 ]) cylinder(h=4, r=0.5); 
    translate([ -3.25, 2.3, -2 ]) cylinder(h=4, r=0.5); 
    translate([ -3.25, -2.3, -2 ]) cylinder(h=4, r=0.5); }
  for( j = [ 5.715: 44.45: 55]) for( i = [ 7.62: 8.89: 35]) 
    color("lightgrey") translate([ j, i, _top + _dispt]) {
    translate([ 2.3, 3.25, -2 ]) cylinder(h=4, r=0.5); 
    translate([ -2.3, 3.25, -2 ]) cylinder(h=4, r=0.5); 
    translate([ 2.3, -3.25, -2 ]) cylinder(h=4, r=0.5); 
    translate([ -2.3, -3.25, -2 ]) cylinder(h=4, r=0.5); }
}

module connect() {
// connect
  color("grey") translate([ _W/2, -6.1/2 + 2.413, 1.1+_dispt]) 
  rotate([15.5,0,0]) { difference() {
    cube([ 6*2.54+0.25, 6.1, 2.5],center=true);
    translate([ -2.54*2-2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ -2.54*1-2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ -2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ 2.54*2+2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ 2.54*1+2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ 2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true); }}
  
  color("grey") translate([ _W-11.5+2.54/2, -6.1/2 + 2.413, 1.1+_dispt]) 
  rotate([15.5,0,0]) { difference() { 
    cube([ 4*2.54+0.25, 6.1, 2.5],center=true);
    translate([ -2.54*1-2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ -2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ 2.54*1+2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true);
    translate([ 2.54/2, -3, 0 ]) cube([ 1.5, 8, 1.5],center=true); }}

  translate([ _W-6.35, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-8.89, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-11.43, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-13.97, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 

  translate([ _W-21.59, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-24.13, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-26.67, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-29.21, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-31.75, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
  translate([ _W-34.29, 2.413, _top + _dispt-2 ]) cylinder(h=4,r=0.5); 
}

module fsr() {
// pressure sensitive resistor Interlink 406
  translate([ 0, 0, 0.3-_kh+_dispt ]){ color("grey") {
    translate([ _W-16.5, 45, 5.5 ]) cube([ 0.46, 7.62, 5]);
    difference() { 
      translate([ _W-18.04, 45+7.62, 5.495 ]) rotate([90,0,0]) cylinder(h=7.62, r=2);
      translate([ _W-18.04, 45+8,    5.495 ]) rotate([90,0,0]) cylinder(h=9, r=1.54);
      translate([ _W-20.5, 44,  5.5 ]) cube([ 5, 10, 3]);
      translate([ _W-21.2, 44,  3 ]) rotate([0,10,0]) cube([ 2.65, 10, 3]); }
  translate([ 0.6, 0, -0.04]) difference() { 
    translate([ 17.04, 45+7.62, 5.5 ]) rotate([90,0,0]) cylinder(h=7.62, r=2);
    translate([ 17.04, 45+8,    5.5 ]) rotate([90,0,0]) cylinder(h=9, r=1.54);
    translate([ 17.3, 44,  3 ]) cube([ 3, 10, 5]);
    translate([ 17, 44,  3 ]) cube([ 3, 10, 3]); }
  translate([ _W-38.1, 45,  7 ]) rotate([0,10,0]) cube([ 20, 7.62, 0.46]);
  difference() { union() {
    translate([ _W-38.3, 45,  3.46 ]) cube([ 14.5, 7.62, 0.46]);
    translate([ _W/2, 48, 2.65 ]) cube([ 7.62, 10, 0.46],center=true); }
    translate([ _W/2+1.95, 51,  3.2 ]) rotate([0,0,45]) cube([ 6, 14, 2],center=true); }
  difference() { 
    translate([ 24, 45+7.62, 3.17 ]) rotate([90,0,45]) cylinder(h=11, r=0.75);
    translate([ 24, 45+7.62, 3.17 ]) rotate([90,0,45]) cylinder(h=11, r=0.29);
    translate([ _W/2+1.95, 46,  3.2 ]) rotate([0,0,45]) cube([ 1, 20, 2],center=true);
    translate([ _W/2-4.31, 52,  2.5 ]) cube([ 1, 2, 1],center=true);
    translate([ _W/2+4, 44.5,  3.5 ]) cube([ 2, 1, 1],center=true); }
  translate([ _W/2, 22.2,  2.65 ]) cube([ 43.7, 43.7, 0.46],center=true); }
  color("blue") translate([ _W/2-24, 21.3,  2.65 ]) cube([ 4, 34, 0.46],center=true); 
  color("blue") translate([ _W/2+24, 21.3,  2.65 ]) cube([ 4, 34, 0.46],center=true); }

  translate([ _W-16.637, 47.371, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 
  translate([ _W-16.637, 49.911, _top + _dispt-6 ]) cylinder(h=8,r=0.5); 
}

module nut_top() color("lightgrey") {
  translate([ _W - 5.1, 58.55, 1]) cylinder(h=17, r=1.5);
  difference() { 
    translate([ _W - 5.1, 58.55, -1.5]) cylinder(h=5, r1=4, r2=0);
    translate([ _W - 5.1, 58.55, -4.9]) cylinder(h=4.95, r=5); 
    translate([ _W - 5.1, 58.55, -4.9]) cylinder(h=6, r=1.5, $fn=6); 
    }
}  

module washer_top() color("Chocolate") {
  difference() { 
    translate([ _W-5.1, 58.55, _top+_pcbt+_dispt ]) cylinder(h=1, r=3);
    translate([ _W-5.1, 58.55, _top+_pcbt+_dispt ]) cylinder(h=2, r=1.5);
  }
}  

module bolt_top() color("lightgrey") {
  difference() { 
    translate([ _W-5.1, 58.55, _top+_pcbt+_dispt+1.1 ]) cylinder(h=2.5, r=3.2, $fn=6);
    translate([ _W-5.1, 58.55, _top+_pcbt+_dispt+1.1 ]) cylinder(h=3, r=1.4);
  }
}

module washer_bottom() color("Chocolate") {
  difference() { 
    translate([ _W-49.85, 58.55, _top+_pcbt+_dispt ]) cylinder(h=1, r=3);
    translate([ _W-49.85, 58.55, _top+_pcbt+_dispt ]) cylinder(h=2, r=1.5);
  }
}  

module nut_bottom() color("lightgrey") {
  translate([ _W-49.85, 58.5, _top + _dispt-10 ]) cylinder(h=14,r=1.5); 
  difference() { 
    translate([ _W-49.85, 58.55, _top+_pcbt+_dispt+1.1 ]) cylinder(h=2.5, r=3);
    translate([ _W-49.85-2, 58.55-2.7, _top+_pcbt+_dispt+2.5 ]) rotate(45)cube([7,1,5]);
  }
}  

module bolt_case(_expl) color("lightgrey") {
    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) translate([ 0, 0, _expl]) cylinder(h=13, r=0.9);
    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) translate([ 0, 0, _expl]) cylinder(h=13, r=0.9);
    translate([ 1.5, _L, _top+25]) rotate([15.5,0,0]) translate([ 0, 0, _expl]) cylinder(h=19, r=0.9);
    translate([ _W-1.5, _L, _top+25]) rotate([15.5,0,0]) translate([ 0, 0, _expl]) cylinder(h=19, r=0.9);

    translate([ 2, 2.7, _top]) rotate([15.5,0,0]) difference() {
      translate([ 0, 0, 12.8+_expl]) cylinder(h=1.2, r=1.9);
      translate([ -2, -2.3, 13+_expl]) rotate(45)cube([5,0.5,2]); }

    translate([ _W-2, 2.7, _top]) rotate([15.5,0,0]) difference() { 
      translate([ 0, 0, 12.8+_expl]) cylinder(h=1.2, r=1.9);
      translate([ -2, -2.3, 13+_expl]) rotate(45)cube([5,0.5,2]); }
    
    translate([ 1.5, _L, _top+25]) rotate([15.5,0,0]) difference() {
      translate([ 0, 0, 18.3+_expl]) cylinder(h=1.2, r=1.9);
      translate([ -2, -2.3, 18.5+_expl]) rotate(45)cube([5,0.5,2]); }
    
    translate([ _W-1.5, _L, _top+25]) rotate([15.5,0,0]) difference() {
      translate([ 0, 0, 18.3+_expl]) cylinder(h=1.2, r=1.9);
      translate([ -2, -2.3, 18.5+_expl]) rotate(45)cube([5,0.5,2]); }
}

module nut_dmx() color("lightgrey") {
  translate([ _W-40.64, _L+3.15, _top + _dispt + _pcbt + 12.5 ]) rotate([90,0,0]) {
  translate([9.9,9.9,0]) {cylinder(h=10,r=1.5);
  difference() {
    translate([0,0,-2.5 ]) cylinder(h=2.5, r=3);
    translate([-3,-3.6,-3 ]) rotate(45)cube([8,1,1.8]); }}
  }
  translate([ _W-40.64, _L+3.15, _top + _dispt + _pcbt + 12.5 ]) rotate([90,0,0]) {
  translate([-9.9,-9.9,0.1]) {cylinder(h=10,r=1.5);
  difference() {
//    translate([0,0,0 ]) cylinder(h=3,r1=3, r2=0);
//    translate([0,0,0 ]) cylinder(h=3,r=2,$fn=6); }}
    translate([0,0,-2.5 ]) cylinder(h=2.5, r=3);
    translate([-3,-3.6,-3 ]) rotate(45)cube([8,1,1.8]); }}
  }
}


module nut_MIDI() color("lightgrey") {
  translate([ _W-15.5, _L+4.9, _top + _dispt + _pcbt + 17.35 ]) rotate([90,0,0]) {
  translate([9.9,9.9,0]) {cylinder(h=12,r=1.5);
  difference() {
    translate([0,0,-2.5 ]) cylinder(h=2.5, r=3);
    translate([-3,-3.6,-3 ]) rotate(45)cube([8,1,1.8]); }}
  }
  translate([ _W-14.25, _L+4.9, _top + _dispt + _pcbt + 24.65 ]) rotate([90,0,0]) {
  translate([-9.9,-9.9,0.1]) {cylinder(h=12,r=1.5);
  difference() {
    translate([0,0,-2.5 ]) cylinder(h=2.5, r=3);
    translate([-3,-3.6,-3 ]) rotate(45)cube([8,1,1.8]); }}
  }
}


module folio() {
  color("lightcyan",0.5) translate([_W/2, 37.3/2+2.4, _sc]) cube([55, 37, 0.2],center=true);

//  for( j = [ 5.715: 8.89: 55]) 
  for( i = [ 10.15: 8.89: 50]) {
    color("black") translate([_W-i, 37.3/2+2.4, _sc]) cube([0.2, 37, 0.22],center=true); }
  for( i = [ 12.06: 8.89: 35]) {
    color("black") translate([_W/2, i, _sc]) cube([55, 0.2, 0.22],center=true);
  }
}

module doku(_size) rotate([270,0,90]) {
  translate([61, 95, -51]) linear_extrude(height = 0.1)  text("M3", size = _size);
  translate([62, -38.2, -51]) linear_extrude(height = 0.1)  text("M3", size = _size);
  translate([61, -35, -6]) linear_extrude(height = 0.1)  text("M3", size = _size);
  translate([122, 61.5, -5.5]) linear_extrude(height = 0.1)  text("M3", size = _size);
  translate([122, 41.6, -25.3]) linear_extrude(height = 0.1)  text("M3", size = _size);

  translate([83.5, -2, -3.4]) linear_extrude(height = 0.1)  text("Mic", size = _size);

  translate([-9, -52, -2]) linear_extrude(height = 0.1) rotate(-15.5) text("M2", size = _size);
  translate([-9, -52, -53.8]) linear_extrude(height = 0.1) rotate(-15.5) text("M2", size = _size);
  translate([87, -82, -2]) linear_extrude(height = 0.1) rotate(-15.5) text("M2", size = _size);
  translate([87, -82, -53.8]) linear_extrude(height = 0.1) rotate(-15.5) text("M2", size = _size);

  translate([54.5, 60.5, -28]) linear_extrude(height = 0.1)  text("Neopixel Ring", size = _size);
  translate([16, 80, -28]) linear_extrude(height = 0.1)  text("Foil", size = _size);
  translate([3, 50, -28]) linear_extrude(height = 0.1)  text("Neopixel Matrix", size = _size);
  translate([5, 38, -28]) linear_extrude(height = 0.1)  text("FSR-Pressure", size = _size);
  translate([61, 10, -29]) linear_extrude(height = 0.1)  text("Teensy 3.6", size = _size);
  translate([56, 27, -29]) linear_extrude(height = 0.1)  text("Waveshare 3''", size = _size);
  translate([52, 15, -7.5]) linear_extrude(height = 0.1)  text("RGB Encoder", size = _size);
//  translate([52, 15, -48.5]) linear_extrude(height = 0.1)  text("RGB Encoder", size = _size);
  translate([104, -39, -16]) linear_extrude(height = 0.1)  text("DMX", size = _size);
  translate([103.5, -28.6, -31.7]) linear_extrude(height = 0.1)  text("Audio in", size = _size);
  translate([102, -31, -47]) linear_extrude(height = 0.1)  text("USB-B", size = _size);
  translate([121, -62, -41.5]) linear_extrude(height = 0.1)  text("MIDI-DIN", size = _size);
  translate([143, -55.8, -32]) linear_extrude(height = 0.1)  text("M3", size = _size);
  translate([143, -68.2, -50.7]) linear_extrude(height = 0.1)  text("M3", size = _size);
}

module shift() color("grey") {
// shift  
  translate([_W-7.62, 93.98, -0.5]) cylinder(h=9.5,r=3);   // Shift left
  translate([_W-7.62, 93.98, _top+_shift]) cylinder(h=5.8-_shift,r=3.7); // Shift left

  translate([_W-48.36, 93.98, -0.5]) cylinder(h=9.5,r=3);   // Shift right
  translate([_W-48.36, 93.98, _top+_shift]) cylinder(h=5.8-_shift,r=3.7); // Shift right
}












// Raspberry Pi3 case
// use this parameters for 4" HyperPixel
_t_wall = 1.6 ; // thickness outer walls; min = 1.6
_t_b    = 1.5 ; // thickness bottom
_lcd_c = 2.5 ;  // lcd cover thickness
_lcd_t = 1 ;    // thickness over glass
_lcd_f = 1 ;    // frame width inside display
_cg = 0.1 ;     // gap between case and cover, cover wall width will be reduced

_rpi_w  = 56 ;  // rpi width (56)
_rpi_l  = 85 ;  // rpi length (85)
_rpi_p = 0.2 ;  // rpi padding (0.2)
_rpi_t = 1.4 ;  // rpi pcb height (1.4)
_rpi_hole_l_offset = 58 ; // rpi length hole offset (58)
_inner_h = 12.8 ; // rpi inner height (12.8)
_h_rpi_offset = 2.5 + _t_b ; // inner screw support (2.5)
_hole_offset = 3.5 ; // distance to border of rpi (3.5) 
_outer_l = _t_wall*2 + _rpi_p*2 + _rpi_l ; // total outer length without lcd (_lcd_l)
_outer_w = _t_wall*2 + _rpi_p*2 + _rpi_w ; // total outer width without lcd (_lcd_w)
_outer_h = _inner_h+_h_rpi_offset+6 ; // 6 extra added
//$fn=50 ;
_sd_width = 12 ;   // sd card slot
_sd_depth = 2.8 ;  // sd card slot
_sd_inset = 2 ;  // sd card slot
_cut = 13.1 ;    // cut between lcd and case
_cutgap = 0.5 ;  // gap between case and lcd
_lcd_ext = 10 ; // case extension for 4" display
_lcd_w = 58.5 ; // 4" display width
_lcd_l = 97 ;   // 4" display length
_lcd_h = 6 ;    // 4" display height

// Screw standoffs
_standoff_hole_r = 1.5 ;
_standoff_r = 3.5 ;
_hole_inset_r = 2.6 ;
_screw_hold = 2 ;

part = "case"; // Which part to render (lcd, case, both)
//rotate([18,0,90]) translate([-1.9,-_L,-35]) show();
//translate([_t_wall*2+1.2, _t_wall*2+0.9, _h_rpi_offset]) rpi(); 

module show() {
    if(part == "lcd") { rotate([0,180,0]) 
        translate([_lcd_c,_lcd_c,-_outer_h-_lcd_h-_lcd_t]) lcd();} 
    else if(part == "case") { translate([0,0,0]) rpicase(); } 
    else { translate([_lcd_c,_lcd_c,0]) {lcd(); rpicase(); }}}


module lcd(padding = 0.2) {
    translate([-1, -1, _outer_h]) difference() {
        union() {
            cover(1, _cg);            
            translate([+1-_cg, +1-_cg, -_cut]) {
                cube([_t_wall*2+_rpi_p*2+_rpi_w+_cg*2, 
                _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l+_cg*2, _lcd_h+_lcd_t+_cut]);
            }   
        }
        translate([_t_wall+_lcd_f, _t_wall+_lcd_f, _lcd_h-_t_b]) 
            cube([_lcd_w-_lcd_f*2, _lcd_l-_lcd_f*2, _lcd_h+_t_b]); // lcd top cutout
        translate([_t_wall-padding, _t_wall-padding, -20]) 
            cube([_lcd_w+padding*2, _lcd_l+padding*2, _lcd_h+20]); // lcd inner cutout
        
        translate([1-_cg, 1-_cg, -_cut-1]) 
            cube([_t_wall*2+_rpi_p*2+_rpi_w+_cg*2, 4+_cg*2, 
            _lcd_h+_t_b+6.6+_cutgap]); // lcd standoff cutout
        translate([1-_cg, _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l-3-_cg, -_cut-1]) 
            cube([4+_cg*2, 4+_cg*2, _lcd_h+_t_b+6.6+_cutgap]); // lcd standoff cutout
        translate([_t_wall*2+_rpi_p+_rpi_w+_cg-3, 
        _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l-3-_cg, -_cut-1]) 
            cube([4+_cg*2, 4+_cg*2, _lcd_h+_t_b+6.6+_cutgap]); // lcd standoff cutout
        
// extra cutouts in the lcd lid
        translate([_t_wall, _lcd_l+_t_wall-1.8, -_lcd_t])
            cube([5, 3, 2+_lcd_t]); // lcd pcb cut
        translate([_t_wall, _lcd_l+_t_wall-2.5, -_lcd_t-19.5])
           rotate([-2,0,0]) cube([5, 3, 20]); // lcd pcb cut

        translate([_t_wall+_lcd_w-5, _lcd_l+_t_wall-1.8, -_lcd_t])    
            cube([5, 3, 2+_lcd_t]); // lcd pcb cut
        translate([_t_wall+_lcd_w-5, _lcd_l+_t_wall-2.5, -_lcd_t-19.5])    
           rotate([-2,0,0]) cube([5, 3, 20]); // lcd pcb cut

        translate([_t_wall+38.5, _lcd_l+_t_wall-2, -_lcd_t])    
            cube([6, 2.7, _lcd_h+_lcd_t]); // lcd cable cut
        translate([_t_wall+38.5, _lcd_l+_t_wall-2.7, -_lcd_t-19.5])    
            rotate([-2,0,0]) cube([6, 2.7, 20]); // lcd cable cut

        translate([11.79, 32.6+_t_wall, -13.6]) 
            rotate([0,-90,0]) cylinder(r=3.2,h=11); // audio cut   

// cutouts in the cover
        translate([3.5+_t_wall, -10.6+_t_wall, -17]) 
            cube([16.4, 12, 13.5]); // eth cut
        translate([22.75+_t_wall, -10, -16.4])
            cube([15.1, 12, 15.6]); // USB cut
        translate([40.75+_t_wall, -10, -16.4])
            cube([15.1, 12, 15.6]); // USB cut
        translate([-11.5+_t_wall, 70.2+_t_wall, -18.65])
            cube([10, 10.5, 6.5]); // micro usb cut  10.5 x 6.5
        translate([0.1, 71.75+_t_wall, -16.9]) musb_hole(); // micro usb cut
        translate([-10, 46.7+_t_wall, -15.9])
            cube([20, 14.6, 5.1]); // HDMI cut
        translate([0.82, 32.6+_t_wall, -13.6]) 
            rotate([0,-90,0]) cylinder(r=3.2,h=11); // audio cut r=3.2 
    }

    translate([2.5+_cg+_t_wall, _cg-_lcd_c, _outer_h-3.5]) 
        cube([16.4-_cg*2, _lcd_c+_t_wall-1.3, 5]); // eth extend
    
    translate([22.5+_cg+_t_wall, _cg-_lcd_c, _outer_h-0.8]) 
        cube([13.6-_cg*2, _lcd_c+_t_wall-1.3, 5]); // usb extend
    translate([22.5+_cg+_t_wall, _cg+2.5-_lcd_c, _outer_h-1.6]) 
        cube([13.6-_cg*2, _lcd_c+_t_wall-3.4, 2]); // usb hold extend

    translate([40.5+_cg+_t_wall, _cg-_lcd_c, _outer_h-0.8]) 
        cube([13.6-_cg*2, _lcd_c+_t_wall-1.3, 5]); // usb extend
    translate([40.5+_cg+_t_wall, _cg+2.5-_lcd_c, _outer_h-1.6]) 
        cube([13.6-_cg*2, _lcd_c+_t_wall-3.4, 2]); // usb hold extend

    snap(0);
}

module cover(corr = 0, _cg) {
    color("Gray")
    translate([-_lcd_c+corr, -_lcd_c+corr, -_outer_h]) difference() { 
        cube([_t_wall*2+_rpi_p*2+_rpi_w+_lcd_c*2, 
        _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l+_lcd_c*2, _outer_h+_lcd_h+_lcd_t]);
        translate([_lcd_c-_cg, _lcd_c-_cg, -1]) 
            cube([_t_wall*2+_rpi_p*2+_rpi_w+_cg*2, 
            _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l+_cg*2, _outer_h+_lcd_h+_lcd_t+2]);
        translate([_lcd_c, 0, 0]) sd_cut() ;
    }
}

module snap(_gap=0.05, _nose=0.8) {
    translate([-_cg, (_outer_l+_lcd_ext)/2-10-_gap*5, -_gap/2]) 
        cube([_nose+_gap+_cg, 20+_gap*10, 1+_gap]); // snap
    translate([_outer_w-_nose-_gap, (_outer_l+_lcd_ext)/2-10-_gap*5, -_gap/2]) 
        cube([_nose+_gap+_cg, 20+_gap*10, 1+_gap]); // snap

    if(_lcd_ext > 0) {
        translate([_outer_w/2-5-_gap*5, -_cg, -_gap/2]) 
            cube([10+_gap*10, _nose+_gap+_cg, 1+_gap]); // snap
        translate([_outer_w/2-5-_gap*5, _outer_l+_lcd_ext-_nose-_gap, 
        -_gap/2+_t_b+_sd_depth]) 
            cube([10+_gap*10, _nose+_gap+_cg, 1+_gap]); // snap
    }
}

module rpicase() {
    difference() {
        union() {
            difference() {
                cube([_t_wall*2+_rpi_p*2+_rpi_w, _lcd_ext+_t_wall*2+_rpi_p*2+_rpi_l, _outer_h]);
                translate([_t_wall, _t_wall, _t_b])
                    cube([_rpi_p*2+_rpi_w, _lcd_ext+_rpi_p*2+_rpi_l, 
                    _outer_h-_t_b + _t_b+1 ]); // inner cut out

                _hole_padding = 0.2;

                sd_cut();
                
                translate([_t_wall+_rpi_p,_t_wall+_rpi_p,_h_rpi_offset+_rpi_t]) {
                    translate([40.43-_hole_padding/2, -2, 1.5])
                        rpiusb(padding=_hole_padding, extends=_t_wall, extraheight=10); // USB 1
                    translate([22.43-_hole_padding/2, -2, 1.5])
                        rpiusb(padding=_hole_padding, extends=_t_wall, extraheight=10); // USB 2
                    _ether_padding = _hole_padding + 0.2; 
                    translate([2.5-_ether_padding/2+.05, -2, 0.4])
                        ether(padding=_ether_padding, extends=_t_wall, extraheight=10); // Ethernet
                    translate([0, 31.4, 0.8]) rpiaudio(padding=0.25, extends=5, hole=false); // Audio
                    translate([0.1, 45.5, 1.5]) hdmi_hole(extends=_t_wall*2); // HDMI
                    translate([0.1,70.5, 0.5]) musb_hole(); // micro usb
                    translate([-12.7, 69, -1.5])
                        cube([10, 10.5, 6.5]); // micro usb cut  10.5 x 6.5
                }
                translate([-_t_wall, _t_wall, _outer_h-_cut-_cutgap]) {
                    translate([0, -_t_wall+4, 0]) // 0, 72.1, -14]
                        cube([_t_wall*2+_outer_w, _outer_l+_lcd_ext-8, 50]); // cut lower level
                    translate([_t_wall+4, _outer_l, 0]) 
                        cube([_outer_w-8, 10, 50]); // cut lower level
                }
            }
            
            // SD card slot support
            translate([_rpi_p + _rpi_w/2 - _sd_width/2, 
            _outer_l-_sd_inset-_lcd_ext-_t_wall, 0])
                cube([_sd_width+_t_wall*2, 11.6, _h_rpi_offset-2.5+1]);

            // SD card cover
            translate([_rpi_p + _rpi_w/2 - _sd_width/2, 
            _outer_l-_sd_inset, _t_b+_sd_depth]) {
                cube([_sd_width+_t_wall*2, _lcd_ext+_sd_inset, _t_wall]);
            translate([0,0,-_sd_depth])
                cube([_t_wall, _lcd_ext+_sd_inset, _sd_depth]);
            translate([_sd_width+_t_wall, 0, -_sd_depth])
                cube([_t_wall, _lcd_ext+_sd_inset, _sd_depth]);
            }

            // Screw standoffs
            translate([_t_wall+_rpi_p+_hole_offset,_t_wall+_rpi_p+_rpi_l-_hole_offset,0]) {
                difference() { hull() {
                    cylinder(r=_standoff_r,h=_h_rpi_offset);
                    translate([-_hole_offset-_rpi_p,-_standoff_r,0]) 
                        cube([1,_standoff_r*2,_h_rpi_offset]); }
                    translate([0,0,_t_b]) 
                        cylinder(r=_standoff_hole_r,h=_h_rpi_offset); }
            }

            translate([_t_wall+_rpi_p+_rpi_w-_hole_offset,
            _t_wall+_rpi_p+_rpi_l-_hole_offset,0]) {
                difference() { hull() {
                    cylinder(r=_standoff_r,h=_h_rpi_offset);
                    translate([_hole_offset+_rpi_p,-_standoff_r,0]) 
                        cube([1,_standoff_r*2,_h_rpi_offset]); }
                    translate([0,0,_t_b]) 
                        cylinder(r=_standoff_hole_r,h=_h_rpi_offset); }
            }

            translate([_t_wall+_rpi_p+_hole_offset,
            _t_wall+_rpi_p+_rpi_l-_hole_offset-_rpi_hole_l_offset,0]) {
                difference() { hull() {
                    cylinder(r=_standoff_r,h=_h_rpi_offset);
                    translate([-_hole_offset-_rpi_p,-_standoff_r,0]) 
                        cube([1,_standoff_r*2,_h_rpi_offset]); }
                    translate([0,0,_t_b]) 
                        cylinder(r=_standoff_hole_r,h=_h_rpi_offset); }
            }

            translate([_t_wall+_rpi_p+_rpi_w-_hole_offset,
            _t_wall+_rpi_p+_rpi_l-_hole_offset-_rpi_hole_l_offset,0]) {
                difference() { hull() {
                    cylinder(r=_standoff_r,h=_h_rpi_offset);
                    translate([_hole_offset+_rpi_p,-_standoff_r,0]) 
                        cube([1,_standoff_r*2,_h_rpi_offset]); }
                    translate([0,0,_t_b]) 
                        cylinder(r=_standoff_hole_r,h=_h_rpi_offset); }
            }
        }
        
        snap(0.05, 0.8); 
        
        // bottom through holes
        translate([_t_wall+_rpi_p, _t_wall+_rpi_p, - _screw_hold + _t_b]) {
            translate([_hole_offset, _rpi_l - _hole_offset, -13]) { 
                cylinder(r=_hole_inset_r,h=15.5); cylinder(r=_standoff_hole_r,h=_inner_h); }
            translate([_rpi_w-_hole_offset,_rpi_l-_hole_offset, -13]) { 
                cylinder(r=_hole_inset_r,h=15.5); cylinder(r=_standoff_hole_r,h=_inner_h); }
            translate([_hole_offset,_rpi_l-_hole_offset-_rpi_hole_l_offset, -13]) { 
                cylinder(r=_hole_inset_r,h=15.5); cylinder(r=_standoff_hole_r,h=_inner_h); }
            translate([_rpi_w-_hole_offset,_rpi_l-_hole_offset-_rpi_hole_l_offset, -13]) { 
                cylinder(r=_hole_inset_r,h=15.5); cylinder(r=_standoff_hole_r,h=_inner_h); }
        }
    }
}

module rpi() {
    difference() {
        union() {
            cube([_rpi_w, _rpi_l, _rpi_t]);
            translate([_rpi_w/2-_sd_width/2, _rpi_l-_t_wall, -_rpi_t-1]) 
                cube([_sd_width, _sd_depth+_rpi_p+_t_wall, 1]); // SD card
            translate([40.75, -2, _rpi_t]) { rpiusb(padding = 0); } // USB1
            translate([22.75, -2, _rpi_t]) { rpiusb(padding = 0); } // USB2
            translate([2.9, -2, _rpi_t]) ether(padding = 0); // Ethernet
            translate([0, 31.6, _rpi_t+0.9]) rpiaudio(padding = 0); // Audio
            translate([0, 45.75, _rpi_t+0.4]) hdmi(padding = 0); // HDMI
            translate([0, 70.7, _rpi_t]) musb(padding = 0); // Micro USB
            translate([0, 38.6, _rpi_t]) cube([22.5, 2.95, 5.7]); // Camera
            translate([_rpi_w/2-22.5/2, 79.55, _rpi_t]) cube([22.5, 2.95, 5.7]); }}}  // Video

module rpiusb(padding = 0.2, extends = 0.2, extraheight = 0) {
    _extra_width = (14.7-13.14);
    cube([13.14+2*padding,17.4+2*padding,15.3+padding+extraheight]);
    translate([-(14.7+2*padding-13.14-2*padding)/2,-extends+0.2,-_extra_width/2]) 
        cube([14.7+2*padding,extends,15.3+padding+_extra_width]);}

module ether(padding = 0.2, extends = 0, extraheight = 0) {
    translate([0,-extends,0]) cube([15.51+2*padding,21.45+extends,13.9+padding+extraheight]); }

module rpiaudio(padding = 0.4,extends=0,hole=true) {
    difference() {
        union() {
            translate([0,0,3]) rotate([0,-90,0]) cylinder(r=3+padding,h=2+extends);
        if (!hole) translate([-2-extends,-3-padding,3]) cube([10,6+padding*2,_cut]);
            translate([0,-3,0]) cube([11,6,6]); }
        if (hole) { translate([5,0,3]) rotate([0,-90,0]) cylinder(r=1.5,h=11); }}}

module hdmi() {
    difference() {
        union() { translate([1,0,0]) cube([10.7,14.5,6.4]);
        hull() {
            translate([-1,0,2]) cube([10.7,14.5,4.4]);
            translate([-1,1,1]) cube([10.7,12.5,5.4]); }}
        hull() {
            translate([-2,0.5,2.3]) cube([10.7,13.5,3.6]);
            translate([-2,1.6,1.5]) cube([10.7,11.7,2]); }}}

module hdmi_hole(padding = 0.4, extends = 5, outer_padding = 0.4) {
    union() {
        translate([-1-0.1,-padding,-padding])
            cube([10.7+0.1,14.5+padding*2,6.4+padding*2]);
        translate([-1-extends,-outer_padding,-outer_padding])
            cube([extends,14.5+outer_padding*2,6.4+outer_padding*2]); }}

module musb() {
    difference() { union() {
        translate([1,0,0]) cube([5.7,7.5,3]);
        hull() {
            translate([-1,0,1]) cube([5.7,7.5,2]);
            translate([-1,1,0.5]) cube([5.7,5.5,2]);} }
        hull() {
            translate([-1.1,0.2,1.2]) cube([5.7,7.1,1.6]);
            translate([-1.1,1.2,0.7]) cube([5.7,5.1,2]); }}}

module musb_hole(padding = 0.4, extends = 5, outer_padding = 0.4) {
    union() {
        translate([-1-0.1,-padding,-padding])
            cube([5.7+0.1,7.5+padding*2,3+padding*2]);
        translate([-1-extends,-outer_padding,-outer_padding])
            cube([extends,7.5+outer_padding*2,3+outer_padding*2]); }}

module sd_cut() {  // SD card slot cut
        translate([_t_wall + _rpi_p + _rpi_w/2 - _sd_width/2, 
        _outer_l-_t_wall-_rpi_p-_sd_inset, -1])
            cube([_sd_width,_sd_depth+_rpi_p+_t_wall+_sd_inset+14, _h_rpi_offset+_sd_depth-1.5]); }
            
