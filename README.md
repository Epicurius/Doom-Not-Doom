<img src="./Readme_assets/DoomNotDoom.png" alt="Engine_Flow" width="900"/></p>
A first person 3D game made in C with SDL2 and no hardware acceleration or 3rd party 3D Library.<br>
Improved on the Build engine from Duke Nukem 3D.<br>
Only works on OSX.

* [Installation](#installation)
* [Controls](#controls)
* [Map](#map-file)
* [Engine](#engine)
* [BXPM](#bxpm-image-format)
* [Features](#features)
---

### Installation
```sh
git clone --recurse-submodules https://github.com/Epicurius/doom_nukem.git DnD
cd DnD && make
./game/doom ./game/resources/MAPS/game.story
# OR
./wolf3d
```
---
### Controls
```
	WASD/Arrow Keys 	-	Move
	Space			-	Jump
	Mouse			-	Look around
	Shift			-	Sprint
	Control			-	Crouch
	Left click		-	Shoot
	E			-	Use
	Tab			-	Show map
	Scroll Wheel		-	Zoom map
	ESC/Q			-	Quit
	P			-	Pause
	`			-	Unstuck player
```
---
##### Map

The map is built using vertices, floors, ceiling, walls and sectors.<br>
Vertices are x and y decimals that describe a position.<br>
Walls are a line segment connected to 2 vertices.<br>
Sectors are a concave shape, consisting of 3 or more clockwise connected walls.<br>
Each sector has its own floor and ceiling.<br>

<img src="./Readme_assets/map.jpg" alt="Engine_Flow" width="700"/></p>

---
##	Engine

Short introduction on how the engine works.
* [Engine Flow](#engine-flow)
* [Map](#map)
* [Map Drawing](#map-drawing)
* [Skybox](#skybox)
* [AI](#entitites)
* [Shooting](#shooting)
* [Collision Detection](#collision-detection)

##### Engine Flow
When designing and building the game engine my priority was performance (FPS) over features.<br>
In my mind a game with many features but low performance is worse that the opposite,<br>
so with the constraints of no hardware acceleration (GPU) and no 3rd party 3D Library (OpenGl)<br>
multithreading (pthreads) was my best option.<br>

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
```
</p>



##### Map Drawing
To maximize on performance the map surfaces are calculated first so that the screen can be split into width amount of vertical pieces.<br>
Each vertical piece is self sufficient from start to end, which enabled them to render at the same time while the main thread can do tasks that don't require the screen, e.g. collision detection, precompute AI.<br>
And when all the all map surfaces have been rendered no more calculations are needed for the rest of the rendering, e.g. Entity rendering.

###### Map rendering on one thread, first monochrome then with texture.</center>
<img src="./Readme_assets/map_render.gif" alt="Engine_Flow" width="900"/></n>

When rendering/drawing the map surfaces .e.g walls, floor and ceiling, a recursive approach is used.<br>
each vertical segment starts with player sector wall, if the wall has a neighbor it calls itself with a reduced screen segment (black part in the above gif) and start from the beginning.
When a solid wall is hit the engine draws the wall and starts to backtrack and drawing any see-through walls.<br>

##### Skybox

Skybox rendering is similar to normal map rendering except for the "walls" of the skybox are not static.<br>
The skybox box is a 10x10x10 box where the player is always in the middle, the box also moves with the player creating the illusion that there is a vast distance.

##### AI

Entities have 4 states IDLE, MOVE, ATTACK and DEATH, static entities use only IDLE.<br>
Alive/non static entities have a detection radius and a view cone, if their line of sight collides<br>
with the player they will get the state MOVE and try to get into their attack range.<br>
When the entity is inside their attack range they will get the state ATTACK and start attacking the player.<br>
If the entities health drops below 1 the state will be set to DEATH and when all the death frames have been played the entity is removed.
During IDLE state, non static entities have a random chance of moving into a radom direction, and if an entity is attacking or pursuing a player while the players crosshair is on the entity the entity will try to move and dodge, to avoid getting shot.<br>

<img src="./Readme_assets/frame.jpg" alt="Engine_Flow" width="800"/><br>
Each entity frames are divided into the entity states and into FRAME and ANGLE.<br>
Take for example the above image, it har move animation of 8 frames with each having 3 angles.<br>
When moving every 120 degrees (360 / 3) around the entity will show a different frame angle.<br>
If an entity has 1 angle the entity will always face the player.<br>
So a entity frame coordinates can be derived from ```doom->eframes[ENTITY].pos[STATE][FRAME_NB][ANGLE]```;

Entity presets can be found from inc/resources.h

##### Shooting

Shooting is very simple, when each entity is drawn if an entity pixel is the middle of the screen,<br>
and the player has pressed left click then that entity has been shot.<br>
No bullet collision detection algorithm is required.<br>

##### Collision Detection

Collision detection has to keep track of velocity, position and sector, this makes collision detection a bit tricky.<br>
It consists of 3 main parts:<br>

```
Vertical_collision():
	Check for z axis collision, e.g. jump, fall.
	If possible apply gravity.
	Change z velocity appropriately.
```
```
Horizontal_collision():
	Check for x/y axis collision and sector changes.
	Set each visited sector to TRUE, to keep track.
	Check all walls in sector.
	If intersect portal, check for step height and start checking all neighboring sectors walls.
	If collision detected pass to slide_collision().
	Else keep original x/y velocity.
```
```
Slide_collision():
	Adjusts velocity so that an entity slides parallel with given wall.
	Checks x/y collision, if collision detected sets x and y velocity to 0.
	Else change x/y velocity appropriately.
```
When all collision detection has been checked, add velocity to entity position.
If entity position is not in original sector, find correct sector from visited sectors list.

---

## BXPM Image Format

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
### Map File



We uses a custom map file, that is divided into 9 types.
Each type consists of x instances of the same information.
For example:
|type:vertex	|x|	y|
|:-:|:-:|:-:|
|0				|0|	0|
|1				|10|0|
|2				|10|10|
|3				|0|10|

In this example we have 4 vertices with and index, x and y coordinates.
Each type always start with index and then type specific information in order.

 



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

## Features

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
