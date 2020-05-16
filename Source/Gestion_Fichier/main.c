#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"
#include "C:\Lab\School\TND\Projet\Source\Project\Debug\prototype.h"

#define NB_DATA 45

int main(int argc, char *argv[])
{
	printf_s("\nCreation des 2 sets : TrainSet et TestsSet.");
	createTrainAndTestsSetFiles();

	printf_s("\nCreation du model set sur base du train set.");
	createModelSet();


	// Generate real and estimated classes
	int realClasses[NB_DATA];
	int estimatedClasses[NB_DATA];

	printf_s("\n\n\nEstimation des testsSet sur base des models.");
	testTestSet(realClasses, estimatedClasses);

	// Display results
	int size = 44;
	displayResultsForEachClasses(realClasses, estimatedClasses, size);

	displayAccuracy(realClasses, estimatedClasses, size);

	displayBarCharts(realClasses, estimatedClasses, size);

	printf_s("\n");
	return 0;
}