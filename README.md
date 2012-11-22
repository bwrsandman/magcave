#Magcave
COMP472 Fall 2012
- Sandy Carter 1121057
- Zoe Briscoe  9611754

##Program Function


Minimax code is included in minimax.cpp and minimax.h

The gamebord class interfaces with ncurses to draw on the stdscreen. 
It is also in charge of drawing the board on which the game is played.

The gameinfo class is used to define the rules of the game.
It determines when a player has won or if a checkmate exists.

The program has been tested under i686 GNU/Linux with the 3.6.6 Linux 
kernel as well as under Windows using cygwin.

##Unpacking and Compiling instructions

Under Linux or cygwin:
(You must have the ncurses dev libraries installed)
   - untar:
    - $ tar xfvj magcave-2.tar.bz2
   - compile using make:
     - $ make
     - or compile manually:
       - $ g++ magcave.cpp minimax.cpp gameboard.cpp gameinfo.cpp -I/usr/include/ncurses -lncurses -o magcave

##Running instructions

Under Linux or cygwin:
   - $ ./magcave

##Keyboard Input
   - q: quits the game
   - k: kills the window
   - w/up key: move up
   - s/down key: move down
   - a/left key: move left
   - d/right key: move right
   - return key: select position and end turn
