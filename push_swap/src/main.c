#include "push_swap.h"

int	main(int argc, char** argv) // ./a 1 2 3 
{
	//check for integer and store in an int array = done
	int array[argc - 1];
	int i = 0;
	while(i <= argc - 2 )
	{
		if(!ft_is_integer(argv[i + 1])) // check for valid integer
		{
			write(1, "Error\n", 6);
			return (-1);
		}
		array[i] = ft_atoi(argv[i + 1]); // turn string to int
		printf("array[%d] = %d\n",i,array[i]); // jsut for checking
		i++;
	}

	// now the sorting 
	return (0);	
}