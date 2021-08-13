#include <stdio.h>
#include "keyboard.h" 
#include "bluetooth-client.h"
int main(void)
{     
    init_keyboard();
    init_bluetooth();
    process_keystrokes();
    printf("Left process_keystrokes\(\) \n");
    restore_keyboard();
    close_bluetooth();
    return 0;
}