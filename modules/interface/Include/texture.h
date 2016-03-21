/* 
 * File:   texture.h
 * Author: cijo
 *
 * Created on 23 January, 2015, 9:02 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H


#include <string>

using namespace std;

//Texture wrapper class
class Texture{
	public:
		//Initializes variables
		Texture();
		//Copy constructor
		Texture(Texture&);

		//Deallocates memory
		virtual ~Texture();

		/**
                 * \brief Loads image at specified path
                 * @return true if sucess
                 */
		bool loadFromFile( std::string path,SDL_Renderer* renderer=NULL  );

		//Creates image from font string @return true on success
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor,SDL_Renderer* renderer=NULL );

		//Deallocates texture
		void free();
                //Close all the resources
                void close();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
                //Change the color of texture
                void changeColor(SDL_Color col);
		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
                
                void resetDimensions(){mWidth=0;mHeight=0;}                                         //Resets the With and Height to zero.

		//Renders texture at given point
		void render( int x, int y,SDL_Renderer* render=NULL, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		bool loadMedia(string path,int sizeofFont=28);                                      //Loads the necessary files for texture to work
		void updateContent(string);                                                         //Update an existing texture wit new text
                void reset();                                                                       //Resets a texture
		bool IsValid(){ if(mTexture!=NULL){return true;} else{return false;}}               //true if the Texture contain a valid texture
                void renderParagraph(string tText,SDL_Color col,int xa,int ya,int tWidth);                     //Renders a large string by splitting the string and render it afterwards

		//Gets image dimensions
		int getWidth();                                                                     //Return the image/texture width
		int getHeight();                                                                    //Return the image/texture height
                int getX(){return x;}                                                               //Returns the Y Co-ordinates
                int getY(){return y;}                                                               //Returns the Y Co-ordinates
                /**
                 * Set the Co-ordinate
                 * @param xa
                 * @param ya
                 */
                void setXY(int xa,int ya){x=xa;y=ya;}                                               //Sets the X and Y Co-ordinates
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Globally used font
                TTF_Font *gFont;

		//Image dimensions
		int mWidth;
		int mHeight;
                int x,y;    //the Co-ordinates
		string text;

};


#endif	/* TEXTURE_H */

