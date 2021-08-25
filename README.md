
# Doom (Doom Not Doom)

### Requiremnts:
- [x] You can look up and down.
- [x] The areas you go through don’t have a fixed shape.
- [x] The floor and ceiling have adjustable heights.
- [x] The floor and ceiling may not be horizontal but inclined planes.
- [x] The floors and ceilings have textures.
- [x] There can be a sky instead of a ceiling.
- [x] Walls can be partially transparent, unveiling the room behind.
- [x] Decorative elements can be placed on the walls over the main texture (wall sprites).
- [x] Objects or characters can be placed in the world as sprites that always face the player.	
- [x] Objects or characters can be placed in the world as multiple sprites displayed according to the orientation 	between the object and the player.
- [ ] Each room or area has a light control tool, affecting both the walls and the objects within.
- [x] Text messages can be displayed during the game over the rest of the graphics.
- [x] There must be a HUD (life, currency, ammunition, carried artifacts...)
- [x] The view follows the mouse smoothly, making it possible to spin around (a whole 360) and to look up and down.
- [x] Strafing is possible.
- [x] Interactions with walls and steps of a reasonable height should be managed properly.
- [x] The player can run, jump, fall, bend down and get up.
- [x] The player can fly or swim (same difference...).
- [x] The objects present may or may not block the passage, in proportion to their visual representation.
- [x] The items around can be picked up - or not, and supply an inventory.
- [x] The player can interact with the elements of the rooms (pressing a button).
- [x] Actions or series of actions can result from interactions.
- [ ] Actions can alter all the elements of the game, all the shapes, all the properties (the shape of a room, theheight of a ceiling, the texture of a wall or an object, the location of the specific texture on a door thatindicates its "handle", etc).
- [x] Game must contain animations, various devices like dooropening systems, keys and ways to use them, elevators and secret passages.
- [x] Specific characters and / or objects can have their own actions, reactions and interactions in the universe.
- [x] Projectiles can be fired and interact with the background, objects, characters, even the player itself.
- [ ] There is a story with a mission, a goal to reach.
- [ ] There is a beginning and an end on each level.
- [x] There are sound effects.
- [x] There’s music.
- [x] A level editor.
- [ ] Just like in the original games, you must pack in a single file all the elements you’re going to need.

### Constraints

> C is mandatory.
> Follow the Norm (A royal pain in the ass)
> Drawing only by filling a one-dimension array of pixels manually.
> Computing everything on the CPU.
> No 3rd party libraries except for SDL, pthread, malloc.
> No crash or memory leaks.
> Ofcourse that the frame rate is not garbage.

## Features
- Skybox 360 view.
- Bullet holes left on wall.
- Store where weapond and upgrades can be bought.
- Rifts (Portals) that spawn entities.
- 2 Game modes, Story and Endless.
- Multythreading.
- Map events.
- Clickable or shootable buttons and position triggers.
- User settings, Window size, FOV, Difficulty etc.
- BXPM, custom image format.
- Wall collision and wall slide.
- AI Dodge/Danger.
- Many more...

By: Niklas Neronin & Jony Salmi