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


#include "../interface.h"

//Button

int Button::buttonCounter=0;
Button::Button()
{
    mPosition.x = 0;
    mPosition.y = 0;
    sno=buttonCounter;
    currentState = BUTTON_SPRITE_MOUSE_OUT;
    next=NULL;
    padding=0;
    visible=true;
    bgColor={255,255,255};
    selected=false;
    textColor={0,0,0};
    id=-1;
    buttonCounter++;
}

Button::Button(const Button& copy) {
    mPosition=copy.mPosition;
    sno=copy.sno;
    currentState=copy.currentState;
    padding=copy.padding;
    next=copy.next;
    textColor=copy.textColor;
    bgColor=copy.bgColor;
    visible=copy.visible;
    selected=copy.selected;
    id=copy.id;
}


Button::~Button(){
    sno=0;
    next=NULL;
}
void Button::renderButton(int x,int y){
    SDL_Rect box={ x, y, getWidth()+padding, getHeight()+padding};
    if(currentState==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        SDL_SetRenderDrawColor(gRenderer,hoverColor.r,hoverColor.g,hoverColor.b,hoverColor.a);
    }else{
        SDL_SetRenderDrawColor(gRenderer,bgColor.r,bgColor.g,bgColor.b,bgColor.a);
    }
    SDL_RenderFillRect(gRenderer,&box);
    render(x+padding/2,y+padding/2);
}

void Button::setPosition( int x, int y ){
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEvent( SDL_Event* e ){
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x ){
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + getWidth() ){
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y ){
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + getHeight() ){
			inside = false;
		}

		//Mouse is outside button
		if( !inside ){
			currentState = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else{
			//Set mouse over sprite
			switch( e->type ){
				case SDL_MOUSEMOTION:
				currentState = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				currentState = BUTTON_SPRITE_MOUSE_DOWN;
				break;

				case SDL_MOUSEBUTTONUP:
				currentState = BUTTON_SPRITE_MOUSE_UP;
				USER_SELECTED=id;
                                currentDisplay.NewEvent=true;
                                selected=true;
				break;
			}
		}
	}
}

void Button::manager(){
    
    if(selected&&USER_SELECTED!=id){
        selected=false;
    }
}
