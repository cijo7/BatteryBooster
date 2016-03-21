/* 
 * 
 *                        ||||||||||||||||||||                        |||||||||||||||||||||     
 *                       ||||||||||                                  ||||||||||                
 *                     |||||||||                                    |||||||                       
 *                    |||||                                         |||||                       
 *                  |||||                                           |||||                       
 *                  |||||                                            ||||||||                            
 *                  |||||                                              ||||||||||||                  
 *                  |||||                                                 |||||||||||||         
 *                  |||||                                                       |||||||||         
 *                  |||||                                                          ||||||||
 *                  |||||                                                         ||||||||    
 *                    |||||                                                     |||||||||       
 *                     |||||||||                        ||                      ||||||||               
 *                       ||||||||||                    ||||                   |||||||||           
 *                        |||||||||||||||||||||         ||           ||||||||||||||||
 * 
 * 
 * 
 * 
 * 
 * LICENCED: BY CIJO SAJU
 * 
 * YOU CAN USE,MODIFY,DISTRIBUTE THIS CODE AS LONG AS YOU AGREE TO THIS AGGREMENT
 * 
 * By using this code you agree to add this license where ever you use this code.
 * You may not place any further distribution of product made from this code.
 * 
 * 
 */

#include <SDL2//SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../interface/interface.h"

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Cursor* hcursor;//Hand cursor
SDL_Cursor* cursor;//Normal cursor
SDL_Cursor* icursor;//Text editor cursor
displayStates currentDisplay;

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
bool cursorBusy=false;  //Sync cursor. False when new event allowed
int cursorOwner=CURSOR_OWNER_NONE;

int USER_SELECTED=BUTTON_DOWNLOADS;
int USER_HIGHLIGHTED=0;
int CURRENT_SCREEN=-1;

Texture gAnyText;//Any texture. A global common texture
DisplayWindow window;

int start_manager(){
    
    return 0;
}

int pop_success(){
    return 0;
}