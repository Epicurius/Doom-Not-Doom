<img src="./Readme_assets/DoomNotDoom.png" alt="Engine_Flow" width="900"/></p>
A first person 3D game made in C with SDL2 and no hardware acceleration or 3rd party 3D Library.
For OSX.

* [Installation](#instalation)
* [Controls](#controls)
* [Map](#map)
* [Engine](#engine)
* [BXPM](#bxpm)
* [Features](#features)
---

#### Installation
```sh
git clone https://github.com/Epicurius/Doom-Not-Doom.git DnD && cd DnD
make
./doom ./resources/MAPS/game.story
```
---
#### Controls
```
	WASD/Arrow Keys -	Move
	Space			-	Jump
	Mouse			-	Look around
	Shift			-	Sprint
	Control			-	Crouch
	Left click		-	Shoot
	E				-	Use
	Tab				-	Show map
	Scroll Wheel	-	Zoom map
	ESC/Q			-	Quit
	P				-	Pause
	`				-	Unstuck player
```

---
###	Engine

When designing and building the game engine my priority was performance (FPS) over features.</n>
In my mind a game with many features but low performance is worse that the opposite,</n>
so with the constraints of no hardware acceleration (GPU) and no 3rd party 3D Library (OpenGl)</n>
multithreading (pthreads) was my best option.

<img src="./Readme_assets/DnD_Engine_Flow.jpg" alt="Engine_Flow" width="900"/></p>
```ruby
1  - Game is launched.
2  - Checking all passed arguments, if not given sets default values.
3  - Parses the given map file.
4  - Validates the map values and corrects any it can, else program terminates.
5  - Inits everything needed for the game to run.
6  - Creates and executes texture parsing threads, wait for all to be ready.
7  - While user has not quit or died:
	1  - Handles game mode specific event, e.g. spawning enemies, game rounds.
	2  - Handles map events, e.g. moving doors, light switches.
	3  - Precompute walls, values that can be calculated before drawing.
	4  - Precompute skybox, values that can be calculated before drawing.
	5  - Creates map drawing threads.
	6  - Precompute weapons, does it have ammo etc.
	7  - Precompute Entities, e.g. movement, aggression.
	8  - Precompute projectile, movement and collision.
	9  - Handel player collision detection.
	10 - Reads all user inputs.
	11 - Wait for all map drawing thread to be ready.
	12 - Draw all projectiles
	13 - Create and execute entity drawing threads.
	14 - Create and execute weapon drawing threads.
	15 - Draw HUD, e.g. ammo amount, health, armour.
	16 - If Tab is pressed draw map.
	17 - Calculate and update window FPS title and delta time.
	18 - Render to screen.
	19 - Check if user has paused or quit game.
8  - Free all allocated memory.
9  - Exit game.

To maximize on performance

```

---

### BXPM

The game required to have different light levels, for that to work each pixel of</n>
a given texture had to brightened or darkened to achieve the desired effect.</n>
Each frame all pixels that had a custom light level had to be calculated.</n>
To improve performance BXPM image format was created.</n>

BXPM is split into three parts:
```
Header:
	Size:		20 bytes.
	Type:		int32_t
	Content:	In order width, height, color amount, pixel amount, pixel format.

Colors:
	Size:		Color amount * 32 bytes
	Type:		int32_t
	Content:	Each unique color in the image.

Pixels:
	Size:		Pixel amount * 16 bytes
	Type:		uint32_t
	Content:	Id of the corresponding color.
```
Which we save into a struct:
```c
typedef struct s_bxpm
{
	int32_t				w;			//Image width
	int32_t				h;			//Image height
	int32_t				bpp;		//Color bits
	int32_t				clr_nb;		//Unique color amount
	int32_t				pix_nb;		//Pixel amount
	uint32_t			*clr;		//Unique colors
	unsigned short		*pix:		//Pixels ids
	uint32_t			**shade;	//Unique color shade
}						t_bxpm;		
```
This makes the BXPM file a lot smaller than a BMP, which also speeds up the parsing.</n>
But now instead of calculating pixel amount we need only calculate the color amount.</n>
We can do it at the start, and save each light level into uint32_t **shade,</n>
which will occupy clr_nb * 32 bytes per unique light level, so during runtime no</n>
light level calculations are done.</n>

If you want to take a look at how it works the library is at root libs/libbxpm.</n>
And in game/bmp_to_bxpm there is a bmp to bxpm converter. (./converter FILE.bmp)</n>

<img src="./Readme_assets/smile.png" alt="smile" width="200"/>

```c
//Visualization of the above (10x10)Image in BXPM format divided by commas, actual BXPM is compressed.
10,10,11,100,24,0xffffffff,0xff000000,0xff0032ff,0xff00ff00,0xff00fbff,0xffef00ff,0xffff6000,0xff00ffb5,0xffffd200, 0xffff0000,0xffffff00,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,10,0,0,0,0,0,0,9,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,8,0,0,0,5,0,0,0,0,6,0,0,0,0,0,1,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
```

---
### Map

DnD uses a custom map file, that is divided into segments (type) that the game interprets.</n>
Each line inside the segment is a separate instance of the info.</n>
```
Type:Map
NAME	-	Type of game mode.
SCALE	-	Scale of the map.
VERT	-	Amount of vertices.
WALL	-	Amount of walls.
SECT	-	Amount of sectors.
```
```
Type:Spawn
X		-	Player spawn x.
Y		-	Player spawn y
Z		-	Player spawn z.
YAW		-	Player horizontal view direction (DEGREES).
```
---

### Features

- 360 degree seamless skybox.
- Bullet holes left on walls after shooting.
- A Store where weapons, ammo, armour and player upgrades can be bought.
- Rifts (Portals) that spawn entities.
- 2 Game modes, Story and Endless.
- Multithreading.
- Map events, flickering light, moving doors etc.
- Clickable or shootable buttons and position triggers.
- User settings, Window size, FOV, Difficulty etc.
- Wall collision and wall slide.
- AI Dodge/Danger.
- Many more...
---