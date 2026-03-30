# Cub3D - Raycasting Engine

<p align="center">
  <img src="image" width="800"/>
</p>

<h1 align="center">Cub3D - Raycasting Engine</h1>

<p align="center">
  A 3D maze exploration game inspired by Wolfenstein 3D
</p>

A 3D maze exploration game using raycasting techniques, inspired by Wolfenstein 3D.

---

## Overview

Cub3D renders a 3D environment from a 2D map using raycasting. The player can navigate through the maze with realistic wall textures and collision detection.

---

## Key Files

| File | Purpose |
|------|---------|
| `draw.c` | Ray initialization, DDA algorithm, scene rendering |
| `pixel.c` | Pixel and texture drawing |
| `moves.c` | Player movement and rotation |
| `moves_utils.c` | Collision detection |
| `init_*.c` | Game, texture, and color initialization |
| `free.c` | Memory cleanup |

---

## How Raycasting Works

### The Basic Concept

For each vertical column on the screen, we cast one ray from the player's position. The ray travels until it hits a wall, then we calculate how tall that wall should appear on screen.

### Step-by-Step Process

**1. Loop Through Screen Columns**
   - For each column x (from 0 to screen width)

**2. Calculate Ray Direction**
   - Combine player direction with camera plane
   - Each column gets a slightly different angle

**3. Initialize DDA Variables**
   - `map_x`, `map_y`: current map square
   - `delta_dist`: distance to move to next grid line
   - `step`: direction of movement (+1 or -1)
   - `side_dist`: distance to next vertical/horizontal line

**4. Perform DDA (Digital Differential Analysis)**
   - Walk along the ray step by step
   - Compare horizontal vs vertical distances
   - Move to the closest next grid line
   - Stop when hitting a wall (map value = 1)

**5. Calculate Wall Distance**
   - Use perpendicular distance to avoid fish-eye effect
   - Formula: `perp_dist = (side_dist - delta_dist)`

**6. Compute Wall Height**
   - `line_height = screen_height / perp_dist`
   - Calculate `draw_start` and `draw_end` positions
   - Clamp values to screen boundaries

**7. Select Texture**
   - Determine which wall face was hit (N/S/E/W)
   - Calculate exact hit position on wall
   - Map to texture coordinates

**8. Draw Vertical Line**
   - Draw ceiling (top to draw_start)
   - Draw textured wall (draw_start to draw_end)
   - Draw floor (draw_end to bottom)
   - Apply shading for Y-side walls

**9. Repeat**
   - Continue for next column until entire screen is filled

**10. Display Image**
   - Put the final rendered image to window

---

## Texturing System

### Overview

Texturing gives life to walls. Instead of flat colors, each wall is mapped with an image (texture) to create realistic 3D visuals.

### How It Works

After a ray hits a wall:
1. Determine **wall orientation** (North, South, East, West)
2. Calculate **exact hit position** on the wall
3. Map that position to a pixel inside the correct texture
4. Render the textured slice for that screen column
5. Apply shading for depth (darken East/West walls slightly)

### Step-by-Step

**1. Detect Wall Orientation**
- Decide which texture to use based on the wall side hit

**2. Calculate Wall Hit Position**
- Vertical wall → `hit_x = player_y + perp_dist * ray_dir_y`
- Horizontal wall → `hit_x = player_x + perp_dist * ray_dir_x`
- Keep only the decimal part → maps to texture column

**3. Map to Texture Coordinates**
- `tex_x = int(hit_x * texture_width)`
- For each pixel in the vertical slice:
  - `tex_y = int((current_pixel - draw_start) / line_height * texture_height)`

**4. Draw Textured Slice**
- Copy pixel color from texture to screen
- Repeat for every column

**5. Apply Shading**
- Darken walls depending on side (East/West) for depth

---

## Rendering Flow
