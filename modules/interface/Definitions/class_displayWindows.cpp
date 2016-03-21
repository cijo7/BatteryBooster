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

#include <SDL2/SDL_video.h>

#include "../interface.h"

//DisplayWindows starts


DisplayWindow::DisplayWindow(){
	//Initialize non-existing window
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
	mRender=NULL;
	x=y=no=0;
	mResize=false;
}

DisplayWindow::~DisplayWindow(){
    free();
}
bool DisplayWindow::init(int config,int w,int h,int x,int y){
    if(w==0||h==0){
        w=SCREEN_WIDTH;
        h=SCREEN_HEIGHT;
    }
	//Create window
    if(config==DW_MAXIMIZED_WINDOW){
	mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED );
    }else if(config==DW_ALL){
        mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    }else if(config==DW_MINIMIZED_WINDOW){
	mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MINIMIZED );
    }else if(config==DW_BASIC_CONFIGURATION){
        mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    }else if(config==DW_SPLASH||config==DW_BORDERLESS){
        if(x==0||y==0)
            mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS|SDL_WINDOW_MAXIMIZED);
        else
            mWindow = SDL_CreateWindow( "Battery Booster v1.0.0", x, y, w, h, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    }
    if( mWindow != NULL ){
            SDL_DisplayMode current;
            if(!SDL_GetCurrentDisplayMode(0, &current)){
		mWidth = current.w;
		mHeight = current.h;
            }else{
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
            }
		mMouseFocus = true;
		mKeyboardFocus = true;
    }
    return mWindow != NULL;
}

SDL_Renderer* DisplayWindow::createRenderer(){
	return SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void DisplayWindow::handleEvent( SDL_Event* e ){
	//Window event occurred
	if( e->type == SDL_WINDOWEVENT ){

		switch( e->window.event ){
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
                                mWidth = e->window.data1;
                                mHeight = e->window.data2;
                                currentDisplay.NewEvent=true;
			break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
                            currentDisplay.NewEvent=true;
			break;

			//Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
                            mMouseFocus = true;
			break;

			//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
                            mMouseFocus = false;
			break;

			//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
                            mKeyboardFocus = true;
			break;


			//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
                            mKeyboardFocus = false;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
                            mMinimized = true;
                            currentDisplay.NewEvent=true;
                        break;

			//Window maximized
			case SDL_WINDOWEVENT_MAXIMIZED:
                            mMinimized = false;
                            currentDisplay.NewEvent=true;
                        break;

			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
                            mMinimized = false;
                            currentDisplay.NewEvent=true;
                        break;
                        case SDL_WINDOWEVENT_RESIZED:
                           // SDL_SetWindowSize(mWindow,SCREEN_WIDTH,SCREEN_HEIGHT);
                        break;

		}


	}
	//Enter exit full screen on return key
	else if( e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN &&false)//remove the false to activate full screen
	{
		if( mFullScreen )
		{
			SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
			mFullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void DisplayWindow::free(){
        SDL_DestroyRenderer(mRender);
        mRender=NULL;
	if( mWindow != NULL )
	{
		SDL_DestroyWindow( mWindow );
	}
	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int DisplayWindow::getWidth(){
	return mWidth;
}

int DisplayWindow::getHeight(){
	return mHeight;
}

bool DisplayWindow::hasMouseFocus(){
	return mMouseFocus;
}

bool DisplayWindow::hasKeyboardFocus(){
	return mKeyboardFocus;
}

bool DisplayWindow::isMinimized(){
	return mMinimized;
}

void DisplayWindow::fullScreenMode(bool action){
    if( action ){
	SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
        mFullScreen = false;
    }
    else{
        SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
	mFullScreen = true;
	mMinimized = false;
    }
}


void DisplayWindow::changeSize(int xa, int ya){
    SDL_SetWindowSize(mWindow, xa, ya);
}
