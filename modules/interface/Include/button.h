/*
 * File:   button.h
 * Author: cijo
 *
 * Created on 23 January, 2015, 9:04 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H
#include "texture.h"

//The mouse button
class Button: public Texture
{
    public:
		//Initializes internal variables
	Button();
        Button(const Button& copy);                         //Copy Constructor
	virtual ~Button();                                  //Destructor
        void renderButton(int x,int y);                                      //Render
	void setPosition( int x, int y );                   //Sets top left position for mouse
	void setSno(int no){sno=no;}                        //Sets a seral number based on sequence of initialization
		//Handles mouse event
	void handleEvent( SDL_Event* e );                   //Handles the button events
        void manager();                                     //Manages the changes to button such as color changes ....
        void setVisibility(bool t){visible=t;}              //Sets the visibility of button
        bool isVisible(){return visible;}                   //Return true if Button is currently visible
        int getSno(){return sno;}                           //Return serial no.
        /**
         * Sets th button color
         * @param tcol text color
         * @param bg background color
         * @param hover(optional) background color on hovering
         */
        void setButtonColor(SDL_Color tcol,SDL_Color bg,SDL_Color hover){textColor=tcol;changeColor(textColor);bgColor=bg;hoverColor=hover;}
        void setPadding(int pad){padding=pad;}              //@param pad padding of button
        SDL_Color getBackgroundColor(){return bgColor;}     //Gets the Background color of the button
        SDL_Color getTextcolor(){return textColor;}         //Gets the Display text color of the button
        int getId(){return id;}                             //Returns the identification number corresponding to a button(As defined in the macro)
        void setId(int p){id=p;}                            //Sets the identification number
        bool ifSelected(){return selected;}                 //true if the button is currently selected
        void setSelection(bool input){selected=input;}      //Set the default selection/ used to give manual selection
        ButtonState currentButtonState(){return currentState;}//Get the last state of mouse events
        Button * next;                                      //The pointer for linking/grouping buttons

    protected:
        int sno;                                            //The button serial number useful to get idea about the initializing sequence of button
        bool visible;                                       //If button is visible
        int id;                                             //The id of button used for button identification
        bool selected;                                      //True if button is currently selected
    private:
	SDL_Point mPosition;                                //The positions
        int padding;                                        //Padding around the button
        SDL_Color bgColor;                                  //Background color of button
        SDL_Color textColor;                                //Text color of button
        SDL_Color hoverColor;                               //Color when hovered
        ButtonState currentState;                         //The button state
	static int buttonCounter;                           //Serial no of object
};

#endif	/* BUTTON_H */

