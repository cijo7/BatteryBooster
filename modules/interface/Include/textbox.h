/* 
 * File:   textbox.h
 * Author: cijo
 *
 * Created on 23 January, 2015, 8:57 PM
 */

#ifndef TEXTBOX_H
#define	TEXTBOX_H


#include <string>

using namespace std;

//The Text Box
class TextBox{
public:
    //Constructor
    TextBox();
    /**
     * Initialize a TextBox with custom Dimensions
     * @param Width
     * @param Height
     */
    TextBox(int,int);
    //Destructor
    virtual ~TextBox();
    //Render a TextBox on typing
    void render();
    //Draw a TextBox For first time
    void draw();
    /**
     * It check for key press and update the input string
     * @param the event pointer
     * @return true on enter press
     */
    bool eventHandler(SDL_Event*);
    //Initialize a TextBox by loading default resources @return true if success
    bool init();
    bool IsLocked();                                                            //If the textbox is locked then return true
    string getData(){return input;}                                             //@retuen the input to textbox
    void setStatus(int id){STATUS=id; }
    void reset();
    //retrieve variable's
    int getWidth(){return width;}
    /**
     *
     * @return X
     */
    int getX(){return x;}
    /**
     *
     * @return Y
     */
    int getY(){return y;}

    /*
     * Set Co-Ordinates
     * @param int @X The X Co-ordinate
     * @param int @Y The Y Co-ordinate
     * */
    void setXY(int xa,int yb){x=xa; y=yb;cursorX=xa+2;cursorY=yb+2;}
    void free();

private:
    /**
    *   Get the last part of string
    *   @param string input the input text
    *   @param int width the max width allowed
    *   @return string the last part o displayable text
    */
    string getDisplayableTextSize(string input,int width);
    string getDisplayText(){return displayText; }   //Return the currently displayed text
    int x,y;    //The Co-ordinates
    int width,height;   //The width and height
    string input;       //the actual input
    string displayText; //The display Text
    unsigned int MAXTEXTLEN;     //the length of display text
    Texture text;      //The texture holding input text
    bool renderText;
    bool hiddenText;    //True when text box had overflowed
    int cursorX,cursorY;
    int shiftIndex;
    int STATUS; //@value 0 when Not active \n   @value 1 when text box is highlighted and Is active \n  @value 2 when text input entered or is In active
};

#endif	/* TEXTBOX_H */

