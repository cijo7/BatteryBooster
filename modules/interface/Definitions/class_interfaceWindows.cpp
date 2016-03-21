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
#include <iostream>


//The window actions

interfaceWindows::interfaceWindows() {
    front=rear=NULL;
    buttonCount=0;
    selectColor={0,0,0,255};
    w=0;
    h=0;
    x=0;
    y=0;
}
interfaceWindows::~interfaceWindows(){

}

void interfaceWindows::screenRefresh(){

    int i=0;
    Button* temp=front;
    while(temp){
            if(USER_HIGHLIGHTED==temp->getSno()){

                temp->render(temp->getX(), temp->getY());

            }else{
                temp->render(temp->getX(), temp->getY());
                }
        temp=temp->next;
        i++;
    }
}

bool interfaceWindows::loadMedia(){


    return true;
}

void interfaceWindows::calcDimensions(){
    int maxw=0,maxh=0,i=0; //temporary variables
    Button * temp=front;
    while(temp){
        if(maxw<temp->getWidth()){
            maxw=temp->getWidth();
        }
        maxh+=temp->getHeight();
        temp=temp->next;
        i++;
    }
    w=maxw;
    h=maxh;

}

void interfaceWindows::renderStyles(){
    int theight=0;
    //Draw red horizontal line
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderDrawLine( gRenderer, 0,  17,25+ w,  17  );
    Button * temp=front;
    for(int i=0;i<buttonCount||temp;i++){
        theight=temp->getHeight();
        temp->manager();
            //Render the specified color to background quad
        SDL_Rect fillRect = { 0, i*theight+theight/2+i*4-1, w+24, theight+3};
        if(temp->ifSelected()){
            SDL_SetRenderDrawColor( gRenderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a );
        }else{
            SDL_SetRenderDrawColor( gRenderer, temp->getBackgroundColor().r, temp->getBackgroundColor().g, temp->getBackgroundColor().b, temp->getBackgroundColor().a );
        }
        SDL_RenderFillRect( gRenderer, &fillRect );
            //Draw red horizontal line
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderDrawLine( gRenderer, 0,  (i+1)*theight+theight/2+i*4+2,25+ w,  theight*(i+1)+theight/2 +i*4 +2);
        temp=temp->next;
    }
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_Rect box={1,1,25+w,buttonCount*theight+theight+buttonCount*4};
    //Draw the blue box
    SDL_RenderDrawRect(gRenderer,&box);
}

void interfaceWindows::InsertIntoWindow(Button* np){
    if(front==NULL){
        front=rear=np;
    }else{
        rear->next=np;
        rear=rear->next;
    }
}

void interfaceWindows::addButtons(string text, int coX, int coY, SDL_Color bgCol, SDL_Color textCol,int identifier, int padding ){
    Button* tmp=new Button();
    tmp->loadMedia("res/menu.ttf");
    tmp->loadFromRenderedText(text,textCol);
    tmp->setButtonColor(textCol,bgCol,{0,0,0,0});
    tmp->setPosition(coX, coY);
    tmp->setXY(coX,coY);
    tmp->setSno(identifier);
    tmp->setId(identifier);
    if(identifier==BUTTON_DOWNLOADS){
        tmp->setSelection(true);
    }
    InsertIntoWindow(tmp);
    buttonCount++;
}

void interfaceWindows::handleEvent(SDL_Event* e){
    bool flag=false;
    for(  Button * temp=front;temp;temp=temp->next){
        temp->handleEvent(e);
        if(temp->currentButtonState()!=ButtonState::BUTTON_SPRITE_MOUSE_OUT){
            flag=true;
        }
    }
    if(flag&&!cursorBusy){
        SDL_SetCursor(hcursor);
        cursorBusy=true; 
        cursorOwner=CURSOR_OWNER_MENU;
    }else if(!flag&&cursorBusy&&cursorOwner==CURSOR_OWNER_MENU){
        SDL_SetCursor(cursor);
        cursorOwner=CURSOR_OWNER_NONE;
        cursorBusy=false;
    }
}

void interfaceWindows::close(){
    Button * temp;
    while(front){
        temp=front;
        front=front->next;
        delete temp;
    }
    front=rear=NULL;
}

void interfaceWindows::standardDisplay(int mode){
    int ha=0;
        ha=rear->getHeight();
        rear->setPosition(20,ha/2+(buttonCount-1)*ha+(buttonCount-1)*4);
        rear->setXY(20,ha/2+(buttonCount-1)*ha+(buttonCount-1)*4);
}
