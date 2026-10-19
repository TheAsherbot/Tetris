This is windows only! It takes control over the windows terminal to display the game. 

## SETUP
You also NEED to set up your terminal to use windows console host. You can changes this by right clicking on the topbar of your cmd, then clicking propteries -> terminal then change the "defualt terminal application" to "windows console host"

## Controls! 
Z: Rotoate counter clockwise
X: Rotate clockwise
Left arrow: move object to the left
Right arrow: move object to the Right
Down arrow: move object down


## Enigne backend. 
I used the c++ windows API to get the handle to the console, and change the size, and stuff. non Windows Console Host terminals do not allow you to t change the size ect though the windows API.