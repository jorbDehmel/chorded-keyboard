//

include <Vars.scad>

$fn = $preview ? 32 : 64;

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

*rotate([rotation, 0, 0])
  translate([
    0,
    -4 * switch_plate_w + 9 + thickness,
    2 * switch_plate_w + thickness
  ])
  base();
