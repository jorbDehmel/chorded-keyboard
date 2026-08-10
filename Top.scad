// STL output file loading just the top from Body.scad

include <Complete.scad>

translate([0, 0, thickness])
  rotate([180, 0, 0])
  top_piece();
