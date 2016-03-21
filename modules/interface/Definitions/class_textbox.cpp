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

//TextBox

TextBox::TextBox(){
    x=y=0;
    width=300;
    height=28;
    MAXTEXTLEN=0;
    displayText="";
    input="";
    STATUS=NOT_ACTIVE;
    renderText=false;
    hiddenText=false;
    cursorX=0;
    cursorY=0;
    shiftIndex=0;
}

TextBox::TextBox(int tx, int ty){
    x=tx;
    y=ty;
    width=300;
    height=28;
    MAXTEXTLEN=0;
    displayText=input="";
    STATUS=NOT_ACTIVE;
    renderText=false;
    hiddenText=false;
    cursorX=0;
    cursorY=0;
    shiftIndex=0;
}

TextBox::~TextBox(){
    if(text.IsValid()){
        text.free();
    }
}
void TextBox::free(){
    text.close();
}

bool TextBox::init(){
    bool status=true;   //success flag

    MAXTEXTLEN=width/10;

    if(!text.loadMedia("res/arial.ttf",20)){
        status=false;
    }
    return status;
}
int cursorCounter=0;    //The cursor shown time sync

void TextBox::render(){
    if(renderText){             //if text is to be rendered
        gAnyText.reset();
        gAnyText.loadMedia("res/arial.ttf",20);
        if(input!=""){
        gAnyText.updateContent(input);
        }
        if(width-15<gAnyText.getWidth()){
            displayText=getDisplayableTextSize(input,width);
            hiddenText=true;
        }else {
            displayText=input;
            hiddenText=false;
        }
        if(displayText!=""){
                text.updateContent(displayText);
        }else{
                text.updateContent(" ");
                text.resetDimensions();
        }
        renderText=false;
    }
    text.render(x+3,y+3);
}


void TextBox::draw(){
    SDL_Rect TextRect = { x, y, width, height};
    //Background
    if(STATUS==NOT_ACTIVE){
        SDL_SetRenderDrawColor(gRenderer,0xF9,0xF9,0xF9,0xFF);
    }else if(STATUS==IS_ACTIVE){
        SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    }else if(STATUS==IS_FOCUSED){
        SDL_SetRenderDrawColor(gRenderer,0xF9,0xF9,0xF9,0xFF);
    }else if(STATUS==IS_LOCKED){
        SDL_SetRenderDrawColor(gRenderer,0xDE,0xDD,0xED,0xFF);
    }
    SDL_RenderFillRect(gRenderer,&TextRect);
    //Border
    if(STATUS==NOT_ACTIVE){
        SDL_SetRenderDrawColor(gRenderer,0x71,0x71,0x71,0xFF);
    }else if(STATUS==IS_ACTIVE){
        SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);
    }else if(STATUS==IS_FOCUSED){
        SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);
    }else if(STATUS==IS_LOCKED){
        SDL_SetRenderDrawColor(gRenderer,0x24,0x23,0x23,0x00);
    }
    SDL_RenderDrawRect(gRenderer,&TextRect);

    //cursor
    if(STATUS==IS_ACTIVE){
        if(cursorCounter<20){
            SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
            SDL_RenderDrawLine(gRenderer,cursorX+text.getWidth(),cursorY+2,cursorX+text.getWidth(),cursorY+height-4);
            cursorCounter++;
        }else{
            cursorCounter++;
            if(cursorCounter>40){
                    cursorCounter=0;
            }
        }
    }
}

bool TextBox::eventHandler(SDL_Event* e){
    bool status=false;  //indicate if some input provided
    if(STATUS==IS_ACTIVE){
        if( e->type == SDL_KEYDOWN ){
            //Handle backspace
            if( e->key.keysym.sym == SDLK_BACKSPACE && input.length() > 0 ){
                //lop off character
		input.pop_back();
		renderText = true;
            }
            //Handle copy
            else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ){
                SDL_SetClipboardText( input.c_str() );
            }
            //Handle paste
            else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ){
                string copy;
                copy = SDL_GetClipboardText();
                input=input+copy;
                renderText = true;
            }
            else if(e->key.keysym.sym==SDLK_RETURN){
                STATUS=IS_LOCKED;
            }
            else if( (e->key.keysym.sym==SDLK_LSHIFT || e->key.keysym.sym==SDLK_RSHIFT) ){
                if(e->key.keysym.sym==SDLK_LEFT)
                    shiftIndex--;
                else if(e->key.keysym.sym==SDLK_RIGHT)
                    shiftIndex++;
            }
        }
            //Special text input event
        else if( e->type == SDL_TEXTINPUT ){
            //Not copy or pasting
            if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ) {
                //Append character
		input += e->text.text;
                renderText = true;
            }
	}
    }
      	//If mouse event happened
    if( e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
		//Get mouse position
        int tx, ty;
        SDL_GetMouseState( &tx, &ty );
		//Check if mouse is in textbox
        if(tx>x&&ty>y&&tx<(x+width)&&ty<(y+height)){    //if inside
            STATUS=IS_ACTIVE;   //activates text box
        }else if(STATUS==IS_LOCKED){

        }else{
            STATUS=NOT_ACTIVE;
        }
    }else if(e->type==SDL_MOUSEMOTION&&STATUS!=IS_ACTIVE){
        int tx, ty;
        SDL_GetMouseState( &tx, &ty );
		//Check if mouse is in button
        if(tx>x&&ty>y&&tx<(x+width)&&ty<(y+height)&&STATUS!=IS_LOCKED){    //if inside
            STATUS=IS_FOCUSED;
        }else if(STATUS==IS_FOCUSED){
            STATUS=NOT_ACTIVE;
        }
    }
    if((e->type == SDL_MOUSEBUTTONUP||e->type==SDL_MOUSEMOTION)&&STATUS==IS_ACTIVE){
        	//Get mouse position
        int tx, ty;
		//Check if mouse is in textbox
        SDL_GetMouseState( &tx, &ty );

        bool inside=false;
        if(tx>x&&ty>y&&tx<(x+width)&&ty<(y+height)){
            inside=true;
        }
        if( inside&&!cursorBusy){    //if cursor is inside and no one occupy/changed/use it
            SDL_SetCursor(icursor);
            cursorBusy=true;
            cursorOwner=CURSOR_OWNER_URLBOX;
        }else if(!inside&&cursorBusy&&cursorOwner==CURSOR_OWNER_URLBOX){
            SDL_SetCursor(cursor);
            cursorOwner=CURSOR_OWNER_NONE;
            cursorBusy=false;
        }
    }
    return status;
}

string TextBox::getDisplayableTextSize(string in,int wi){
    bool flag=false;
    unsigned int i;
    string temp;
    for(i=0;i<in.length();i++){
        temp=in.substr(i);
        text.updateContent(temp);
        if( text.getWidth()<(wi-15) ){
            flag=true;
            break;
        }
    }
    if(flag)
        return temp;
    else
        return "";
}


bool TextBox::IsLocked(){
        if(STATUS==IS_LOCKED){
            return true;
        }else{
            return false;
        }
}

void TextBox::reset(){
    displayText="";
    input="";
    STATUS=NOT_ACTIVE;
    renderText=true;
}
