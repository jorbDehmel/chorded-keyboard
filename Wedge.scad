//

include <Vars.scad>

wedge_depth = 4 * switch_plate_w + 6 * thickness;

// WIP
module wedge() {
  difference() {
    // Main base
    cube([
      4 * switch_plate_w + 4 * thickness, // Exact
      4 * switch_plate_w + 4 * thickness, // Eyeballing it
      50
    ]);

    // Cutout for entire thing (eyeballing it)
    translate([-thickness, 6.733 * thickness, 1.397 * thickness])
      rotate([wedge_rotation, 0, 0])
      cube([wedge_depth, 73.56, 50]);

    translate([-thickness, 6.733 * thickness, 1.397 * thickness])
      rotate([wedge_rotation, 0, 0])
      translate([0, 73.56, 0])
      rotate([rotation])
      cube([wedge_depth, 15, 20]);

    translate([-thickness, 6.733 * thickness, 1.397 * thickness])
      rotate([wedge_rotation + rotation, 0, 0])
      cube([wedge_depth, 30, 40]);
  }

  // Pinky hole support
  rotate([wedge_rotation + rotation, 0, 0])
    translate([0, -3 * thickness, -switch_plate_w + 3.3])
    cube([wedge_depth, 20 + 7.45 * thickness, 20]);
}

*wedge();
