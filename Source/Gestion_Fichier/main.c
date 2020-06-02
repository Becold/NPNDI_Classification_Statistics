#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"
#include "C:\Lab\School\TND\Projet\Source\Project\Debug\prototype.h"

#define NB_ESTIMATED 45

int main(int argc, char *argv[])
{
	printf_s("\nCreation des 2 sets : TrainSet et TestsSet.");
	createTrainAndTestsSetFiles();

	printf_s("\nCreation du model set sur base du train set.");
	createModelSet();

	// Generate real and estimated classes
	int realClasses[NB_ESTIMATED];
	int estimatedClasses[NB_ESTIMATED];

	printf_s("\n\n\nEstimation des testsSet sur base des models.");
	testTestSet(realClasses, estimatedClasses);

	// Display results
	displayResultsForEachClasses(realClasses, estimatedClasses, NB_ESTIMATED);

	displayAccuracy(realClasses, estimatedClasses, NB_ESTIMATED);

	displayBarCharts(realClasses, estimatedClasses, NB_ESTIMATED);

	printf_s("\n");
	return 0;
}