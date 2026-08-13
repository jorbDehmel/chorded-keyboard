// The casing for a chorded keyboard
// See: https://blog.arduino.cc/2023/06/05/build-your-own-wireless-hand-wired-keyboards-a-guide/

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

show_spacing = false;

// Model of arduino
module arduino() {
  arduino_width = 18;
  arduino_height = usb_c_female_height + 4;
  arduino_depth = 36;

  // Board
  cube([arduino_depth, arduino_width, arduino_height]);

  // USB-C female port 1 mm above base of board. I'll
  // put 2 for wiggle room
  translate([-usb_c_female_depth,
    (arduino_width - usb_c_female_width) / 2, 2])
    cube([usb_c_female_depth, usb_c_female_width,
      usb_c_female_height]);
}

// Tiling these next to each other is standard. See
// https://deskthority.net/viewtopic.php?t=20144
module keycap_mount() {
  delta = switch_plate_w - switch_hole_w;
  difference() {
    translate([-switch_plate_w / 2, -switch_plate_w / 2, 0])
      cube([switch_plate_w, switch_plate_w, thickness]);
    translate([
        -switch_plate_w / 2 + delta / 2,
        -switch_plate_w / 2 + delta / 2, -1])
      cube([switch_hole_w, switch_hole_w, thickness + 2]);
  }
  if (show_spacing) {
    color("blue")
      translate([-switch_plate_w / 2,
        -switch_plate_w / 2, -spacing])
      cube([switch_plate_w, switch_plate_w, spacing]);
  }
}

// The mounting for the two buttons corresponding to one
// finger
module finger_section_mount() {
  // Upper
  translate([switch_plate_w / 2, 0, 0])
    keycap_mount();
  // Lower
  translate([-switch_plate_w / 2, 0, 0])
    keycap_mount();
}

module edge_leveller(h, r) {
  difference() {
    cube([h, 2 * r, 2 * r]);
    translate([-1, 0, 0])
      rotate([0, 90, 0])
      cylinder(h = 2 * h, r = r);
  }
}

// The mounts for all the switches
module top_piece() {
  difference() {
    union () {
      // Pinky
      translate([
          2 * switch_plate_w,
          switch_plate_w / 2,
          0])
        finger_section_mount();

      // Main fingers
      for (d=[1, 2, 3]) {
        translate([
            switch_plate_w,
            d * switch_plate_w + switch_plate_w / 2,
            0])
          finger_section_mount();
      }

      // Thumb
      translate([
          3 * switch_plate_w,
          4 * switch_plate_w,
          -switch_plate_w / 2 - switch_plate_w])
        rotate([-90, 0, 0])
        finger_section_mount();

      // Between thumb and main mount
      translate([0, 4 * switch_plate_w, -2 * switch_plate_w])
        cube([
          2 * switch_plate_w,
          thickness,
          2 * switch_plate_w + thickness
        ]);

      // Going up from thumb
      translate([
        2 * switch_plate_w,
        4 * switch_plate_w,
        -switch_plate_w
      ])
        cube([
          switch_plate_w,
          thickness,
          switch_plate_w + thickness
        ]);

      // Going from pinky to the previous part
      translate([2 * switch_plate_w, switch_plate_w, 0])
        cube([switch_plate_w, 3 * switch_plate_w, thickness]);

      // Bottom lining under thumb
      translate([
        0,
        4 * switch_plate_w,
        -2 * switch_plate_w - thickness
      ])
        cube([4 * switch_plate_w, thickness, thickness]);

      // Bottom lining under pinky
      translate([switch_plate_w, -thickness, 0])
        cube([2 * switch_plate_w, thickness, thickness]);

      // Front panel
      translate([
        -thickness,
        4 * switch_plate_w,
        -2 * switch_plate_w - thickness
      ])
        cube([thickness, thickness, thickness]);

      translate([
        -thickness,
        switch_plate_w,
        0
      ])
        cube([thickness, 3 * switch_plate_w, thickness]);

      // This is the part with the USB-C hole
      difference() {
        translate([
          -thickness,
          4 * switch_plate_w - 9 - thickness,
          -2 * switch_plate_w
        ])
          cube([
            thickness,
            9 + 2 * thickness,
            2 * switch_plate_w + thickness
          ]);

        // USB-C hole
        translate([
          -2 * thickness,
          4 * switch_plate_w - thickness - 2,
          -switch_plate_w - usb_c_female_width
          + usb_c_female_height / 2
        ])
          rotate([0, 90, 0])
          union() {
            cylinder(
              h=2 * usb_c_female_depth,
              r=usb_c_female_height / 2
            );

            translate([
              usb_c_female_width - usb_c_female_height,
              0,
              0
            ])
              cylinder(
                h=2 * usb_c_female_depth,
                r=usb_c_female_height / 2
              );

            translate([0, -usb_c_female_height / 2, 0])
              cube([
                usb_c_female_width - usb_c_female_height,
                usb_c_female_height,
                2 * usb_c_female_depth
              ]);
          };
      }
    }
    translate([-2 * thickness, 4 * switch_plate_w, 0])
      rotate([0, 0, 0])
      edge_leveller(100, thickness);
  }
}

