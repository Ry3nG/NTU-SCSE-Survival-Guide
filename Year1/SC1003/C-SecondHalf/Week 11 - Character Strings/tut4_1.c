#include <stdio.h>
#include <string.h>
#define M1 "How are ya, sweetie?"
char M2[40] = "Beat the clock.";
char *M3 = "chat";
int main()
{
 char words[80],*p;
 printf(M1);
 puts(M1);
 puts(M2);
 puts(M2+1);
 fgets(words, 80, stdin); /* user inputs : win a toy. */
 if (p=strchr(words,'\n')) *p = '\0';
 puts(words);
 scanf("%s", words+6); /* user inputs : snoopy. */
 puts(words);
 words[3] = '\0';
 puts(words);
 while (*M3) puts(M3++);
 puts(--M3);
 puts(--M3);
 M3 = M1;
 puts(M3);
 return 0;
}