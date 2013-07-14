#include "gpio.h"

int gpio_pin_exists(int ch, int index)
{
    int i, gpioSize = 0;
	unsigned int tmp = 0;
	unsigned int *gpio = NULL;
	
	if(ch == -1)
	{
		tmp = index % 32;
		ch = (index - tmp) / 32;

		if(ch >= 0 && ch < GPIO_PORT  &&  tmp >= 0)	return gpio_pin_exists(ch, tmp);
	}
	else if(ch < GPIO_PORT  && index >= 0)
	{
		switch(ch)
		{
			case 0:
				gpio = gpio0;
				gpioSize = sizeof(gpio0)/sizeof(*gpio0);
				break;
			case 1:
				gpio = gpio1;
				gpioSize = sizeof(gpio1)/sizeof(*gpio1);
				break;
			case 2:
				gpio = gpio2;
				gpioSize = sizeof(gpio2)/sizeof(*gpio2);
				break;
			case 3:
				gpio = gpio3;
				gpioSize = sizeof(gpio3)/sizeof(*gpio3);
				break;
			default:
				return -1;
				break;
		}
		//printf("ch %d index %d\n", ch, index);
		for(i = 0; i < gpioSize; i++)
		{
			if(index == gpio[i])		return (ch * 32 + index);
		}
	}
	
	return -1;
}       

int gpio_open(int ch, int index, int DDR)
{
	FILE *f;
	char file[35], ris[5];
	int port = gpio_pin_exists(ch, index);
	
	if(port == -1)	return -1;
	
	f = fopen(EXPORT, "w");
	if (fprintf(f, "%d\n", port) < 0)
	    return -2;
	fclose(f);

	sprintf(file, "/sys/class/gpio/gpio%d/direction", port);
	f = fopen(file, "w");

	if (!DDR)
	    sprintf(ris, IN);
	else
	    sprintf(ris, OUT);
	    
	if (fprintf(f, "%s", ris) < 0)
	    return -2;
	
	fclose(f);
	
	return 0;
}

int gpio_close(int ch, int index)
{
	FILE *f;
	int port = gpio_pin_exists(ch, index);
	
	if(port == -1)	return -1;
	
	f = fopen(UNEXPORT, "w");
	if(fprintf(f, "%d\n", port) < 0)
	    return -2;
	fclose(f);
	return 0;
}

int gpio_read(int ch, int index)
{
	FILE *f;
	char file[31];
	int i;
	int port = gpio_pin_exists(ch, index);
	
	if(port == -1)	return -1;
	
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "r");
	fscanf(f, "%d", &i);
	fclose(f);
	return i;
}

int gpio_write(int ch, int index, int value){
	FILE *f;
	char file[35],ris[5];
	int port = gpio_pin_exists(ch, index);
	
	if (port == -1)	return -1;
	
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "w");

	if (!value)
	    sprintf(ris, LOW);
	else
	    sprintf(ris, HIGH);
	
	if (fprintf(f, "%s", ris) < 0)
	    return -2;
	
	fclose(f);
	return 0;
}
