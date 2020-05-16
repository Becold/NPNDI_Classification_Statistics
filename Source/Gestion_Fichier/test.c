#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "Structure.h"
#include "Prototype.h"

#define NB_MODEL 6
#define NB_VECTOR 1000

typedef struct Model Model;
struct Model
{
	double vectors[1000];
};

void testTestSet(char realClasses[], char estimatedClasses[])
{
	Model models[NB_MODEL];
	FILE* pModelsFile;
	FILE* pTestSetFile;
	char line[9500];
	int iModel = 0;
	int iVector = 0;
	char* pNext = 0;

	// Initialization
	for (iModel = 0; iModel < NB_MODEL; iModel++)
	{
		for (iVector = 0; iVector < 1000; iVector++)
		{
			models[iModel].vectors[iVector] = 0;
		}
	}

	// Lecture des models
	fopen_s(&pModelsFile, "modelSet.csv", "r");

	// Read Models file and write it into memory
	// Less write on 
	iModel = 0;
	while (pModelsFile != NULL && !feof(pModelsFile))
	{
		fgets(line, 9500, pModelsFile);

		while (!feof(pModelsFile))
		{
			// Read begining of line (activity index)
			iModel = strtod(line, &pNext);
			while (iModel < NB_MODEL && !feof(pModelsFile))
			{
				// Read vectors
				iVector = 0;
				while (iVector < NB_VECTOR && !feof(pModelsFile))
				{
					models[iModel].vectors[iVector] = strtod(pNext + 1, &pNext);
					iVector++;
				}

				// Read next line
				fgets(line, 9500, pModelsFile);
				iModel = strtod(line, &pNext);
			}
		}
	}

	if (iModel == 0)
	{
		printf_s("\nNo models has been read. Program exiting.");
		exit(1);
		return 1;
	}

	fclose(pModelsFile);


	// Read TestSet et test it
	// and write result to realClasses and estimatedClasses
	pNext = 0;
	printf_s("\n-- Lecture du fichier testSet et estimation des activites.");
	fopen_s(&pTestSetFile, "testsSet.csv", "r");

	int iRow = 0;
	int iActivity = 0;
	while (iRow < 45 && pTestSetFile != NULL && !feof(pTestSetFile))
	{
		fgets(line, 9500, pTestSetFile);

		// Read begining of line of test (activity index) => write it to realClasses
		if (pTestSetFile != NULL && !feof(pTestSetFile))
		{
			iActivity = strtod(line, &pNext);
			printf_s("\n---- Lecture de la ligne %d.", iRow);
			realClasses[iRow] = iActivity + '0';

			// We compare tested vectors with model vectors
			iVector = 0;
			double sumVectors[NB_MODEL];
			while (iVector < NB_VECTOR && pTestSetFile != NULL && !feof(pTestSetFile))
			{
				double vectorTest = strtod(pNext + 1, &pNext);
				for (int iModell = 0; iModell < NB_MODEL; iModell++)
				{
					sumVectors[iModell] = 0;
				}

				for (int iModel = 0; iModel < NB_MODEL && pTestSetFile != NULL && !feof(pTestSetFile); iModel++)
				{
					double vectorModel = models[iActivity].vectors[iVector];
					sumVectors[iModel] += pow(vectorTest - vectorModel, 2);

					iVector++;
					vectorTest = strtod(pNext + 1, &pNext);
				}
			}

			// Calculate distance
			double oldDistance = DBL_MAX;
			int iEstmatedActivityOfTest = 0;
			for (int iModell = 0; iModell < NB_MODEL; iModell++)
			{
				double distance = sqrt(sumVectors[iModell]);

				// If we got closer of an other model, it must be it
				if (distance < oldDistance)
				{
					iEstmatedActivityOfTest = iModell;
					oldDistance = distance;
				}
			}
			estimatedClasses[iRow] = iEstmatedActivityOfTest + '0';

			// Read next line
			fgets(line, 9500, pTestSetFile);
			iActivity = strtod(line, &pNext);
			iRow++;
		}

		fclose(pTestSetFile);
	}
}