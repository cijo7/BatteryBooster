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

#include <stdlib.h> //for getenv
#include <fstream>  //for file
#include <time.h>   //for time
#include <cstring>  //For char

#include "../include/app.h"
#ifdef OS_WINDOWS
#include <windows.h>//for winprocesss
#include <tlhelp32.h> //Processes
#endif
#ifdef DEBUG_MODE
#include <iostream>
#endif
/**
 * #define Integer starts from 300 - 399
 *
 */
#define FILENAME_LOG "Battery Booster/data/logs.txt"

#define ERROR_RETRIVING_ENVIRONMENT_VARIABLES 301   //Environment variables initialisation failed
#define ERROR_EMPTY_FILE_PATH 302                    //Current file path variables initialisation failed
#define ERROR_EMPTY_FOLDER_PATH 303                  //Current folder path variables initialisation failed
#define ERROR_EMPTY_STRING 304                      //String is empty

char sAppName[]="battery_bg.exe";
bool IsRunning();

namespace App{
    std::string AppData;                    //The AppData folder location
    bool AppInitialized;                    //True if App can be launched. Otherwise false.
    std::string currentPath;                //Path of currently executing executable
    int MAXWIDTH,MAXHEIGHT;                 //Screen resolution

    void InitializeApp(){
        AppInitialized=true;
        InitializeVariables();
        if(IsRunning()){
            AppInitialized=false;
        }
    }

    void InitializeVariables(){
        try{
            char *appData;
#ifdef OS_WINDOWS
            appData = getenv("APPDATA");
#endif
#ifdef OS_LINUX
            appData="";
#endif
            if(appData!=NULL){
                App::AppData=std::string(appData)+"/";
            }else{
                App::AppData="";
#ifdef OS_WINDOWS
                AppInitialized=false;
                throw ERROR_RETRIVING_ENVIRONMENT_VARIABLES;
#endif
            }

        }catch(ErrorCode err){
#ifdef DEBUG_MODE
            if(err==ERROR_RETRIVING_ENVIRONMENT_VARIABLES)
                App::Log("Unknown Environment Variables");
#endif
        }
        try{
            TCHAR filePath[MAX_PATH];
            ::GetModuleFileNameA(NULL,filePath,MAX_PATH);
            std::string temp=std::string(filePath);
            if(temp=="") throw ERROR_EMPTY_FILE_PATH;
            App::currentPath=temp.substr(0,temp.find_last_of("\\")+1);
            if(App::currentPath=="") throw ERROR_EMPTY_FOLDER_PATH;
        }catch(ErrorCode err){
#ifdef DEBUG_MODE
            if(err==ERROR_EMPTY_FILE_PATH)
                App::Log("Current file path is empty");
            else if(err==ERROR_EMPTY_FOLDER_PATH)
                App::Log("Current folder path is empty");
#endif
        }
    }

    void Log(std::string log){
#ifndef DEBUG_MODE
        try{
            if(log=="") throw ERROR_EMPTY_STRING;
            if(log.find_last_of("\n")!=log.npos)
                log=log.substr(0,log.find_last_of("\n"));
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );

            std::string fname=App::AppData+FILENAME_LOG;
            std::fstream f;
            f.open(fname.c_str(),std::ios::out|std::ios::in);
            if(f){             //If exists
                f.seekp(0,std::ios::end);
                f<<"[Time:"<<asctime(timeinfo)<<"] "<<log.c_str()<<"\r\n";     //Windows specific code ("\r\n")
            }else{           //If no logs exist
                std::fstream temp(fname.c_str(),std::ios::out);
                temp<<"[LOGS]\r\n\r\n";
                temp<<"[Time:"<<asctime(timeinfo)<<"] "<<log.c_str()<<"\r\n";     //Windows specific code ("\r\n")
                temp.close();
            }
            f.close();
        }catch(ErrorCode err){
            
        }
#else
std::cout<<log.c_str()<<"\n";;
#endif
    }
    
}

/**
 * Locks the application to prevent multiple opening as its useless
 * @return true if process is running
 */
bool IsRunning(){
#ifdef OS_WINDOWS
    PROCESSENTRY32 pe32 = {0};
    HANDLE hSnap;
    int bProcessFound=0;
        hSnap =CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);
        pe32.dwSize =sizeof(PROCESSENTRY32);
        BOOL hRes=Process32First(hSnap,&pe32);     // Can throw away, never an actual app
        while(hRes){
            if (strcmp(pe32.szExeFile,sAppName) == 0){    // Did we find our process?
                bProcessFound++;
            }
            hRes = Process32Next(hSnap, &pe32);
        }
        CloseHandle(hSnap);
        if(bProcessFound<=1)    // if we didn't find any duplicate process running...
        {
#ifdef DEBUG_MODE
            App::Log("No Duplicate Process is Running");
#endif
            return false;
        }else{
#ifdef DEBUG_MODE
            App::Log("Similar Process is already Running.");
#endif
            return true;
        }

#endif
}
