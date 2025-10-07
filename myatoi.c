/* gcc -std=c11 -g -O -Wall -o myatoi myatoi.c */

/* Error 1: empty string or spaces only 
 * Error 2: no number, space or sign 
 * Error 3: more than one sign, in the wrong position 
 * Error 4: these cases: "+","-" */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isSign(char c) {
    if (c == '+' || c == '-') return true;
    return false;
}

int myatoi(char *s, int *n) {
    
    /* EMPTY STRING OR SPACES ONLY */
    int len = strlen(s);
    if (len == 0) return 1;
    int sp = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') sp++;
    }
    if (sp == len) return 1;

    /* RANGE ERROR */
    /* Digits Decimal Interval: [48,57] */
    for (int i = 0; i < len; i++) {
        if (!((s[i] >= 48 && s[i] <= 57) || isSign(s[i])|| s[i] == ' ')) return 2;
    }

    /* MORE THAN ONE SIGN */
    int p = 0;
    int m = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '+') p++;
        if (s[i] == '-') m++; 
    }
    if (p > 1 || m > 1) return 3;

    /* UNITARY LENGTH AND ONE SIGN */
    if (len == 1 && (isSign(s[0]))) return 4;

    /* CONVERSION. It must ignore any initial space 
     * and it must stop whenever it meets a space. */
    int idx = 0;
    while (s[idx] == ' ') idx++;
    int sign_pos = idx;

    int minus = false;
    if (isSign(s[idx])) {
        if (s[idx] == '-') minus = true;
        idx++; 
    }

    while (s[idx] != ' ' && idx < len) {
        if ((isSign(s[idx])) && idx != sign_pos) return 3; //WRONG SIGN POSITION
        *n = (*n * 10) + (s[idx] - '0'); 
        idx++;
    }
    if (minus == true) *n *= -1;

    return 0;
}

int main(int argc, char *argv[])
{
  for(int i=1;i<argc;i++) {
    int n, e;
    e = myatoi(argv[i],&n);
    if(e!=0) printf("Conversion Error: %d\n",e);
    else printf("Output: %d\n",n);
  }
  return 0;
} 
