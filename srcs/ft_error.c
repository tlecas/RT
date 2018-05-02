#include "rt.h"

void	ft_error(char *str, void *ptr1, void *ptr2)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free(ptr2);
	ft_putendl(str);
	exit(EXIT_FAILURE);
}
