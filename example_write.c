#include <stdio.h>
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	int port = -1;
	int error = 0;
	int try = 0;
	
	if(argc<2)
	{
		printf("Enter at least 1 argument\n");
		printf("with the port: %s 37\tgpio1[5]=>pin22 of P8\n", argv[0]);
		printf("with the GPIO number and index: %s 0 22\tgpio0[22]=>pin19 of P8\n", argv[0]);
		return -1;
	}
	
	if(argc<3)	port = gpio_pin_exists(-1, atoi(argv[1]));
	else port = gpio_pin_exists(atoi(argv[1]), atoi(argv[2]));
	
	if (gpio_open(-1, port, GPIO_WRITE) < 0) {
	    puts("Unable to open PIN file");
	    return -1;
	}
	
	while (!error && try<10) {
	    error = gpio_write(-1, port, 1);
	    sleep(1);
	    error = gpio_write(-1, port, 0);
	    sleep(1);
		try++;
	}
	
	gpio_write(-1, port, 0);
	gpio_close(-1, port);
	return 0;
}

