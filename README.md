# AdaShip
## 1. Challenge Outline

### a) Summary and review of the problem,

I was tasked with creating a version of Battleship for my university. They reqeusted that the size of the map, the amount of boats (including their lengths and names), be read from a file and used to set up the game.

The requriements included making it possible for the player to play agaisnt the computer but also against another person. Further, 2 additional modes were to be implemented: 
* Salvo mode where a player can shoot as many times as she has ships alive
* Mines mode where 5 mines are randomly placed on the map and when hit, damage any ships around them.

I designed the architecture with these requriements in mind. This lead me to the folowing key decisisons:
*  Create a configurationReader to get the data from the file.
*  Create a Menu class to get user game type and mode choices
*  Make the Game object constructor take fileConfiguration and userConfiguration structures to set up the game correctly
*  Give the Board class a list of populated points to ease with AI implementation
*  Give Ship objects a health property so I can tell when one is sunk.

### b) UML class dependency diagram
![](umlImage.png)

### c)  Development strategy and approach to quality
I used an Agile strategy for this project. Before beginning development, i made a class dependency diagram based on the requriements. Once the first iteration was compleate, I adjusted the diagram and did another iteration. This helped me ensure i'm meeting the current requriement and to plan ahead so I dont end up in a situation where the architecture of the program prevents me from meeting requirements i had yet to tackle.

Another way I ensured the high quality of the solution is by testing the code and looking for edge cases. This helped me find bugs early and fix them before the codebase grew and made this harder.

### d) and Problem decomposition
I broke down the problem into epics, and stories. I had 6 epics:
* Read data from file and get user game configuration data
  - create configurationReader class
  - create menu to take input 
* Create Classes
  - Ship
  - Point
  - Board
  - Game
* Allow for boat placement on the Board
  - Manual
  - Random placement for AI
* Turn taking
  - Shooting
    - Manual shooting
    - AI shooting
  - Determining winner
* Salvo mode (simple)
  - Determining amout of shots for player
* Mines
  - Mine creation
  - Mine explosion

By breaking the problem down i was able to structure the development so that functions I make in current stories would be useufl in the next ones.

It was key to split the problem in this way as it let me build upon my previous work by coordinating development tasks.

###  e) Object dependency plan
Looking at the dependency diagram shows you how I planned the development. First i craeted the Ship class and then ensure the configurationReader correctly initialises the Ship objects.

Next I created the Point class and tested it too.

Now I was able to make the Board which depends on the existance of Points. Here i implemented only the basic functions and in later iterations I added other functions to it.

Finally, I could create the Game class and begin working on boat placement. 