// STL output file loading just the base from Body.scad

include <Complete.scad>

rotate([rotation, 0, 0])
  translate([
    0,
    -4 * switch_plate_w + 9 + thickness,
    2 * switch_plate_w + thickness
  ])
  base();
