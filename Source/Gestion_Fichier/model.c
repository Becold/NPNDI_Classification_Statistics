#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"

#define NB_CLASSES 6
#define LG_ACTIVITY 20

#define NB_VECTOR 1000


void createModelSet(void)
{
	// char activities[NB_CLASSES][LG_ACTIVITY] = { "downstairs", "jogging", "sitting", "standing", "upstairs", "walking" };
	FILE* pTrainset;
	FILE* pModelset;
	int iClasse;
	int iVector;
	double vector;
	char line[100];
	char* word;
	double moyenne;
	char sMoyenne[10];

	// Init classes
	Classe classes[6];
	for (int i = 0; i < NB_CLASSES; i++)
	{
		classes[i].nbRow = 0;
		for (int j = 0; j < NB_VECTOR; j++)
		{
			classes[i].sumVectors[j] = 0;
		}
	}

	fopen_s(&pTrainset, "trainSet.csv", "r");
	fopen_s(&pModelset, "modelSet.csv", "w");

	if (pTrainset != NULL && pModelset != NULL)
	{
		// Read a line
		fgets(line, 1, pTrainset);

		while (!feof(pTrainset))
		{
			// Read begining of line (activity index)
			iClasse = strtok(line, ',');
			while (iClasse != NULL && iClasse < NB_CLASSES)
			{
				classes[iClasse].nbRow++;

				// Read vectors
				iVector = 0;
				word = strtok(line, ',');
				while (iVector < NB_VECTOR)
				{
					vector = atof(word);

					classes[iClasse].sumVectors[iVector] += vector;
					iVector++;
					word = strtok(line, ',');
				}

				iClasse++;
				iClasse = strtok(line, ',');
			}
		}

		iClasse = 0;
		while (iClasse < NB_CLASSES)
		{
			// Write activity index to file
			memset(sMoyenne, 0, sizeof(sMoyenne));
			snprintf(sMoyenne, sizeof(sMoyenne), "%d,", iClasse);
			fwrite(sMoyenne, 1, strlen(sMoyenne), pModelset);

			iVector = 0;
			while (iVector < NB_VECTOR)
			{
				moyenne = classes[iClasse].sumVectors[iVector] / classes[iClasse].nbRow;

				// Write vector to file
				memset(sMoyenne, 0, sizeof(sMoyenne));
				snprintf(sMoyenne, sizeof(sMoyenne), "%lf,", moyenne);
				fwrite(sMoyenne, 1, strlen(sMoyenne), pModelset);
				iVector++;
			}
			iClasse++;
		}

		fclose(pTrainset);
		fclose(pModelset);
	}
	else
	{
		printf_s("\nAn error occured while opening trainSet.csv and modelSet.csv. Their might be used by an other process.\n");
		system("pause");
		exit(0);
	}

}