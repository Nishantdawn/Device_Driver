#include<stdio.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>
int main()
{

char c;
int rc;
    int fd = open("/dev/serial_led0", O_RDONLY);
    if (fd < 0) 
    {
	printf("not able to open file.\n");
	return 0;
    }
    printf("opened the fd = %d\n", fd);

 read (fd, &c, 1);
 printf("Status of LED is = %c\n", c);   
    
    if (close(fd) < 0) 
    {
	printf("not able to close file.\n");
	return 0;
    } 
    printf("closed the fd.\n");
}
