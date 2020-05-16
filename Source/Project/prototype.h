#pragma once


void displayResultsForEachClasses(int realClasses[], int estimatedClasses[]);

void displayAccuracy(int realClasses[], int estimatedClasses[]);

void displayBarCharts(int realClasses[], int estimatedClasses[]);

double computeRatio(int* maxTotal);

void researchClasses(int realClasses[], int estimatedClasses[], int size, Classe** classes, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal);

void displayLegende();

void displayXaxis(double maxValue, double ratio);

void displayColumnsAndBars(Classe* classes, double ratio);

void displayBar(double value, double ratio);

void addOrUpdateClasses(Classe** classes, int real, int estimated, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal);

void updateClasse(Classe* pClasse, bool isCorrect);

void addClasse(int real, bool isCorrectEstimation, Classe** classes, Classe* pPrecClasse, int* nbClasses, int* maxTotal);

void updateMaxTotal(int* maxTotal, int total);

void updateSumTotalAndSumNbGoodEstimation(int* sumTotal, bool isCorrectEstimation, int* sumNbGoodEstimation);

Classe* createClasse(int name, bool isCorrectEstimation);

double calculatePourcentage(double numerator, double denominator);