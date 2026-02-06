# Cub3D - Raycasting Engine

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

## Rendering Flow

```
Game Loop
    ↓
Handle Input (movement/rotation)
    ↓
Update Player Position
    ↓
Create New Image Buffer
    ↓
For Each Screen Column:
    ├─ Initialize Ray
    ├─ Run DDA Algorithm
    ├─ Find Wall Hit
    ├─ Calculate Distance
    ├─ Compute Wall Height
    ├─ Get Texture Coordinates
    └─ Draw Vertical Slice
    ↓
Display Image
    ↓
Repeat
```

---

## Movement System

### Controls
- **W/S**: Move forward/backward
- **A/D**: Strafe left/right
- **←/→**: Rotate camera
- **ESC**: Exit game

### Features
- Smooth movement using direction vectors
- Rotation using 2D rotation matrix
- Collision detection with wall sliding
- 8-point circle sampling for accurate collision

---

## Technical Details

### Fish-Eye Correction
Using perpendicular distance instead of Euclidean distance prevents the fish-eye distortion effect.

### Wall Shading
Y-side walls (East/West) are slightly darkened to provide depth perception.

### Texture Mapping
Each wall hit calculates:
- Which texture to use (N/S/E/W)
- X-coordinate on the texture
- Y-coordinates for each pixel from top to bottom

---

## Compilation

```bash
make
./cub3D maps/map.cub
```

---

## Map Format

Maps are defined in `.cub` files containing:
- Texture paths (NO, SO, WE, EA)
- Floor and ceiling colors (F, C)
- 2D map grid (0=empty, 1=wall, N/S/E/W=player start)

---

## Key Concepts for Evaluation

1. **One Ray Per Column**: Each screen column = one ray cast
2. **DDA Algorithm**: Efficient grid traversal to find walls
3. **Perpendicular Distance**: Prevents fish-eye distortion
4. **Texture Mapping**: Correct texture coordinates for realistic walls
5. **Collision Detection**: Prevents walking through walls
6. **Performance**: Real-time rendering at playable frame rates

---

## Project Structure

```
cub3d/
├── src/
│   ├── draw.c          # Core raycasting
│   ├── pixel.c         # Rendering helpers
│   ├── moves.c         # Player movement
│   ├── moves_utils.c   # Collision
│   └── init_*.c        # Initialization
├── cub3d.c
│── cub3d.h         # Header file
└── maps/
    └── *.cub           # Map files
```

---


**Note**: This README focuses on the raycasting and rendering pipeline. Parsing documentation to be completed by teammate.