#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Prototype.h"

#define NB_ACTIVITIES 6
#define LG_ACTIVITY 20

#define NB_FOLDERS 15
#define LG_FOLDER 7

#define NB_FILES 24

void createTrainAndTestsSetFiles(void)
{
	char activities[NB_ACTIVITIES][LG_ACTIVITY] = { "downstairs", "jogging", "sitting", "standing", "upstairs", "walking" };
	char folderName[NB_FOLDERS][LG_FOLDER] = { "dws_1", "dws_11", "dws_2", "jog_16", "jog_9", "sit_13", "sit_5", "std_14", "std_6", "ups_12", "ups_3", "ups_4", "wlk_15", "wlk_7", "wlk_8" };
	FILE* pTrainset;
	FILE* pTestset;
	FILE* pFileData;

	fopen_s(&pTrainset, "trainSet.csv", "w");
	fopen_s(&pTestset, "testsSet.csv", "w");

	for (int iFolder = 0; iFolder < NB_FOLDERS; iFolder++)
	{
		for (int iFile = 0; iFile < NB_FILES; iFile++)
		{
			char filepath[35];
			sprintf_s(filepath, 35, "projRess\\%s\\sub_%d.csv", folderName[iFolder], iFile + 1);
			fopen_s(&pFileData, filepath, "r");

			// Skip first line
			char titre[175];
			fgets(titre, 175, pFileData);

			Row* pRow = malloc(sizeof(Row));
			Row row = *pRow;

			fscanf_s(pFileData, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &row.id, &row.attitude.roll, &row.attitude.pitch, &row.attitude.yaw,
				                                                                               &row.gravity.x, &row.gravity.y, &row.gravity.z,
				                                                                               &row.rotationRate.x, &row.rotationRate.y, &row.rotationRate.z,
				                                                                               &row.userAcceleration.x, &row.userAcceleration.y, &row.userAcceleration.z);

			for (int iRow = 0; iRow < 10000 && !feof(pFileData); iRow++)
			{
				double vector = sqrt(row.userAcceleration.x * row.userAcceleration.x * row.userAcceleration.y * row.userAcceleration.y * row.userAcceleration.z * row.userAcceleration.z);
				char sVector[50];
				sprintf_s(sVector, 50, "%lf,", vector);
	
				// TODO Sortir les initializations des variables en dehors des boucles
				// TODO Ecrire les vectors + l'activité dans le fichier
				/*
				if (iRow % 10 == 0)
				{
					fwrite(pTestset, sizeof(char), 50, &sVector);
				}
				else
				{
					fwrite(pTrainset, sizeof(char), 50, &sVector);
				}
				*/

				printf_s("%d, %d, %d\n", iFolder, iFile, iRow);

				fscanf_s(pFileData, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &row.id, &row.attitude.roll, &row.attitude.pitch, &row.attitude.yaw,
					&row.gravity.x, &row.gravity.y, &row.gravity.z,
					&row.rotationRate.x, &row.rotationRate.y, &row.rotationRate.z,
					&row.userAcceleration.x, &row.userAcceleration.y, &row.userAcceleration.z);
			}


			fclose(pFileData);
		}
	}

	fclose(pTrainset);
	fclose(pTestset);
}

int GetActivityIndex(int iFolder)
{
	if (iFolder >= 0 && iFolder <= 2)
		return 0;
	if (iFolder >= 3 && iFolder <= 4)
		return 1;
	if (iFolder >= 5 && iFolder <= 6)
		return 2;
	if (iFolder >= 7 && iFolder <= 8)
		return 3;
	if (iFolder >= 9 && iFolder <= 11)
		return 4;
	if (iFolder >= 12 && iFolder <= 14)
		return 5;

	printf_s("This activity (folder index: %d) does not exists.", iFolder);
	system("pause");
	exit(0);
}