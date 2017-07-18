# shooter-game
minimal game built in c++ / SFML

# Building the game
## Installing Dependencies
* libsfml-dev

For debian or debian based systems do:
```sh
#apt install libsfml-dev
```
For other systems follow https://www.sfml-dev.org/

## Building
If you use codeblocks open `game/game.cbp` project and build.

If you want to do it mannually do :
```sh
  cd shooter-game/game/
```
```sh
g++ -c main.cpp
```
```sh
g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
```
run the game
```
./game
```

# Playing:
Space fires the ball. If you hit the moving target you'll get points.
