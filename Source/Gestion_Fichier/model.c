#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"

#define NB_ACTIVITIES 6
#define LG_ACTIVITY 20

#define NB_VECTOR 1000

#define NB_CLASSES 6

void createModelSet(void)
{
	char activities[NB_ACTIVITIES][LG_ACTIVITY] = { "downstairs", "jogging", "sitting", "standing", "upstairs", "walking" };
	Classe classes[100];
	FILE* pTrainset;
	FILE* pModelset;
	int iClasse = 0;

	fopen_s(&pTrainset, "trainSet.csv", "r");
	fopen_s(&pModelset, "modelSet.csv", "w");

	if (pTrainset != NULL && pModelset != NULL)
	{
		// Lecture du fichier
		/*
		while ()
		{
			iClasse = GetActivityIndex(ligne);
			classes[iClasse].nbRow++;
			iVector = 0;
			while (iVector < NB_VECTOR)
			{
				classes[iClasse].sumVectors[iVector] += ligne[iVector];
				iVector++;
			}
		}
		*/

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