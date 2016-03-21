
/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h> //sleep

#include "interface.h"

#define IMAGE_WIDTH 455
#define IMAGE_HEIGHT 200//445
#define REFRESH_LIMIT_POPUP_LEFT 15
#define REFRESH_LIMIT_POPUP_RIGHT (REFRESH_LIMIT_POPUP_LEFT+10)
#define FADE_SPEED 11


using namespace std;

#define ERROR_LOADING_SOUND string("Error Code:0x00000S")                            //unable to load
#define ERROR_LOADING_FONT string("Error Code:0x00000F")                             //unable to load
#define ERROR_LOADING_IMAGE string("Error Code:0x000000I")                           //unable to load
#define ERROR_SDL string("Error Code:0x00000U Cause:")+string(SDL_GetError())        //Unknown error occurred
const int MIN_RENDER_WIDTH=640;             //The minimum width that needs to be used
const int MIN_RENDER_HEIGHT=580;            //The minimum height to be used

			//Main loop flag
bool quitApp = false;
bool interfaceQuit=false;
DisplayWindow mywindow;//The main App window
Animation popup;
UINT8 CIalpha=SDL_ALPHA_TRANSPARENT;



//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close_Interface();

bool init(){
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO| SDL_INIT_AUDIO ) < 0 ){
#ifdef DEBUG_MODE
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
#endif
        success = false;
    }
    else{   //Success initialization of SDL
		//Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
#ifdef DEBUG_MODE
		printf( "Warning: Linear texture filtering not enabled!" );
#endif
            }
            //Create window
            if( !mywindow.init(DW_BORDERLESS,IMAGE_WIDTH,IMAGE_HEIGHT) ){
#ifdef DEBUG_MODE
                printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
#endif
                success = false;
            }
            else{
			//Create renderer for window
		gRenderer = mywindow.createRenderer();
                if( gRenderer == NULL ){
#ifdef DEBUG_MODE
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
#endif
                    success = false;
		}
		else{
				//Initialize renderer color
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Initialize PNG loading
                    int imgFlags = IMG_INIT_PNG;
                    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
#ifdef DEBUG_MODE
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
#endif
                        success = false;
                    }
				 //Initialize SDL_ttf
                    if( TTF_Init() == -1 ){
#ifdef DEBUG_MODE
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
#endif
			success = false;
                    }
				 //Initialize SDL_mixer
                    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
#ifdef DEBUG_MODE
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
#endif
                    }
                }
            }
    }
    return success;
}

void close_Interface(){

    if(interfaceQuit){
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;
        gAnyText.close();
        mywindow.free();                    //close the window
	//Quit SDL subsystems
        Mix_CloseAudio();//Close Audio
        Mix_Quit();//Release mixer
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	}
	interfaceQuit=false;
}

