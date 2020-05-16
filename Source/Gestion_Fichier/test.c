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
	double vectors[1500];
};

void testTestSet(int realClasses[], int estimatedClasses[])
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
				double vectorModel = strtod(pNext + 1, &pNext);
				while (iVector < NB_VECTOR && pNext != NULL && !feof(pModelsFile))
				{
					if (vectorModel > 200)
					{
						printf_s("\n[Incoherence de lecture][Model][Model:%d][Vector:#%d] %f", iModel, iVector, vectorModel);
					}

					models[iModel].vectors[iVector] = vectorModel;
					iVector++;
					vectorModel = strtod(pNext + 1, &pNext);
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
		while (pTestSetFile != NULL && !feof(pTestSetFile))
		{
			iActivity = strtod(line, &pNext);
			printf_s("\n---- Test de la ligne %d.", iRow);
			realClasses[iRow] = iActivity;

			// We compare tested vectors with model vectors
			iVector = 0;
			double sumVectors[NB_MODEL];
			for (int iModell = 0; iModell < NB_MODEL; iModell++)
			{
				sumVectors[iModell] = 0;
			}

			while (iVector < NB_VECTOR && pTestSetFile != NULL && !feof(pTestSetFile))
			{
				double vectorTest = strtod(pNext + 1, &pNext);
				if (vectorTest > 200)
				{
					printf_s("\n---- [Incoherrence de lecture][TestsSet][Row:%d][Vector:#%d] %f\n", iRow, iVector, vectorTest);
				}

				for (int iModel = 0; iModel < NB_MODEL && pNext != NULL && pTestSetFile != NULL && !feof(pTestSetFile); iModel++)
				{
					double vectorModel = models[iModel].vectors[iVector];
					sumVectors[iModel] += pow(vectorTest - vectorModel, 2);
				}
				iVector++;
			}

			// Calculate distance for each model
			double oldDistance = DBL_MAX;
			int estimatedActivity = 0;
			int iModelTest = 0;
			while (iModelTest < NB_MODEL)
			{
				double distance = sqrt(sumVectors[iModelTest]);

				// If we got closer of an other model, it must be it
				if (oldDistance > distance)
				{
					estimatedActivity = iModelTest;
					oldDistance = distance;
				}
				iModelTest++;
			}
			estimatedClasses[iRow] = estimatedActivity;
			printf_s("... Estimation: %d", estimatedClasses[iRow]);

			// Read next line
			fgets(line, 9500, pTestSetFile);
			iActivity = strtod(line, &pNext);
			iRow++;
		}

		fclose(pTestSetFile);
	}
}