#include "lib/lib.h"
#include "lib/libsys.h"
#include "user/user_sys.h"
#include "user/user.h"
#include "printf.h"

void loop(char * str)
{
	char buf[2] = {""};
	while (1) {
		for (int i = 0; i < 5; i++) {
			buf[0] = str[i];
			libsys_write(buf);
			user_delay(1000000);
		}
	}
}

void umain()
{
	libsys_write("User process\n\r");
	int pid = libsys_fork();
	if (pid < 0) {
		libsys_write("Error during fork\n\r");
		libsys_exit();
		return;
	}
	if (pid == 0) {
		loop("abcde");
	} else {
		loop("12345");
	}
}
