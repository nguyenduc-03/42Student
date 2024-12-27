#include <stdio.h>

int main()
{
    //printf("%d\n",ft_printf("Hi my lady : %q : %i\n %",130));
    printf("%d\n",printf("Hi my lady : %p%k : %i\n %",130,1));
    printf("%d\n",printf("Hi my lady : %p%k : %i\n %",130,1)); // if there's a error before the % at the end, it return normal value, other 
                                                                // return -1
 
    return 0;
}