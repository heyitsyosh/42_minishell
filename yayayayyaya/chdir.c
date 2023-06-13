
#include <unistd.h>
#include <stdio.h>
// sample.c
#include <stdio.h>

int	main(int argc, char *argv[])
{
	 chdir(NULL);
	 printf("%s\n", getcwd(0, 0));
}