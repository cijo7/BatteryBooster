/* 
 * File:   app.h
 * Author: cijo
 *
 * Created on 27 February, 2015, 7:50 PM
 */

#ifndef APP_H
#define	APP_H

#include <string>

/**
 * #define int range 200-299
 */
#define OS_WINDOWS
//#define OS_LINUX

#define BATTERY_LEVEL_FULL 210              //Battery level is 100%
#define BATTERY_LEVEL_HIGH 214              //Battery level is less than 100%
#define BATTERY_LEVEL_MEDIUM 211            //Battery level is less than 60%
#define BATTERY_LEVEL_LOW 212               //Battery level is less than 30%
#define BATTERY_LEVEL_CRITICAL 213          //Battery level is less than 10%

#define PLUGGED_IN 221
#define UNPLUGGED 222

typedef long Error;         //The hex value of error
typedef int ErrorCode;      //The error code
typedef int Code;           //The code

namespace App{
    extern std::string AppData;
    extern bool AppInitialized;
    extern std::string exe;
    extern std::string currentPath;
    extern int MAXWIDTH,MAXHEIGHT;
    
    /**
     * Initialize application
     */
    void InitializeApp();

    /**
     * Initializes App variables
     */
    void InitializeVariables();
        
    /**
     * Get Data about battery state
     */
    void BatteryInfo();
    
    /**
     * Kills the Main App
     */
    void Kill();
    
    /**
     * Finds the executing path of App and store it to exePath
     */
    void findPath();
    
    /**
     * Logs of App
     * @param logtext String to be logged
     */
    void Log(std::string logtext);
   

}



#endif	/* APP_H */

