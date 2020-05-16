#pragma once
void createTrainAndTestsSetFiles(void);
Row ReadRow(pFileData);
int GetActivityIndex(int iFolder);

void createModelSet(void);

void testTestSet(int realClasses[], int estimatedClasses[]);