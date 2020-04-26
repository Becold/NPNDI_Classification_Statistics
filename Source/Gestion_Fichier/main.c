#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"

int main(int argc, char *argv[])
{
	printf_s("Hello world.");

	createTrainAndTestsSetFiles();

	createModelSet();

	printf_s("\n");
	return 0;
}