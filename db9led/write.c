#include<stdio.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>
int main(int argc, char *argv[])
{

char c;
if(argc==2)
{
c=*argv[1];

    int fd = open("/dev/serial_led0", O_WRONLY);
    if (fd < 0) 
    {
	printf("not able to open file.\n");
	return 0;
    }
    printf("opened the fd = %d\n", fd);

 write (fd, &c, 1);
 printf("Data Written is = %c\n", c);   
    
    if (close(fd) < 0) 
    {
	printf("not able to close file.\n");
	return 0;
    } 
    printf("closed the fd.\n");
return 0;
}
else
printf("LED status value is not passed\n");
return 0;
}
