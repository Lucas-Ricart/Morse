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
    std::string word ="";
    std::string message = "";
    int tiWithoutClick = 0;
    int tiLoop = 1000;

    while (true) {
        bool clickDetected = false;
        DWORD start = GetTickCount();

        while (GetTickCount() - start < tiLoop) {
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
        char letter = morse.count(sequence) ? morse[sequence] : '?';
        std::cout << "\r" << message << word << letter << std::flush;

        if (tiWithoutClick >= 3) {
            if (letter != '?') {
                word += letter;
            }
            sequence = "";
        }
        if (tiWithoutClick >= 7) {
            message += word + " ";
            word = "";
            tiWithoutClick = 0;
        }
    }
    return 0;
}