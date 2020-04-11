#include <stdio.h>
#include <string.h>

int main() {
	int i = 0;
	i += 1;
	char c[2] = "t";
	char something[2];
	itoa(i, something);
	strcat(c, something);
	printf("%s", c);
}
