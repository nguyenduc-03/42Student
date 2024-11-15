//ft_split
/*  1. Split */
#include <stdlib.h>
#include <stdio.h>

int count_word(char const *s, char c)
{
    int count; 
    int in_word;
    int i;

    i = 0;
    in_word = 0;
    count = 0;
    
    while(s[i] == c ) i++;

    while(s[i])
    {
       if(s[i] != c )
       {
            if(in_word == 0){
        count++;}
        in_word = 1;
       }
       else in_word = 0;
       i++;
    }
    return count;
}

char **ft_split(char const *s, char c)
{
    char **array; //malloc bao nhieu word
    int start;
    int end;
    int count;
    int i;

    i = 0;
    start = 0;
    end = 0;
    count = 0;
    array = (char**)malloc((count_word(s, c) + 1) * sizeof(char*));
    if (!array)
        return NULL;
    while(s[end])
    {
        if(s[end] == c || s[end + 1] == '\0')
        {
            i = 0;

            int word_length;
            if (s[end] == c) 
                word_length = end - start;
            else
                word_length = end - start + 1;
            array[count] = (char*)malloc((word_length+ 1)*sizeof(char));
            if (!array[count])
                return NULL;
            while(start < end)
            {
                array[count][i]= s[start];
                i++;
                start++;
                printf("start: %c\n",s[start]);
            }
            if (s[end + 1] == '\0' && s[end] != c)
                array[count][i++] = s[end];
            array[count][i] = '\0';
            count++;
            start = end + 1;
        }
        end++;
    }
    array[count] = NULL;
    return array;
}





int main(){
    char set = ' ';
    char const *s1 = "1111 22222 3 3 31";

    char **strtrim = ft_split(s1,set);
    
    int i = 0;
    while(count_word(s1,set) != i){
        printf("Strtrim: %s\n", strtrim[i]);
        free(strtrim[i]);
        i++;
        
        printf("i: %d\n",i);
    }
    free(strtrim);
    printf("Words: %d\n", count_word(s1,set));
    
    return 0;
}
