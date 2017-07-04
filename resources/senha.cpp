//fonte https://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
#include <iostream>
#include <string>
#ifdef __linux__
    #include <termios.h>
    #include <unistd.h>
#else
    #include <windows.h>
#endif


using namespace std;


string digiteSenha(){
    cout << "Digite sua senha: " << endl;
    string s;
    #ifdef __linux__
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        getline(cin, s);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #else
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
        getline(cin, s);
        SetConsoleMode(hStdin, mode);
    #endif
    return s;
}

int main()
{
    cout << digiteSenha();
    return 0;
}