#include <stdio.h>

int main(){

int i;
for(i=0;i<256;i++)
	if(i='\t') printf("%d",i);
}