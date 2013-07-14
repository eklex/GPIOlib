#include <stdio.h>
#include "gpio.h"

int main(int argc, char** argv)
{
	int port = -1;
	int ret, oldret, try=0;;
	
	if(argc<2)
	{
		printf("Enter at least 1 argument\n");
		printf("with the port: %s 37\tgpio1[5]=>pin22 of P8\n", argv[0]);
		printf("with the GPIO number and index: %s 0 22\tgpio0[22]=>pin19 of P8\n", argv[0]);
		return -1;
	}
	
	if(argc<3)	port = gpio_pin_exists(-1, atoi(argv[1]));
	else port = gpio_pin_exists(atoi(argv[1]), atoi(argv[2]));
	
	if(port == -1)
		return -1;

	if (gpio_open(-1, port, GPIO_READ) < 0) {
	    printf("Unable to open PIN file (%d)\n", port);
	    return -1;
	}

	while (try < 10) {
		oldret = ret;
		ret = gpio_read(-1, port);
		if(oldret!=ret)
		{
			printf("%d\n", ret);
			try = 0;
		}
		else try++;
		sleep(1);
	}

	gpio_close(-1, port);
	return 0;
}

