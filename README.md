# 📚 LIBRARY INFORMATION

## 🔎 LIB Information

1) **`<iostream>`**  
   -> 🖨️ Provides input and output functionality using `std::cout` and `std::cin`.  
   -> ✅ Essential for console-based applications.  

2) **`<windows.h>`**  
   -> 🪟 Gives access to the Windows API.  
   -> ✅ Useful for interacting with system-level features like creating processes, handling files, modifying registry entries, and interacting with system components.  

3) **`<winuser.h>`**  
   -> 🧩 Subset of the Windows API that provides functions for interacting with the user interface.  
   -> ✅ Used for operations like simulating keyboard and mouse events, managing windows, and handling GUI elements.  

4) **`<fstream>`**  
   -> 💾 Provides functionality for file handling in C++.  
   -> ✅ Contains classes like `std::ifstream` (for reading) and `std::ofstream` (for writing).  
   -> 🔒 Commonly used in keyloggers or system-monitoring applications to log data into files.  

---

## ⚠️ If your program involves
- 👉 Interacting with the Windows system (`windows.h` & `winuser.h`).  
- 👉 Capturing keystrokes (often using `GetAsyncKeyState()` from `winuser.h`).  
- 👉 Writing captured keystrokes to a file (`fstream`).  
- 👉 Displaying output to the console (`iostream`).  

---

## ❓ Why we removed `GetAsyncKeyState()` from `<winuser.h>`  
We removed `GetAsyncKeyState()` from the keylogger code because it polled key states for each key repeatedly. Instead, we use **Windows hooks** (`SetWindowsHookEx`) to capture key events more efficiently and reliably.

---

## 🔔 Logging Function (Hook Installation)

```cpp
keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger::keyLoggerProc, NULL, 0);
Explanation of each parameter:

WH_KEYBOARD_LL
-> 📥 Specifies a low-level keyboard hook.
-> ✅ Allows the program to monitor keyboard input globally (even outside the application).

Keylogger::keyLoggerProc
-> 🧠 The callback function (hook procedure) that will be called whenever a keyboard event occurs.

NULL
-> 🔗 The handle to the DLL module containing the hook.
-> ✅ NULL means the hook is being set for the current process only.

0
-> 🧵 Thread ID.
-> ✅ 0 installs the hook for all threads in the system (global hook).

🔎 What This Line Does

➕ Installs a keyboard hook that listens for key presses.

➕ Every time a key is pressed, keyLoggerProc is called.

➕ The program runs until it is manually stopped or exits.

🛠️ Why is This Used?

✅ Keylogger implementations.

✅ Custom global keyboard shortcuts.

✅ Security applications (e.g., detecting unauthorized keypress patterns).

🧩 What are DLLs and Hooks?
📦 DLL (Dynamic Link Library)

🔁 A file that contains code and functions multiple programs can use.

➕ Allows sharing code without embedding it into every executable.

🧾 Examples:

user32.dll — handles UI elements (windows, buttons, hooks).

kernel32.dll — handles system operations (files, memory, processes).

gdi32.dll — handles graphics operations.

🪝 Hook

🔍 A way to intercept events (keystrokes, mouse events, messages).

➕ Hooks allow a program to monitor or modify these events.

🧭 Types of Windows hooks:

WH_KEYBOARD_LL — Low-Level Keyboard Hook (captures key presses).

WH_MOUSE_LL — Low-Level Mouse Hook (captures mouse events).

WH_CBT — Detects system-level window changes.

WH_GETMESSAGE — Captures messages before they reach an application.

⚠️ Why Use Hooks and DLLs?

🛡️ Hooks let programs monitor input without modifying other applications.

🔁 DLLs are required when setting system-wide hooks across multiple processes because the hook procedure must be loaded into each process.

🌐 Global hooks often require the hook proc to be present in a DLL so it can be injected into other processes.

✅ Checking if the hook was successfully installed
if (!keyboardHook) {
    std::cout << "Failed to install hook! ❌" << std::endl;
}


✅ If keyboardHook is NULL, the installation failed — handle the error and log/notify accordingly.

🔔 Consider adding more diagnostic info (e.g., use GetLastError() to print the error code).


If you want, I can:
- add a short **example `keyLoggerProc`** function snippet, or  
- provide a **safe, non-malicious demo** showing how to set a keyboard hook for legitimate apps (hotkeys), or  
- export this as a `README.md` file ready to drop into a repo. Which would you like?
