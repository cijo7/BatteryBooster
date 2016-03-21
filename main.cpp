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
 *
 * File:   main.cpp
 * Author: cijo
 *
 * Created on 27 February, 2015, 7:36 PM
 *
 */
//#define NOMINMAX
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sstream>
#include "include/app.h"
#ifdef OS_WINDOWS
#include <windows.h>
#endif
/**
 * #define range of int 100-199
 * #define error start from 0x000100-0x000199
 */


using namespace std;

/*
 * Windows Entry point
 */
//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,    LPSTR lpCmdLine, INT nCmdShow)

int main(int argc, char* argv[]){
#ifndef DEBUG_MODE
    Sleep(3*60*1000);       //Sleep for 3 minutes
#endif
    int notify_screen(int);

    App::InitializeApp();
   
    if(!App::AppInitialized){
#ifdef RELEASE_MODE
       App::Log("ERROR: Similar process is already running.");
       return 1;
#endif
    }
#ifdef DEBUG_MODE
    App::Log("Starting the program in Debug Mode");
#else
    App::Log("Starting the program.");
#endif
    int sleepTime;
    unsigned char plugged,chargelevel;
    while(true){
#ifdef OS_WINDOWS
        try{
        SYSTEM_POWER_STATUS sps={0};
        ::GetSystemPowerStatus(&sps);
        plugged=sps.ACLineStatus;
        chargelevel=sps.BatteryLifePercent;
        if(plugged==-1||chargelevel==-1) throw "Failed to retrieve system data.";
        }catch(string err ){
            App::Log(err);
        }
#endif
#ifdef OS_LINUX
#endif

        try{
            int chargePercent=chargelevel;
            stringstream t;
            t<<chargePercent;
            if(plugged==1)
                App::Log(string("Charging: ")+t.str()+ string("% ."));
            else
                App::Log(string("Charge Level: ")+t.str()+ string("% ."));
        }catch(...){}

        if(plugged==1){//Plugged
            if(chargelevel==100){     //Fully charged. Unplug
                App::Log("Battery is Full");
                notify_screen(BATTERY_LEVEL_FULL);
            }
            if(chargelevel<92)
                sleepTime=5*60;
            else
                sleepTime=30;
        }else if(plugged==0){//Unplugged
            if(chargelevel>=50)
                sleepTime=10*60;
            else if(chargelevel>=30){ //less than 50%
                App::Log("Battery charge is at moderate level.");
                notify_screen(BATTERY_LEVEL_MEDIUM);
                if(chargelevel>=35)
                    sleepTime=5*60;
                else
                     sleepTime=2*60;
            }
            else if(chargelevel>=10){//less than 30%
                App::Log("Battery is Low.");
                notify_screen(BATTERY_LEVEL_LOW);
                sleepTime=60;
            }
            else{//less than 10%
                App::Log("Battery is at Critical Level.");
                notify_screen(BATTERY_LEVEL_CRITICAL);
                sleepTime=30;
            }
        }
        
#ifdef DEBUG_MODE                               //Debugging Testing
        notify_screen(BATTERY_LEVEL_FULL);
        notify_screen(BATTERY_LEVEL_MEDIUM);
        notify_screen(BATTERY_LEVEL_LOW);
        notify_screen(BATTERY_LEVEL_CRITICAL);
#endif
#ifndef DEBUG_MODE                      //Debugging code terminator
        Sleep(sleepTime*1000);
#else
        cout<<"Sleep for the next"<<sleepTime<<" seconds";//Usefull to see the last sleep time been set
        break;
#endif
    }
    return 0;
}
