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
#include <SDL2/SDL_render.h>

Texture::Texture(){
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
    gFont=NULL;
    x=0;
    y=0;
}

Texture::Texture(Texture & obj){
    mTexture=obj.mTexture;
    mWidth=obj.mWidth;
    mHeight=obj.mHeight;
    gFont=obj.gFont;
    x=obj.x;
    y=obj.y;
}

Texture::~Texture(){
        if(gFont!=NULL){
            //Free font
            TTF_CloseFont( gFont );
            gFont = NULL;
        }
	//Deallocate
	free();
}

bool Texture::loadFromFile( std::string path ,SDL_Renderer* renderer ){
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
#ifdef DEBUG_MODE
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
#endif
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGBA( loadedSurface->format, 0, 0xFF, 0xFF ,0xFF) );

		//Create texture from surface pixels
                if(renderer==NULL){
                    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                }else{
                    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                }
                
		if( newTexture == NULL ){
#ifdef  DEBUG_MODE
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
#endif
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor ,SDL_Renderer* renderer){
	//Get rid of preexisting texture
	free();
        text=textureText;
        if(gFont==NULL){
#ifdef DEBUG_MODE
            cout<<"No font\n";
#endif
            return false;
        }
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
	if( textSurface == NULL ){
#ifdef DEBUG_MODE
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
#endif
	}
	else{
		//Create texture from surface pixels
            if(renderer==NULL){
                mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
            }else{
                mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
            }
            if( mTexture == NULL ){
#ifdef DEBUG_MODE
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
#endif
            }
            else{
			//Get image dimensions
                mWidth = textSurface->w;
                mHeight = textSurface->h;
            }
		//Get rid of old surface
            SDL_FreeSurface( textSurface );
	}
	//Return success
	return mTexture != NULL;
}

void Texture::changeColor(SDL_Color colour){
    free();
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), colour );
	if(textSurface!=NULL){

		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL ){
#ifdef DEBUG_MODE
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
#endif
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
}

void Texture::free(){
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

}
void Texture::close(){
    if(gFont!=NULL){
            //Free font
        TTF_CloseFont( gFont );
        gFont = NULL;
    }
    free();
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending ){
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha ){
	//Modulate texture alpha
    if(mTexture)
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render( int x, int y,SDL_Renderer* render, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    setXY(x,y);
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
        if(render==NULL){
        	//Render to screen
            SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );   
        }else{
            SDL_RenderCopyEx( render, mTexture, clip, &renderQuad, angle, center, flip );   
        }
}

int Texture::getWidth(){
	return mWidth;
}

int Texture::getHeight(){
	return mHeight;
}

bool Texture::loadMedia(string path,int sizeofFont){
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( path.c_str(), sizeofFont );
	if(gFont == NULL ){
#ifdef DEBUG_MODE
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
#endif
		success = false;
	}

	return success;
}



void Texture::updateContent(string t){
//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if( !loadFromRenderedText( t, textColor ) ){
#ifdef DEBUG_MODE
			printf( "Failed to render text texture!\n" );
#endif

		}
}

void Texture::reset(){
    TTF_CloseFont(gFont);
    gFont=NULL;
}


void Texture::renderParagraph(string tText,SDL_Color col,int xa,int ya,int tWidth){
    int len=tText.length();
    string temp;
    int start=0,line=0;
    for(int i=len;i>0;i--){
        if(tText.substr(i,1)==" "){
        try{
            temp=tText.substr(start,i-start);
        }catch(exception &e){
            cout<<"Exception"<<e.what();
        }
        if(temp==""){
            break;
        }

        if( !loadFromRenderedText( temp, col ) ){
#ifdef DEBUG_MODE
            printf( "Failed to render text texture!\n" );
#endif
        }else if(this->getWidth()<tWidth ){
            this->render(xa,ya+line*this->getHeight());
            line++;
            start=i+1;
            i=len;
        }
        }
        if(i<=start){
            break;
        }
    }
}
