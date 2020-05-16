#pragma once
void createTrainAndTestsSetFiles(void);
Row ReadRow(pFileData);
int GetActivityIndex(int iFolder);

void createModelSet(void);

void testTestSet(char realClasses[], char estimatedClasses[]);
int GetEstimatedActivityIndex(double test);