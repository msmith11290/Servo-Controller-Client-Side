/*  Initialize keyboard by putting it into curses mode. i.e. don't echo the 
    keystroke and no waiting for enter to be hit before being able to read 
    each keystroke*/
#include <stdio.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO/*tcgetattr gets the parameters of the current terminal
#include "bluetooth-client.h"
//#include "i2c.h"
//#include "servo.h"
static struct termios oldt, newt;
extern int currentPosition;   // A good starting point ???
extern int stepsize;
extern unsigned char i2cCmdBuff[10];
    
    void init_keyboard(void)
    {
        /* STDIN_FILENO will tell tcgetattr that it should write the settings
           of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
                    /*now the settings will be copied*/
        newt = oldt;

            /*ICANON normally takes care that one line at a time will be processed
            that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON | ECHO);          

          /*Those new settings will be set to STDIN
            TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    }
void restore_keyboard(void)
{
    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
void process_keystrokes(void)
{
    int c;  
    while((c=getchar())!= 'q')  
    {
        if( c == 27)    // 27d = ESCAPE
        {
            c = getchar();
            if( c == '[')
                c = getchar();
        }
     //   putchar(c);                 
        printf("Keystroke = %c \n", c);
        switch( c )
        {
            case 'w' :
            case 'A' :  send_keystroke('A');
                        break;
            case 'z' :
            case 'B' : send_keystroke('B');
                       break;
            case 'a' :
            case 'C' : send_keystroke('C');
                       break;
            case 's' :
            case 'D' : send_keystroke('D');
                       break; 
        
        }
    }
    // If we quit, we need to inform the server
    send_keystroke('q');
    printf("Exited keyboard interpreter. No Bluetooth commands can be sent \n");
}