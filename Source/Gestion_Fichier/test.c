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
		for (iVector = 0; iVector < NB_VECTOR; iVector++)
		{
			models[iModel].vectors[iVector] = 0;
		}
	}

	// Read Models file and write it into memory
	// => Less reading on disk harddrive
	fopen_s(&pModelsFile, "modelSet.csv", "r");
	iModel = 0;
	if (pModelsFile != NULL && !feof(pModelsFile))
	{
		fgets(line, 9500, pModelsFile);

		while (!feof(pModelsFile))
		{
			// Read begining of line (activity index)
			iModel = strtod(line, &pNext);

			// Read vectors
			while (iModel < NB_MODEL && (*pNext) != "" && (*pNext) != ',\n' && (*pNext) != '\n' && !feof(pModelsFile))
			{
				iVector = 0;
				double vectorModel = strtod(pNext + 1, &pNext);
				while (iVector < NB_VECTOR && pNext != NULL && (*pNext) != "" && (*pNext) != ',\n' && (*pNext) != '\n' && !feof(pModelsFile))
				{
					models[iModel].vectors[iVector] = vectorModel;
					vectorModel = strtod(pNext + 1, &pNext);
					iVector++;
				}

			}

			// Read next line
			fgets(line, 9500, pModelsFile);
		}
	}
	else
	{
		printf_s("\nAn error occured while opening modelSet.csv. Their might be used by an other process.\n");
		system("pause");
		exit(0);
	}

	fclose(pModelsFile);


	// Read TestSet et test it
	// and write results to realClasses and estimatedClasses arrays
	printf_s("\n-- Lecture du fichier testSet et estimation des activites.");
	fopen_s(&pTestSetFile, "testsSet.csv", "r");

	int iRow = 0;
	int iActivity = 0;
	while (iRow < 45 && pTestSetFile != NULL && !feof(pTestSetFile))
	{
		fgets(line, 9500, pTestSetFile);

		// Read begining of line of test (activity index) => write it to realClasses
		pNext = 0;
		int iActivity = strtod(line, &pNext);
		while (pTestSetFile != NULL && pNext != NULL && (*pNext) != "" && (*pNext) != ',\n' && (*pNext) != '\n' && !feof(pTestSetFile))
		{
			printf_s("\n---- Test de la ligne %d.", iRow);
			realClasses[iRow] = iActivity;

			// We compare tested vectors with model vectors
			double sumVectors[NB_MODEL];
			for (int iSumModel = 0; iSumModel < NB_MODEL; iSumModel++)
			{
				sumVectors[iSumModel] = 0.00;
			}

			// Sum 
			iVector = 0;
			while (iVector < NB_VECTOR && pTestSetFile != NULL && pNext != NULL && (*pNext) != "" && (*pNext) != ',\n' && (*pNext) != '\n' && !feof(pTestSetFile))
			{
				double vectorTest = strtod(pNext + 1, &pNext);

				for (int iModel = 0; iModel < NB_MODEL; iModel++)
				{
					double vectorModel = models[iModel].vectors[iVector];
					sumVectors[iModel] += pow(vectorTest - vectorModel, 2);
				}
				iVector++;
			}

			// Calculate distance for each model
			double oldDistance = DBL_MAX;
			int estimatedActivity = 0;
			for (int iModelTest = 0; iModelTest < NB_MODEL; iModelTest++)
			{
				double distance = sqrt(sumVectors[iModelTest]);

				// If we got closer of an other model => update the estimated activity
				if (oldDistance > distance)
				{
					estimatedActivity = iModelTest;
					oldDistance = distance;
				}
			}
			estimatedClasses[iRow] = estimatedActivity;

			// Display some output to the console
			char* textOk = estimatedClasses[iRow] == iActivity ? " -- Ok !" : "";
			printf_s("... Estimation: %d - Real: %d %s", estimatedActivity, iActivity, textOk);

			// Read next line
			fgets(line, 9500, pTestSetFile);
			iActivity = strtod(line, &pNext);
			iRow++;
		}
	}
	fclose(pTestSetFile);
}