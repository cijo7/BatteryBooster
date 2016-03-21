#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <cmath>

#include "../../include/app.h"

using namespace std;

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

//The button sprite
enum ButtonState
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};
struct displayStates{
    bool NewEvent=true;
    bool ScreenRefresh=false;
    
};
struct ButtonProperties{
    int padding;    //Padding around a button
    int x;          //The x- Cordinate
    int y;          //The y-Co-ordinate
};

typedef int MOTION;//Specifies the direction of motion
#define MOTION_LEFT 41
#define MOTION_RIGHT 42
#define MOTION_UP 43
#define MOTION_DOWN 44

struct Animation{
    bool positionChange;//True if there is change in position of animation
    int frameCount;     //Number of frames to draw
    int refreshRate;    //Refresh rates
    int type;           //The type or category of Animation being played
    MOTION direction;   //Moving direction
};

#define FONTS_CALIBRI "C:\\Windows\\Fonts\\Calibri.ttf"
#define FONTS_ARIAL "C:\\Windows\\Fonts\\arial.ttf"
#define ICON_BATTERY_STATUS std::string(App::currentPath+"images\\battery-status.png")
#define FILE_MUSIC_NOTIFY "C:\\Windows\\Media\\notify.wav"
#define CURSOR_OWNER_NONE 30
#define CURSOR_OWNER_MENU 31
#define CURSOR_OWNER_URLBOX 32

#define BUTTON_ABOUT 20
#define BUTTON_EXIT 21
#define BUTTON_DOWNLOADS 22
#define BUTTON_CLOSE 23
#define NONE 0


extern bool interfaceQuit;
extern bool cursorBusy;
extern int cursorOwner;
extern int USER_SELECTED;
extern int USER_HIGHLIGHTED;
extern int SCREEN_HEIGHT,SCREEN_WIDTH;
extern SDL_Renderer* gRenderer;
extern SDL_Cursor* hcursor;//Hand cursor
extern SDL_Cursor* cursor;//Normal cursor
extern SDL_Cursor* icursor;//editing cursor
extern displayStates currentDisplay;

#include "Include/texture.h"
extern Texture gAnyText;

#include "include/button.h"

//A custom textbox


#define NOT_ACTIVE 0    //before invocation when textbox is empty \n @value 0
#define IS_ACTIVE 1     //at invocation when typing the input to textbox \n @value 1
#define IS_FOCUSED 2    //When the textbox is focused using the mouse\n @value 2
#define IS_LOCKED 3     //When input is Finalized by user \n @value 3

#include "include/textbox.h"


//this class wrap a window as a whole

#define RENDER_VERTICAL 201                     //When rendering is done on interface in vertical mode
#define RENDER_HORIZONTAL 202                   //When rendering is done on interface in horizontal mode

class interfaceWindows{
public:
    interfaceWindows();
    virtual ~interfaceWindows();
    bool loadMedia();                           //Loads the objects
    void screenRefresh();                       //Manages to draw the core contents
    void calcDimensions();                      //Calculates the dimension of current window based on maximum sized member Texture
    void renderStyles();                        //Render the style associated with window
    void handleEvent(SDL_Event* e);             //Handle the whole events to a window
    Button* getRear(){return rear;}             //Gives the last button added \n @Return rear
    int getMaxWidth(){return w;}                //Return Maximum Width of Interface
    int getMaxHeight(){return h;}               //Return Maximum Height of Interface
    
    /**
     * Help to give a standard layout to buttons
     * @param mode Vertical or horizontal
     */
    void standardDisplay(int mode);
    
    /**
     * Create a new button with the parameters given 
     * @param text  The text to be displayed on Button
     * @param coX   X coordinate
     * @param coY   Y coordinate
     * @param bgColor   Background color of button
     * @param textColor Text color of Button
     * @param padding   Padding given to the sides of a button. By default value is 1.
     */
    void addButtons(string text,int coX,int coY,SDL_Color bgColor,SDL_Color textColor,int identifier=0, int padding=0);              //Adds a new button
    void close();                               //Closes a window by killing resources
protected:
    int buttonCount;
    SDL_Color selectColor;
private:
    void InsertIntoWindow(Button* np);          //Adds to button list in a window
    Button * front, * rear;                     //The Linked list handles for buttons 
    int w,h;                                    //the window width
    int x,y;                                    //Window Co-ordinates
};


#define DW_MAXIMIZED_WINDOW 30                 //flag for creating a maximized window
#define DW_BASIC_CONFIGURATION 31              //flag for manually configuring a basic window
#define DW_MINIMIZED_WINDOW 32                  //flag for a minimized window
#define DW_ALL 33                               //Flag for a normal fully editable window
#define DW_SPLASH 34                          //Flag for a standard screen size of 640x480
#define DW_BORDERLESS  35                         //Flag for borderless window

class DisplayWindow{                           //The window containing everything
    public:
                                                //Initializes internals
        DisplayWindow();
        virtual ~DisplayWindow();
                
                                                //Creates window
	bool init(int temp=DW_ALL,int w=480,int h=620,int x=0,int y=0);

                                                //Creates renderer from internal window
	SDL_Renderer* createRenderer();
        void initRenderer(){ mRender=SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );}
        SDL_Renderer* getRenderer(){return mRender;}            //Get the window specific renderer

                                                //Handles window events
        void handleEvent( SDL_Event* e );
        void fullScreenMode(bool action=true);                  //Sets a window to full screen
        void changeSize(int xa,int ya);                         //Change the window dimension @param x @param y
        /**
         * Changes and updates the coordinates
         * @param ax
         * @param ay
         */
        void changeXY(int ax,int ay){x=ax;y=ay;SDL_SetWindowPosition(mWindow,ax,ay);}
		
        void free();                    //Deallocates internals

		//Window dimensions
	int getWidth();                 //Window dimensions-Width
        int getHeight();                //Window dimensions-Height
        int getX(){return x;}
        int getY(){return y;}
        SDL_Window* getWindow(){ return mWindow;}   //Get the window
        int getScreenNo(){return no;}               //Get screen number

		//Window focus
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
        bool isResized(){return mResize;}

    private:
		//Window data
        SDL_Window* mWindow;
        SDL_Renderer* mRender;      //Window's renderer
        
		//Window dimensions
        int mWidth;             //Width
        int mHeight;            //Height
        int x,y;                //Co-ordinates
        int no;                 //Window number
		//Window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;
        bool mResize;
};

#endif // INTERFACE_H_INCLUDED
