// The casing for a chorded keyboard
// See: https://blog.arduino.cc/2023/06/05/build-your-own-wireless-hand-wired-keyboards-a-guide/

is_main = false;
include <Base.scad>
include <Top.scad>
include <Wedge.scad>

color("red")
  wedge();

translate([
  2 * thickness, // Exact
  2.1 * thickness, // Eyeballing it
  9
  ])
  rotate([wedge_rotation, 0, 0])
  rotate([rotation, 0, 0])
  union() {
    if (show_spacing) {
      color("blue")
        translate([0, 4 * switch_plate_w, -2 * switch_plate_w])
        rotate([90, 0, 0])
        arduino();
    }

    color("orange") base();
    top_piece();
  }