module base() {
  difference() {
    union() {
      // Bottom edge of pinky
      translate([
        switch_plate_w - thickness,
        -thickness,
        -spacing - thickness
      ])
        cube([
          2 * switch_plate_w + 2 * thickness,
          thickness,
          spacing + thickness
        ]);

      // Bottom edge of thumb
      translate([
        -thickness,
        4 * switch_plate_w - spacing - thickness,
        -2 * switch_plate_w - thickness
      ])
        cube([
          4 * switch_plate_w + 2 * thickness,
          spacing + thickness,
          thickness
        ]);

      // Baseplate bottom
      translate([
        -thickness,
        4 * switch_plate_w - 9 - thickness,
        -2 * switch_plate_w - thickness
      ])
        rotate([90 - rotation, 0, 0])
        cube([
          4 * switch_plate_w + 2 * thickness,
          thickness,
          4 * switch_plate_w - 2.641
        ]);

      // Walls around pinky
      translate([
        -thickness,
        -thickness,
        -switch_plate_w
      ])
        cube([
          switch_plate_w + thickness,
          switch_plate_w + thickness,
          switch_plate_w + thickness
        ]);

      // Back wall
      translate([
        3 * switch_plate_w,
        -thickness,
        -2 * switch_plate_w
      ])
        cube([
          thickness,
          3 * switch_plate_w + thickness,
          2 * switch_plate_w + thickness
        ]);

      // Front wall
      translate([
        -thickness,
        switch_plate_w,
        -2 * switch_plate_w
      ])
        cube([
          thickness,
          3 * switch_plate_w - 9 - thickness,
          2 * switch_plate_w
        ]);

      // Inner thumb wall
      translate([
        3 * switch_plate_w,
        -thickness,
        -2 * switch_plate_w
      ])
        cube([
          switch_plate_w + thickness,
          3 * switch_plate_w + thickness,
          switch_plate_w
        ]);

      // Back thumb wall
      translate([
        4 * switch_plate_w,
        switch_plate_w,
        -2 * switch_plate_w - thickness
      ])
        cube([
          thickness,
          3 * switch_plate_w + thickness,
          switch_plate_w + 2 * thickness
        ]);

      // Thumb cover
      translate([
        3 * switch_plate_w,
        3 * switch_plate_w,
        -switch_plate_w
      ])
        cube([
          thickness,
          switch_plate_w + thickness,
          switch_plate_w + thickness
        ]);

      translate([
        3 * switch_plate_w + thickness,
        3 * switch_plate_w - thickness,
        -switch_plate_w
      ])
        cube([
          switch_plate_w - thickness,
          switch_plate_w + 2 * thickness,
          thickness
        ]);
    }

    // Hole above pinky
    translate([
      -switch_plate_w - thickness,
      -switch_plate_w - thickness,
      -2 * switch_plate_w
    ])
      cube([
        2 * switch_plate_w,
        2 * switch_plate_w,
        3 * switch_plate_w
      ]);

    // Hole at base of thumb
    translate([
      3 * switch_plate_w + thickness,
      -2 * thickness,
      -3 * switch_plate_w
    ])
      cube([
        switch_plate_w + 2 * thickness,
        3 * switch_plate_w + thickness,
        5 * switch_plate_w
      ]);

    // Trim any junk below the base
    translate([
      -2 * thickness,
      4 * switch_plate_w - 9 - thickness,
      -2 * switch_plate_w - thickness
    ])
      rotate([90 - rotation, 0, 0])
      translate([0, -20 * thickness, 0])
      cube([
        4 * switch_plate_w + 20 * thickness,
        20 * thickness,
        4 * switch_plate_w + 20 * thickness
      ]);

    // Round off the peak
    translate([-2 * thickness, 4 * switch_plate_w, 0])
      rotate([0, 0, 0])
      edge_leveller(100, thickness);
  }
}

// WIP
module wedge() {
  linear_extrude(thickness)
    projection(cut = false)
    translate([thickness, 10, 9])
      rotate([wedge_rotation + rotation, 0, 0])
      union() {
        base();
        top_piece();
      };
}

if (show_spacing) {
  color("blue")
    translate([0, 4 * switch_plate_w, -2 * switch_plate_w])
    rotate([90, 0, 0])
    arduino();
}

// wedge();
// translate([thickness, 10, 9])
// rotate([wedge_rotation, 0, 0])
// rotate([rotation, 0, 0])
// union() {
//   color("orange") base();
//   top_piece();
// }
