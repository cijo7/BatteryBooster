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
 * Created on 14 March, 2015, 2:11 PM
 * 
 */

#include <cstdlib>
#include "../../include/app.h"

using namespace std;
#define INSTALLER "installed"
/*
 * 
 */
int main(int argc, char* argv[]) {

    App::InitializeApp();
    string parameter="";
    if(!App::AppInitialized){
        App::Log("GUI Failed to Initialize.");
        return 1;
    }
    int start_manager();
    int pop_success();
    
    if(argc>1){
        parameter=string(argv[1]);
        App::Log("We received a parameter: " +parameter );
    }
    if(parameter!=""){
        if(parameter==INSTALLER){
            pop_success();
        }
    }else{
        start_manager();
    }
    return 0;
}

