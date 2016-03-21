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
 * Created on 28 February, 2015, 6:10 PM
 * 
 */

#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "../../include/app.h"

using namespace std;

/*
 * Trigger main
 */
#ifdef OS_WINDOWS  //Main 
#ifndef DEBUG_MODE
/*
 * Windows Entry point
 */
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,    PSTR lpCmdLine, INT nCmdShow)
#else
    /**
     * Default entry point
     * @return 0
     */
    int main(int argc, char** argv)
#endif
#else
    /**
     * Default entry point
     * @return 0
     */
    int main(int argc, char** argv)
#endif

{
    App::InitializeVariables();
    if(!App::AppInitialized){//when main App is running
        App::Kill();
    }
    return 0;
}
