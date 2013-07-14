#ifndef _GPIO_H
#define _GPIO_H

#include <stdio.h>

#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"
#define IN "in\n"
#define OUT "out\n"
#define LOW "0\n"
#define HIGH "1\n"
#define GPIO_READ 0
#define GPIO_WRITE 1

#define	BLACK_MODEL		TRUE

#if BLACK_MODEL == TRUE

#define	GPIO_PORT		4
static unsigned int gpio0[] = 
{
	2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 22, 23, 26, 27, 30, 31
};
static unsigned int gpio1[] = 	
{
	0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15, 16, 17, 18, 19, 28, 29, 30, 31
};
static unsigned int gpio2[] = 
{
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 22, 23, 24, 25
};
static unsigned int gpio3[] = 
{
	14, 15, 16, 17, 18, 19, 20, 21
};

#else

#define	GPIO_PORT		0
static unsigned int *gpio0 = NULL;
static unsigned int *gpio1 = NULL;
static unsigned int *gpio2 = NULL;
static unsigned int *gpio3 = NULL;

#endif


int gpio_open(int, int, int);
int gpio_close(int, int);
int gpio_read(int, int);
int gpio_write(int, int, int);
int gpio_pin_exists(int, int);

#endif
