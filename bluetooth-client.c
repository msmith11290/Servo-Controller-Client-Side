/* Note you need to sudo apt-get install libbluetooth-dev to get <bluetooth/bluetooth.h> */
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>      // This is to set piscan
#include <sys/ioctl.h>          // This also is to set piscan
static int s;
int init_bluetooth(void)
{
    struct sockaddr_rc addr = { 0 };
    int status;
    char dest[18] = "E4:5F:01:1B:09:04";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    return status;
}
void send_keystroke( char key )
{
    int status;
    // send a message
        status = write(s, &key, 1);
    if( status < 0 ) perror("uh oh");
}
int close_bluetooth()
{
    close(s);
    return 0;
}

