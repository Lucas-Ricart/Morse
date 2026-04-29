#include <windows.h>
#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, char> morse = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'},
        {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
        {"--.", 'G'}, {"....", 'H'}, {"..", 'I'},
        {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
        {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},
        {"...", 'S'}, {"-", 'T'}, {"..-", 'U'},
        {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
        {"-.--", 'Y'}, {"--..", 'Z'},
    };

    std::string sequence = "";
    int tiWithoutClick = 0;
    int loopTimer = 1000;

    while (tiWithoutClick < 7) {
        bool clickDetected = false;
        DWORD start = GetTickCount();

        while (GetTickCount() - start < loopTimer) {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                sequence += ".";
                tiWithoutClick = 0;
                clickDetected = true;
                Sleep(200);
                break;
            } else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                sequence += "-";
                tiWithoutClick = 0;
                clickDetected = true;
                Sleep(200);
                break;
            }
            Sleep(10);
        }
        if (!clickDetected) {
            tiWithoutClick++;
        }
        char lettre = morse.count(sequence) ? morse[sequence] : '?';
        std::cout << "\r" << lettre << std::flush;

        if (tiWithoutClick >= 3) {
            std::cout << std::endl;
            sequence = "";
        }
    }
    std::cout << " ";
    tiWithoutClick = 0;
    return 0;
}