# Cub3D

A raycasting game engine inspired by Wolfenstein 3D, built using the MinilibX graphics library.
## Usage
```bash
make
./cub3D maps/map.cub
```

## Map Format
```

NO		./textures/wall2.xpm

SO		./textures/wall1.xpm

EA		./textures/wall3.xpm

WE		./textures/wall4.xpm

F	53, 94, 59

C	0, 255, 0


11111111111111111111111111111
10000000001100000000000011111
10110000011100000000000011111
10010000000000000000000011111
11111111101100000111000001111
10000000001100000111011000011
11110111111111011100000000001
11110111111111011101010000001
11000000110101011100000000001
10000000000000001100000010001
10000000000000001101010001001
11000001110101011111011110N01
11110111111101011101111010001
11111111111111111111111111111
```

## Features
- Raycasting engine
- Textured walls
- Player movement (WASD)
- Camera rotation (arrow keys)
- Collision detection
- Floor/ceiling colors
- Custom map parsing

## Technical Implementation
- MinilibX for graphics rendering
- DDA algorithm for raycasting
- Texture mapping
- FPS optimization
- Memory management
- Error handling

## Project Structure
```
cub3D/
├── cub/
│   ├── Gnl/
│   ├── libc/
│   ├── textures/
│   ├── parser.c
│   ├── parser2.c
│   ├── parser3.c
│   ├── parser4.c
│   ├── raycasting.c
│   ├── render.c
│   ├── utils1.c
│   └── cub3d.h
```

## Controls
- `W/S`: Move forward/backward
- `A/D`: Strafe left/right
- `←/→`: Rotate camera
- `ESC`: Exit game

## Error Handling
- Invalid map configuration
- Missing textures
- Memory allocation
- File reading errors
- Map validation

## Dependencies
- MinilibX
- GCC
- Make
- X11 development files