int notify_screen(int status){
    void Events();
    bool IsPlugged();
    interfaceQuit=false;
    Texture chargingIcon,notification;//Icon and text notifications
    Button close;//close button
        //The music that will be played
    Mix_Chunk *lSound = NULL;
    
    if( !init() ){
	App::Log( "Failed to Initialize!\n" );
    }else if( !notification.loadMedia(FONTS_CALIBRI,25)|| !close.loadMedia(FONTS_ARIAL,20)){ //LOAD RESOURSES
#ifdef DEBUG_MODE
        App::Log("Failed to load Fonts");
#else
        App::Log("Missing Resources. "+ERROR_LOADING_FONT);

#endif
    }else if(!chargingIcon.loadFromFile(ICON_BATTERY_STATUS,gRenderer)){
#ifdef DEBUG_MODE
        App::Log("Failed to load Image:images/battery-status.png");
#else
        App::Log("Missing Resources. "+ERROR_LOADING_IMAGE);
#endif
    }else{
        if(status==BATTERY_LEVEL_FULL)
            notification.loadFromRenderedText("Battery Full",{255,255,255,255});
        else if(status==BATTERY_LEVEL_MEDIUM)
            notification.loadFromRenderedText("Battery Level is below 50%",{255,255,255,255});
        else if(status==BATTERY_LEVEL_LOW)
            notification.loadFromRenderedText("Battery Level is Below 30%",{255,255,255,255});
        else if(status==BATTERY_LEVEL_CRITICAL)
            notification.loadFromRenderedText("Battery Level is Critically Low",{255,255,255,255});
        
        lSound = Mix_LoadWAV(FILE_MUSIC_NOTIFY );  //Load notification music
        if(lSound==NULL){
#ifdef DEBUG_MODE
        App::Log("Failed to load Sound at windows/tada.wav");
#else
        App::Log("Missing Resources. "+ERROR_LOADING_SOUND);
#endif
        }
        close.loadFromRenderedText("Later",{255,255,255,255});
        ButtonProperties closebutton={6,IMAGE_WIDTH-close.getWidth()-10,IMAGE_HEIGHT+30+notification.getHeight()-10};//x+width-padding-(small difference)
        close.setButtonColor({255,255,255,255},{0x59,0x59,0x59,0xFF},{0x00,0x00,0x00,0xFF});
        close.setPadding(closebutton.padding);
        close.setPosition(closebutton.x, closebutton.y);
        close.setSno(BUTTON_CLOSE);
        close.setId(BUTTON_CLOSE);
        
                        //Sets cursor
        hcursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                        //Configure window
        App::MAXWIDTH=mywindow.getWidth();
        App::MAXHEIGHT=mywindow.getHeight(); 
        int windowx;
			//Resize window
        if(IMAGE_WIDTH>notification.getWidth()){
            mywindow.changeSize(IMAGE_WIDTH,IMAGE_HEIGHT+30+close.getHeight()+notification.getHeight());
            windowx=IMAGE_WIDTH;
        }
        else{
            mywindow.changeSize(notification.getWidth(),IMAGE_HEIGHT+30+close.getHeight()+notification.getHeight());
            windowx=notification.getWidth();
        }
        windowx=App::MAXWIDTH-windowx;
        mywindow.changeXY(windowx,5);
            //initializing Pop-up animation
        popup.frameCount=0;
        popup.positionChange=true;
        popup.refreshRate=2;
        popup.direction=MOTION_LEFT;
        popup.type=status;
        
        SDL_Rect clip;
        if(status==BATTERY_LEVEL_FULL)
            clip={0,0,445,200};
        else if(status==BATTERY_LEVEL_MEDIUM)
            clip={0,200,445,200};
        else if(status==BATTERY_LEVEL_LOW)
            clip={0,400,445,200};
        else if(status==BATTERY_LEVEL_CRITICAL)
            clip={0,600,445,200};
        int xn,yn,xc;
        if(IMAGE_WIDTH>notification.getWidth()){
            xn=(IMAGE_WIDTH-notification.getWidth())/2;
            xc=0;
        }else{
            xn=0;
            xc=(notification.getWidth()-IMAGE_WIDTH)/2;
        }
        yn=IMAGE_HEIGHT+10;
        
        SCREEN_WIDTH=mywindow.getWidth();
        SCREEN_HEIGHT=mywindow.getHeight();
        SDL_Rect seperator={0,IMAGE_HEIGHT+15+notification.getHeight(),SCREEN_WIDTH,2};//Separator b/w notifications and close button
        
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(mywindow.getWindow(), &wmInfo);
        HWND hwnd = wmInfo.info.win.window;
        SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
        
        SDL_Event e;//Event handler 
        if(lSound!=NULL)//FIXME Invalid audio device id on second call
            Mix_PlayChannel( -1, lSound, 0 );
        while( !quitApp ){
#ifdef DEBUG_MODE
                        App::Log(SDL_GetError());
#else
                        if(string(SDL_GetError())!="")
                            App::Log("Something went wrong. "+ERROR_SDL);
#endif
                        SDL_ClearError();
                        SCREEN_WIDTH=mywindow.getWidth();
                        SCREEN_HEIGHT=mywindow.getHeight();
                        
                        //Handle events on queue
                        while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitApp = true;
                            }
                            mywindow.handleEvent(&e);
                            close.handleEvent(&e);
                        }
                        Events();//render only after taking events
#ifndef DEBUG_MODE
                        if(IsPlugged()&&status!=BATTERY_LEVEL_FULL)
                            quitApp=true;
                        else if(!IsPlugged()&&status==BATTERY_LEVEL_FULL)
                            quitApp=true;
#endif
                        if(!mywindow.isMinimized()){
				//Clear screen#3D83FF
                            SDL_SetRenderDrawColor( gRenderer, 0x3D, 0x83, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            
                            chargingIcon.setAlpha( CIalpha);
                            chargingIcon.render(xc,0,gRenderer,&clip);
                            close.renderButton(closebutton.x, closebutton.y);
                            if(close.currentButtonState()==BUTTON_SPRITE_MOUSE_OVER_MOTION)
                                SDL_SetCursor(hcursor);
                            else
                                SDL_SetCursor(cursor);
                            notification.render(xn,yn);
                            SDL_SetRenderDrawColor( gRenderer, 0x00 ,0x47,0xD7,0xFF );//#0047D7
                            SDL_RenderDrawRect( gRenderer,&seperator );                       //Draw the separator
				//Update screen
                            SDL_RenderPresent( gRenderer );
                        }
                        Sleep(40);
                    }
        quitApp=false;
        USER_SELECTED=NONE;
    }
    Mix_FreeChunk( lSound );
    lSound=NULL;
    chargingIcon.close();
    notification.close();
    close.close();
    interfaceQuit=true;
    close_Interface();
    return 0;
}


void Events(){
    switch(USER_SELECTED){
        case BUTTON_CLOSE:
            quitApp=true;
            break;
    }

    if(popup.positionChange){
        int tx=mywindow.getX(),ty=mywindow.getY();
        
        if(popup.frameCount<REFRESH_LIMIT_POPUP_LEFT)
            popup.direction=MOTION_LEFT;
        else if(popup.frameCount<REFRESH_LIMIT_POPUP_RIGHT)
            popup.direction=MOTION_RIGHT;
        else
            popup.positionChange=false;
        
        if(popup.direction==MOTION_LEFT)//Move left
            mywindow.changeXY(tx-popup.refreshRate,ty);
        else if(popup.direction==MOTION_RIGHT)//Move right
            mywindow.changeXY(tx+popup.refreshRate,ty);
        
        float calc;
        calc=FADE_SPEED*popup.frameCount;
        if(calc>SDL_ALPHA_OPAQUE){
            calc=(float)SDL_ALPHA_OPAQUE;
        }
        CIalpha=(UINT8)calc;
        
       
        popup.frameCount++;
    }
}

/**
 * Query if charger plugged
 * @return true when charger is plugged in
 */
bool IsPlugged(){
    unsigned char plugged;
#ifdef OS_WINDOWS
        SYSTEM_POWER_STATUS sps={0};
        ::GetSystemPowerStatus(&sps);
        plugged=sps.ACLineStatus;
#endif
        if(plugged==1)
            return true;
        else
            return false;
}