#include "user_sys.h"
#include "user.h"
#include "printf.h"

void loop(char* str)
{
	char buf[2] = {""};
	while (1){
		for (int i = 0; i < 5; i++){
			buf[0] = str[i];
			call_sys_write(buf);
			user_delay(1000000);
		}
	}
}


void user_process2() 
{
	for (int i = 0; i < 30; i++)
	{
		char str[10] = "[kill2]\n\r\0";
		call_sys_write(str);
		user_delay(100000);
	}
	call_sys_kill(2,1);
	call_sys_exit();
}
void user_process() 
{
	call_sys_write("User process\n\r");
	int pid = call_sys_fork();
	if (pid < 0) {
		call_sys_write("Error during fork\n\r");
		call_sys_exit();
		return;
	}
	if (pid == 0){
		user_process2();
		//loop("abcde");
	} else {
		call_sys_reprior(40,5);
		loop("12345");
	}
}