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
