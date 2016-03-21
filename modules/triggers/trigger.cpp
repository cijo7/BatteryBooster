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
#include "../../include/app.h"

#ifdef OS_WINDOWS
#include <windows.h>
#include <process.h>//for terminate
#include <tlhelp32.h> //Processes
#include <cstring>  //For charchar
#include <winbase.h>    //for terminate

extern char sAppName[];

namespace App{
    void Kill(){
         HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
        PROCESSENTRY32 pEntry;
        pEntry.dwSize = sizeof (pEntry);
        BOOL hRes = Process32First(hSnapShot, &pEntry);
        while (hRes){
            if (strcmp(pEntry.szExeFile, sAppName) == 0){
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,(DWORD) pEntry.th32ProcessID);
                if (hProcess != NULL){
                    TerminateProcess(hProcess, 9);
                    CloseHandle(hProcess);
                }
            }
        hRes = Process32Next(hSnapShot, &pEntry);
        }
        CloseHandle(hSnapShot);
    }
}
#endif