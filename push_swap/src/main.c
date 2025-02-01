#include "push_swap.h"

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int	main(int argc, char** argv) // ./a 1 2 3 
{
	// still need to check for "3 2 1", using ft_split 
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

	// now the sorting and print the swap push according to wiki, block sort is fast
	selectionSort(array, argc-1);
	printArray(array,argc -1);
	return (0);	
}