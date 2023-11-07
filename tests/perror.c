#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	int i;

	i = 0;
	while (i < 134)
	{
		printf("%d Error: %s\n", i, strerror(i));
		i++;
	}
	return (0);
}
