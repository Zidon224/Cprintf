/*
    Cprintf

    The basic implementation of the default printf function with few more features and small aditions.

    Features:
    # Same known features as default printf
    # Unicode charset support (UTF-8)
    # Ansi escape codes:
        RGB support, 
        XTerm 255 color array, 
        Standard colors

    Changelogs:

    - 16.11.2023: First publish
    - 24.11.2023: New comits
*/
/*
    MIT License

    Copyright (c) 2023 Zidon224

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <Windows.h>
#endif




//Predefined default strings for color flag detections
#define ansiR               "\033[31m"
#define ansiG               "\033[32m"
#define ansiY               "\033[33m"
#define ansiB               "\033[34m"
#define ansiM               "\033[35m"
#define ansiC               "\033[36m"
#define ansiW               "\033[37m"
#define ansiDF              "\033[39m"
#define ansiBR              "\033[41m"
#define ansiBG              "\033[42m"
#define ansiBY              "\033[43m"
#define ansiBB              "\033[44m"
#define ansiBM              "\033[45m"
#define ansiBC              "\033[46m"
#define ansiBW              "\033[47m"
#define ansiBDF             "\033[49m"
#define ansiFGBrightBlack   "\033[90m"
#define ansiFGBrightRed     "\033[91m"
#define ansiFGBrightGreen   "\033[92m"
#define ansiFGBrightYellow  "\033[93m"
#define ansiFGBrightBlue    "\033[94m"
#define ansiFGBrightMagenta "\033[95m"
#define ansiFGBrightCyan    "\033[96m"
#define ansiFGBrightWhite   "\033[97m"
#define ansiBGBrightBlack   "\033[100m"
#define ansiBGBrightRed     "\033[101m"
#define ansiBGBrightGreen   "\033[102m"
#define ansiBGBrightYellow  "\033[103m"
#define ansiBGBrightBlue    "\033[104m"
#define ansiBGBrightMagenta "\033[105m"
#define ansiBGBrightCyan    "\033[106m"
#define ansiBGBrightWhite   "\033[107m"
#define ansiRst             "\033[0m"
#define ansiFullCtrl        "\033["





char *_strrev (char *str)
{
    int i;
    int len = 0;
    char c;
    if (!str)
        return NULL;
    while(str[len] != '\0')
    {
        len++;
    }
    for(i = 0; i < (len/2); i++)
    {
        c = str[i];
        str [i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
    return str;
}

char * _itoa(int i, char *strout, int base)
{
    char *str = strout;
    int digit, sign = 0;
    if (i < 0) 
    {
        sign = 1;
        i *= -1;
    }
    while(i) 
    {
        digit = i % base;
        *str = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
        i = i / base;
        str ++;
    }
    if(sign) 
    {
        *str++ = '-';
    }
    *str = '\0';
    _strrev(strout);
    return strout;
}

int cprintf(char * str, ...)
{
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
        SetConsoleOutputCP(CP_UTF8);
    #endif

    va_list vl;
    int i = 0, j=0;
    char buff[100]={0}, tmp[20];
    char * str_arg;
  
    va_start( vl, str );
    while (str && str[i])
    {
        if(str[i] == '%')
        {
            i++;
            switch (str[i]) 
            {
                case 'c': 
                {
                    buff[j] = (char)va_arg( vl, int );
                    j++;
                    break;
                }
                case 'd':
                {
                    _itoa(va_arg( vl, int ), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 'x': 
                {
                    _itoa(va_arg( vl, int ), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 'o': 
                {
                    _itoa(va_arg( vl, int ), tmp, 8);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's': 
                {
                    str_arg = va_arg( vl, char* );
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
                    break;
                }
            }
        }
        //Ansi flags
            else if(str[i] == '#')
            {
                i++;
                switch (str[i]) 
                {
                    case 'r': 
                    {
                        strcpy(&buff[j], ansiR);
                        j += strlen(ansiR);
                        break;
                    }
                    case 'g':
                    {
                        strcpy(&buff[j], ansiG);
                        j += strlen(ansiG);
                        break;
                    }
                    case 'y':
                    {
                        strcpy(&buff[j], ansiY);
                        j += strlen(ansiY);
                        break;
                    }
                    case 'b':
                    {
                        strcpy(&buff[j], ansiB);
                        j += strlen(ansiB);
                        break;
                    }
                    case 'm':
                    {
                        strcpy(&buff[j], ansiM);
                        j += strlen(ansiM);
                        break;
                    }
                    case 'c':
                    {
                        strcpy(&buff[j], ansiC);
                        j += strlen(ansiC);
                        break;
                    }
                    case 'w':
                    {
                        strcpy(&buff[j], ansiW);
                        j += strlen(ansiW);
                        break;
                    }
                    case 'd':
                    {
                        strcpy(&buff[j], ansiDF);
                        j += strlen(ansiDF);
                        break;
                    }
                    case 'x':
                    {
                        strcpy(&buff[j], ansiRst);
                        j += strlen(ansiRst);
                        break;
                    }
                }
            }
            else if(str[i] == '$')
            {
                i++;
                switch (str[i]) 
                {
                    case 'r': 
                    {
                        strcpy(&buff[j], ansiBR);
                        j += strlen(ansiBR);
                        break;
                    }
                    case 'g':
                    {
                        strcpy(&buff[j], ansiBG);
                        j += strlen(ansiBG);
                        break;
                    }
                    case 'y':
                    {
                        strcpy(&buff[j], ansiBY);
                        j += strlen(ansiBY);
                        break;
                    }
                    case 'b':
                    {
                        strcpy(&buff[j], ansiBB);
                        j += strlen(ansiBB);
                        break;
                    }
                    case 'm':
                    {
                        strcpy(&buff[j], ansiBM);
                        j += strlen(ansiBM);
                        break;
                    }
                    case 'c':
                    {
                        strcpy(&buff[j], ansiBC);
                        j += strlen(ansiBC);
                        break;
                    }
                    case 'w':
                    {
                        strcpy(&buff[j], ansiBW);
                        j += strlen(ansiBW);
                        break;
                    }
                    case 'd':
                    {
                        strcpy(&buff[j], ansiBDF);
                        j += strlen(ansiBDF);
                        break;
                    }
                    case 'x':
                    {
                        strcpy(&buff[j], ansiRst);
                        j += strlen(ansiRst);
                        break;
                    }
                }
            }
            else if(str[i] == '&')
            {
                i++;
                switch (str[i]) 
                {
                    case 'r': 
                    {
                        strcpy(&buff[j], ansiFGBrightRed);
                        j += strlen(ansiFGBrightRed);
                       break;
                    }
                    case 'g':
                    {
                        strcpy(&buff[j], ansiFGBrightGreen);
                        j += strlen(ansiFGBrightGreen);
                        break;
                    }
                    case 'y':
                    {
                        strcpy(&buff[j], ansiFGBrightYellow);
                        j += strlen(ansiFGBrightYellow);
                        break;
                    }
                    case 'b':
                    {
                        strcpy(&buff[j], ansiFGBrightBlue);
                        j += strlen(ansiFGBrightBlue);
                        break;
                    }
                    case 'm':
                    {
                        strcpy(&buff[j], ansiFGBrightMagenta);
                        j += strlen(ansiFGBrightMagenta);
                        break;
                    }
                    case 'c':
                    {
                        strcpy(&buff[j], ansiFGBrightCyan);
                        j += strlen(ansiFGBrightCyan);
                        break;
                    }
                    case 'w':
                    {
                        strcpy(&buff[j], ansiFGBrightWhite);
                        j += strlen(ansiFGBrightWhite);
                        break;
                    }
                    case 'x':
                    {
                        strcpy(&buff[j], ansiRst);
                        j += strlen(ansiRst);
                        break;
                    }
                }
            }
            else if(str[i] == '@')
            {
                i++;
                switch (str[i]) 
                {
                    case 'r': 
                    {
                        strcpy(&buff[j], ansiBGBrightRed);
                        j += strlen(ansiBGBrightRed);
                        break;
                    }
                    case 'g':
                    {
                        strcpy(&buff[j], ansiBGBrightGreen);
                        j += strlen(ansiBGBrightGreen);
                        break;
                    }
                    case 'y':
                    {
                        strcpy(&buff[j], ansiBGBrightYellow);
                        j += strlen(ansiBGBrightYellow);
                        break;
                    }
                    case 'b':
                    {
                        strcpy(&buff[j], ansiBGBrightBlue);
                        j += strlen(ansiBGBrightBlue);
                        break;
                    }
                    case 'm':
                    {
                        strcpy(&buff[j], ansiBGBrightMagenta);
                        j += strlen(ansiBGBrightMagenta);
                        break;
                    }
                    case 'c':
                    {
                        strcpy(&buff[j], ansiBGBrightCyan);
                        j += strlen(ansiBGBrightCyan);
                        break;
                    }
                    case 'w':
                    {
                        strcpy(&buff[j], ansiBGBrightWhite);
                        j += strlen(ansiBGBrightWhite);
                        break;
                    }
                    case 'x':
                    {
                        strcpy(&buff[j], ansiRst);
                        j += strlen(ansiRst);
                        break;
                    }
                }
            }
            else 
            {
                buff[j] =str[i];
                j++;
            }
            i++;
    }
    fwrite(buff, j, 1, stdout); 
    va_end(vl);
    return j;
}

//custom control functions

int ansiSTDColorFG(int fgColorCode)
{
    cprintf("\033[%dm", fgColorCode);
}

int ansiSTDColorFG_BG(int fgColorCode, int bgColorCode)
{
    cprintf("\033[%d;%dm", fgColorCode, bgColorCode);
}

int ansiXtermFG(int fgColorCode)
{
    cprintf("\033[38;5;%dm", fgColorCode);
}

int ansiXtermBG(int BgColorCode)
{
    cprintf("\033[48;5;%dm");
}

int ansiXtermFG_BG(int fgColorCode, int bgColorCode)
{
    cprintf("\033[38;5;%d;48;5;%dm", fgColorCode, bgColorCode);
}

int ansiRGB_FG(int r, int g, int b)
{
    cprintf("\033[38;2;%d;%d;%dm", r, g, b);
}

int ansiRGB_BG(int r, int g, int b)
{
    cprintf("\033[48;2;%d;%d;%dm", r, g, b);
}

int ansiRGB_FG_BG(int fR, int fG, int fB, int bR, int bG, int bB)
{
    cprintf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm", fR, fG, fB, bR, bG, bB);
}

int ansiReset()
{
    cprintf("\033[0m");
}
