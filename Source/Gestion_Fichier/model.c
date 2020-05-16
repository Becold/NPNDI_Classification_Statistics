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
	char line[9500];
	char* word;
	char* next_classe = ' ';
	char* next_vector = ' ';
	double moyenne;
	char sMoyenne[10];
	char backline = '\n';

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

	char* pNext = 0;

	printf_s("\n-- Calcul pour les modèles");
	if (pTrainset != NULL && pModelset != NULL && !feof(pTrainset))
	{
		// Read a line
		fgets(line, 9500, pTrainset);
		int iRow = 0;

		while (!feof(pTrainset))
		{
			// Read begining of line (activity index)
			iClasse = strtod(line, &pNext);
			while (iClasse < NB_CLASSES && !feof(pTrainset))
			{
				classes[iClasse].nbRow++;

				// Read vectors
				iVector = 0;
				vector = strtod(pNext + 1, &pNext);
				while (iVector < NB_VECTOR && pNext != NULL && !feof(pTrainset))
				{
					if (vector > 200)
					{
						printf_s("\n[Incoherrence de lecture][TrainSet][Row:%d][Vector:#%d] %f", iRow, iVector, vector);
					}

					classes[iClasse].sumVectors[iVector] += vector;

					vector = strtod(pNext + 1, &pNext);
					iVector++;
				}

				// Read next line
				fgets(line, 9500, pTrainset);
				iRow++;
				iClasse = strtod(line, &pNext);
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
				// Write vector to file
				double somme = classes[iClasse].sumVectors[iVector];
				moyenne = somme / classes[iClasse].nbRow;
				snprintf(sMoyenne, sizeof(sMoyenne), "%f", moyenne);
				fprintf_s(pModelset, "%s,", sMoyenne);
				iVector++;
			}

			// Write a backline to file to finish the line
			fwrite(&backline, 1, sizeof(backline), pModelset);
			printf_s("\n-- Fin d'ecriture du model %d", iClasse);
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