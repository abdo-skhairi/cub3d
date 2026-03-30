<div align="center">


<div align="center">
<pre>
 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝
</pre>
</div>




**A 3D maze exploration game inspired by Wolfenstein 3D**

![C](image)
![MiniLibX](https://img.shields.io/badge/graphics-MiniLibX-orange?style=flat-square)
![42 Project](https://img.shields.io/badge/school-42-black?style=flat-square)

</div>

---

## What Is This?

Cub3D is a 3D maze renderer built entirely in C using the **raycasting** technique — the same algorithm that powered *Wolfenstein 3D* in 1992. A 2D grid map is transformed in real time into a first-person 3D perspective with textured walls, floor/ceiling colors, and smooth player movement.

No GPU. No 3D engine. Just math, rays, and pixels.

---

## Demo

> *(Add a gameplay gif or screenshot here)*

---

## Features

- Real-time raycasting renderer
- Textured walls (North / South / East / West)
- Configurable floor and ceiling colors
- Smooth player movement and camera rotation
- Collision detection with wall sliding
- Custom `.cub` map format parser

---

## Quick Start

```bash
# Clone and build
git clone <your-repo-url>
cd cub3d
make

# Run with a map
./cub3D maps/map.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W / S` | Move forward / backward |
| `A / D` | Strafe left / right |
| `← / →` | Rotate camera |
| `ESC` | Exit |

---

## Map Format

Maps are plain-text `.cub` files with this structure:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

        1111111111
        1000000001
        1011100001
        1000110001
  1111111001100001111
  1000000000000000001
  1000000000000000001
  1111111111111111111
```

| Symbol | Meaning |
|--------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `N S E W` | Player start position + orientation |
| `NO SO WE EA` | Texture paths for each wall face |
| `F` | Floor color (R,G,B) |
| `C` | Ceiling color (R,G,B) |

---

## How Raycasting Works

For every vertical column on screen, one ray is cast from the player's position into the 2D map. When the ray hits a wall, we calculate how tall that wall slice should appear — closer walls are taller, distant walls are shorter. Repeat across all 800+ columns and the scene emerges.

### The Pipeline

```
For each screen column x:
│
├─ 1. Compute ray direction
│     Combine player direction + camera plane offset
│
├─ 2. Set up DDA variables
│     map cell, step direction, side distances
│
├─ 3. Run DDA (Digital Differential Analysis)
│     Advance ray grid-by-grid until wall hit
│
├─ 4. Calculate perpendicular distance
│     Avoids fish-eye by using projected distance, not Euclidean
│
├─ 5. Determine wall height
│     line_height = SCREEN_HEIGHT / perp_dist
│
├─ 6. Select texture
│     Which face was hit? (N/S/E/W)
│     Where on the wall? → texture X coordinate
│
└─ 7. Draw the column
      Ceiling → Textured wall slice → Floor
```

### Key Concepts

**DDA Algorithm**
Rather than checking every point along a ray, DDA jumps directly to the next grid boundary — making it O(grid crossings) instead of O(ray length). This is what makes real-time raycasting possible.

**Perpendicular Distance**
Naively using the Euclidean distance to the wall hit point causes a fish-eye distortion — walls appear curved. The fix is to project the hit point back onto the player's camera plane and use *that* distance instead.

```c
// Side 0 = vertical wall hit, Side 1 = horizontal wall hit
if (side == 0)
    perp_dist = side_dist_x - delta_dist_x;
else
    perp_dist = side_dist_y - delta_dist_y;
```

**Texture Mapping**
After a wall hit:
1. Calculate the exact fractional position on the wall face
2. Multiply by texture width → `tex_x`
3. For each pixel in the vertical slice, interpolate → `tex_y`
4. Sample the texture and draw

**Depth Shading**
East/West facing walls are drawn slightly darker than North/South walls. This simple trick adds a strong sense of depth without any additional computation.

---

## Project Structure

```
cub3d/
├── cub3d.c              # Entry point
├── cub3d.h              # All structs and prototypes
│
├── src/
│   ├── draw.c           # Ray initialization, DDA, scene rendering
│   ├── pixel.c          # Pixel and texture drawing utilities
│   ├── moves.c          # Player movement and rotation
│   ├── moves_utils.c    # Collision detection (8-point circle sampling)
│   ├── init_game.c      # Window and image initialization
│   ├── init_textures.c  # Texture loading
│   ├── init_colors.c    # Floor/ceiling color setup
│   └── free.c           # Memory cleanup
│
└── maps/
    └── *.cub            # Map files
```

---

## Technical Notes

### Collision Detection
Player collision uses 8 evenly-spaced sample points arranged in a circle around the player's position. Each point is checked against the map before movement is applied — this gives smooth wall sliding rather than stopping dead on contact.

### Rotation
Camera rotation uses a standard 2D rotation matrix:

```
new_dir_x = dir_x * cos(angle) - dir_y * sin(angle)
new_dir_y = dir_x * sin(angle) + dir_y * cos(angle)
```

The camera plane vector is rotated by the same amount to maintain the correct field of view.

### Memory Management
All heap-allocated resources (textures, images, map array) are tracked in the main game struct and freed in `free.c` on exit or error — including MiniLibX window and display resources.

---

## Roadmap

- [ ] Minimap overlay
- [ ] Animated sprites / enemies
- [ ] Floor and ceiling textures
- [ ] Mouse-look support
- [ ] Door mechanics

---

## Authors

| Contributor | Focus |
|-------------|-------|
| *Your name* | Raycasting, rendering, texturing, movement |
| *Teammate* | Map parsing, validation |

---

> *Parsing documentation to be completed by teammate.*
