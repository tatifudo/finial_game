/*
  MeggyJr_CheckButtonsPress.pde
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
 from the Meggy Jr RGB library for Arduino
 
 Test which buttons have been pressed, since last we checked,
using the CheckButtonsPress() routine.

 
 
 Version 1.22 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
 	  
 */


 
//The point of the game is to make all the dots on the board show a color without touching the red or blue dots. If that occurs the player will be forced to start over. 
//When the player reaches the green dot they will be transported to the other side of the board where they will do the same thing. After all the dots are colored, the player needs to make their way over to the violet dot to win the game.

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.
int BD=1;
int xdot=0;
int ydot=1;
int counter = 1; //counter that will allow player to 'move' at different rate 
//then the backdrop changes
int xarray[64] = {0}; //Making and initializing the snake array.
int yarray[64] = {1}; //Where you start is up to you! The two points
int dotLength = 1;

void setup()                    // run once, when the sketch starts
{

  MeggyJrSimpleSetup();      // Required code, line 2 of 2.

}  // End setup()


void loop()                     // run over and over again
{  
  ClearSlate (); 
  
  if (BD==1)
      {
       DrawBackdrop1();
        }
     else DrawBackdrop2();
 

 CheckButtonsPress();   //Check to see which buttons are down that weren't before.
  if (Button_Up)  
    {  
    yarray[0] = yarray[0] + 1; 
    dotLength = dotLength + 1;
    }

  if (Button_Down)    
   {
   yarray[0] = yarray[0] - 1;  
   dotLength = dotLength + 1;
   }
  
  if (Button_Right)   
   {  
    xarray[0] = xarray[0] + 1;  
    dotLength = dotLength + 1;
    }  

  if (Button_Left)  
   {  
     xarray[0] = xarray[0] - 1; 
    dotLength = dotLength + 1;
    }
     
//keep from going out of bounds by wrapping
if (yarray[0] > 7) //keeps y coord from going out of bounds
yarray[0] = 7;
if (yarray[0] < 0) //keeps y coord from going out of bounds
yarray[0] = 0;

if (xarray[0] > 7) //keeps x coord from going out of bounds
xarray[0] = 7;
if (xarray[0] < 0) //keeps x coord from going out of bounds
xarray[0] = 0;

     
if (ReadPx(xarray[0], yarray[0]) == Red)  //collision code to make dot go to beginning
  {
    xarray[0] = 0;
    yarray[0] = 1;
  }
 if (ReadPx(xarray[0], yarray[0]) == Blue)  //collision code to make dot go to beginning
  {
    xarray[0] = 0;
    yarray[0] = 1;
  }
 if (ReadPx(xarray[0], yarray[0]) == Green)  //collision code to make dot go to beginning
  {
    xarray[0] = 7;
    yarray[0] = 6;
  }
  
 if (ReadPx(xarray[0], yarray[0]) == Violet)  //collision code to make game end
{
    for (int i=0; i<8; i++)
      {  
          for (int j=0; j<8; j++)
            {
                DrawPx(xarray[i], yarray[j],White);
            }
      }
  }
  
 
Updatedot(); //Call this method to update the snake coords.
Drawdot(); //Call this method to draw the new snake coords to memory. 
DisplaySlate();      // Write the updated game buffer to the screen.
  //delay(250); Going to use a counter and modulo's instead of delay
  counter = counter + 1;
  
}//end of main loop


void DrawBackdrop1()//draw backdrop one to the game
{
DrawPx(0,0,Blue); //move
DrawPx(1,1,Blue); //move
DrawPx(2,2,Blue); //move
DrawPx(4,4,Blue); //move
DrawPx(5,5,Blue); //move
DrawPx(6,6,Blue); //move
DrawPx(0,7,Red); //move
DrawPx(1,0,Red); //move
DrawPx(1,4,Red); //move
DrawPx(2,7,Red); //move
DrawPx(4,1,Red); //move
DrawPx(4,5,Red); //move
DrawPx(6,3,Red); //move
DrawPx(7,0,Red); //move
DrawPx(3,4,Violet); 
DrawPx(6,7,Green); 

//NOTE: The main loop is run through about 1000 times a second.
//We can use a counter that counts the number of times through the loop.
//In this code, when the # of times through loop divided by 1000 has 0 as a remainder, then switch backdrops
if (counter%1000 == 0) //this will allow the backdrop to run at a different rate                                       //than the player
  {
    BD=2;
  }
} //end of drawbackdrop 1

void DrawBackdrop2()
{
DrawPx(3,3,Blue); //move
DrawPx(1,1,Blue); //move
DrawPx(2,2,Blue); //move
DrawPx(7,7,Blue); //move
DrawPx(5,5,Blue); //move
DrawPx(6,6,Blue); //move
DrawPx(0,6,Red); //move
DrawPx(2,0,Red); //move
DrawPx(1,3,Red); //move
DrawPx(3,7,Red); //move
DrawPx(4,0,Red); //move
DrawPx(4,6,Red); //move
DrawPx(7,3,Red); //move
DrawPx(7,1,Red); //move
DrawPx(3,4,Violet); 
DrawPx(6,7,Green); 

if (counter%1000 == 0) //this will allow the backdrop to run at a different rate                                       //than the player
  {
    BD=1;
  }
} //end of drawbackdrop 2

void Updatedot()
//First: Reset snake coords from back to front, except for snake head.
//Second: Reset snake head coords, based on direction variable.
{
for (int i = dotLength; i < 0; i--) //reset snake body coords from back to front
{
xarray[i] = xarray[i-1]; //Steps backwards through the snake array
yarray[i] = yarray[i-1]; //Each snake body segment's new coords are now set to the 'old' coords
//of the snake body segment in 'front' of it.
//So, snake body segment D, is where C was one loop ago, and C is where B was
//one loop ago, like they are all moving over one seat in a movie theater.
}
}

void Drawdot() //Draws the snake's new coords to memory.
{
for (int i = 0; i < dotLength - 1; i++) //Draw the body blue in color
{
DrawPx(xarray[i], yarray[i], White);
}
}
