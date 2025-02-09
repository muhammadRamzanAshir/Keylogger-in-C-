
LIBRARY INFORMATION
LIB Information:
1) <iostream>:
    -> provide input and output functionality using std::cout and std::cin.
    -> Essential for console based application.
2) <windows.h>:
    -> Give access to windows API
    -> useful for interacting the system level  features like creating process handling files,
        modifying registry entries, intreacting with system components.
3) <winuser.h>:
    -> A subset of windows API that provide function for intreacting with the user interface , handling files
        modifying registry entries and intreacting with the system compnoents.
    -> use opeartion like stimulating keyboared and mouse events, managing windows and handling GUI elements
4) <fstream>:
    -> Provides functionality for file handling in C++.
    -> contains class like (std::ifstream for reading file )
    -> contains class like (std::ofstream for writing file)
    -> commanly used in  keylogger or the other system monitoring application to log the data into the file
5) If your program involves:
    -> Interacting with the Windows system (windows.h & winuser.h).
    -> Capturing keystrokes (often using GetAsyncKeyState() from winuser.h).
    -> Writing the captured keystrokes to a file (fstream).
    -> Displaying output to the console (iostream).
why we removed GetAsyncKeyState() from <winuser.h> ?
-> we removed GetAsyncKeyState() from the keylogger code because it was previously being used  to detact wheather the key was
    pressed or not while checking the key states for every key press. we use windows hooks (SetWindowsHookEx) to capture key
    events efficiently
|                                         Logging Function                                                     |
Explanation of each parameter:
keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger::keyLoggerProc, NULL, 0);
    ->Global Keyboared hook in  windows API
1)WH_KEYBOARD_LL:
    -> this specifies that we are setting a lowe-level-keyboared hook
    -> it allows the program to monitor keyboared input globally (even outside the application)
2)Keylogger::keyLoggerProc:ADJ_FREQUENCY
    -> This is the callback function (hook procedure) that will be called whenever a keyboared event occur
3) Null:
    -> The third parameter specifies the handle to the DLL module containing the hook
    -> Since the null, it means the hook is being set for the current process
4) 0:
    -> thread id
    -> this is installed for all threads in the system globally  (hook)
What This Line Does:
    -> it install  keyboared hoook that listen for keypress
    -> everytime key is pressed, keyLoggerProc is called
    -> this program run until the program manually stop or exit
Why is This Used?
    -> keylogger
    -> Custom keyboard shortcuts
    -> Security applications (e.g., detecting unauthorized keypresses).
what DLL and Hook ? 
DLL?
    -> Dynamic link library is a file contain code and function  that multiple program  can use
    -> instead of all code including  an executable
    -> share code dynamically
    Example of DLL Usage:
        -> user32.dll handle user interface element (windows, buttons, hooks)
        -> kernel32.dll handle system operation (file, memory,process)
        -> gdi32.dll handle graphic operation
Hook:
    -> way to intrecept events (like keystroke, mouseevents or message)
    -> Hooks allow a program to monitor or modify these events.
    Types of Hooks in Windows:
        -> WH_KEYBOARD_LL (Low-Level Keyboard Hook) → Captures key presses.
        -> WH_MOUSE_LL (Low-Level Mouse Hook) → Captures mouse events.
        -> WH_CBT (Computer-Based Training Hook) → Detects system-level window changes.
        -> WH_GETMESSAGE → Captures messages before they reach an application.
Why Use Hooks and DLLs?
    -> Hooks allow programs to monitor user input without modifying applications.
    -> DLLs are needed when setting system-wide hooks across multiple processes.
    -> Global hooks require DLLs because the hook procedure must be loaded into each process.
Checking if the hook was successfully installed ?
if(!keyboardHook){
    cout<< "Failed to install hook!" <<endl;
}
