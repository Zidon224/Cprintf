/*
    Cprintf

    The basic implementation of the default printf function with few more features and small aditions.

    Features:
    # Same known features as default printf
    # Unicode charset support (UTF-8)
    # Ansi escape codes (RGB support, XTerm 255 color array, Standard colors will come up soon)

    Changelogs:

    - 16.11.2023: First publish
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
    char * ansiBlack = "\033[30m";
    char * ansiR     = "\033[31m";
    char * ansiG     = "\033[32m";
    char * ansiY     = "\033[33m";
    char * ansiB     = "\033[34m";
    char * ansiM     = "\033[35m";
    char * ansiC     = "\033[36m";
    char * ansiW     = "\033[37m";
    char * ansiDF    = "\033[39m";
    char * ansiRst   = "\033[0m";
  
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
