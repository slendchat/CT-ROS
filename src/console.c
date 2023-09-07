// #include "printf.h"
// #include <string.h>

// char inner_buf[256] = {0};
// char con_buffer[1024] = {0};
// char input_buf[256] = {0};
// unsigned int cnt = 0;

// void console()
// {
//     int pos=0;
//     for (int i = 0; i < 256; i++)
//     {
//         if (input_buf[i]==' ')
//         {
//             pos = i;
//             break;
//         }
//     }
//     strncpy(inner_buf,input_buf,pos);

//     for (int i = 0; i < 256; i++)
//     {
//         input_buf[i]=0;
//     }
//     cnt = 0;
// }