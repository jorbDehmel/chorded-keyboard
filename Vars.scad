
$fn = $preview ? 32 : 64;

switch_plate_w = 19.05;
switch_hole_w = 14;
thickness = 1.5;
spacing = 9;
rotation = 24;

usb_c_female_width = 9;
usb_c_female_height = 3;
usb_c_female_depth = 2 * thickness;

wedge_rotation = 30;

show_spacing = true;

module edge_leveller(h, r) {
  difference() {
    cube([h, 2 * r, 2 * r]);
    translate([-1, 0, 0])
      rotate([0, 90, 0])
      cylinder(h = 2 * h, r = r);
  }
}
