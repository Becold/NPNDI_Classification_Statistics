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

#define LG_VECTOR 12

void createTrainAndTestsSetFiles(void)
{
	char activity[LG_ACTIVITY];
	char activities[NB_ACTIVITIES][LG_ACTIVITY] = { "downstairs", "jogging", "sitting", "standing", "upstairs", "walking" };
	char folderName[NB_FOLDERS][LG_FOLDER] = { "dws_1", "dws_11", "dws_2", "jog_16", "jog_9", "sit_13", "sit_5", "std_14", "std_6", "ups_12", "ups_3", "ups_4", "wlk_15", "wlk_7", "wlk_8" };
	FILE* pTrainset;
	FILE* pTestset;
	FILE* pFileData;
	char filepath[35];
	char titre[175];
	Row* pRow = malloc(sizeof(Row));
	Row row = *pRow;
	double vector;
	char sVector[LG_VECTOR];
	bool isTestsetFile;
	char backline = '\n';

	fopen_s(&pTrainset, "trainSet.csv", "w");
	fopen_s(&pTestset, "testsSet.csv", "w");

	if (pTrainset != NULL && pTestset != NULL)
	{
		for (int iFolder = 0; iFolder < NB_FOLDERS; iFolder++)
		{
			for (int iFile = 0; iFile < NB_FILES; iFile++)
			{
				sprintf_s(filepath, 35, "projRess\\%s\\sub_%d.csv", folderName[iFolder], iFile + 1);
				fopen_s(&pFileData, filepath, "r");

				if (pFileData != NULL)
				{
					// Skip first line (title)
					fgets(titre, 175, pFileData);

					// Write activity at the begining
					memset(activity, 0, sizeof(activity));
					snprintf(activity, sizeof(activity), "%s,", activities[GetActivityIndex(iFolder)]);
					isTestsetFile = iFile % 10 == 0;
					if (isTestsetFile)
					{
						fwrite(activity, 1, sizeof(activity), pTestset);
					}
					else
					{
						fwrite(activity, 1, sizeof(activity), pTrainset);
					}

					// Read a row
					fscanf_s(pFileData, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &row.id, &row.attitude.roll, &row.attitude.pitch, &row.attitude.yaw,
						&row.gravity.x, &row.gravity.y, &row.gravity.z,
						&row.rotationRate.x, &row.rotationRate.y, &row.rotationRate.z,
						&row.userAcceleration.x, &row.userAcceleration.y, &row.userAcceleration.z);

					// Writes computed vectors
					for (int iRow = 0; iRow < 1000 && !feof(pFileData); iRow++)
					{
						vector = sqrt(row.userAcceleration.x * row.userAcceleration.x * row.userAcceleration.y * row.userAcceleration.y * row.userAcceleration.z * row.userAcceleration.z);
						memset(sVector, 0, sizeof(sVector));
						snprintf(sVector, sizeof(sVector), "%lf,", vector);

						if (isTestsetFile)
						{
							fwrite(sVector, 1, sizeof(sVector), pTestset);
						}
						else
						{
							fwrite(sVector, 1, sizeof(sVector), pTrainset);
						}

						// Read a row
						fscanf_s(pFileData, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &row.id, &row.attitude.roll, &row.attitude.pitch, &row.attitude.yaw,
							&row.gravity.x, &row.gravity.y, &row.gravity.z,
							&row.rotationRate.x, &row.rotationRate.y, &row.rotationRate.z,
							&row.userAcceleration.x, &row.userAcceleration.y, &row.userAcceleration.z);
					}
					fclose(pFileData);

					if (isTestsetFile)
					{
						fwrite(&backline, 1, sizeof(backline), pTestset);
					}
					else
					{
						fwrite(&backline, 1, sizeof(backline), pTrainset);
					}
				}
				else
				{
					printf_s("An error occured while opening %s file. Their might be used by an other process.", filepath);
					system("pause");
					exit(0);
				}
			}
		}

		fclose(pTrainset);
		fclose(pTestset);
	}
	else
	{
		printf_s("An error occured while opening trainSet.csv and testsSet.csv. Their might be used by an other process.");
		system("pause");
		exit(0);
	}
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