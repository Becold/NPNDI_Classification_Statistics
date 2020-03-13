#pragma once


void displayResultsForEachClasses(char realClasses[], char estimatedClasses[]);

void displayAccuracy(char realClasses[], char estimatedClasses[]);

void displayBarCharts(char realClasses[], char estimatedClasses[]);

void researchClasses(char realClasses[], char estimatedClasses[], int size, Classe** classes, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal);

void displayLegende();

void displayXaxis(double maxValue, double ratio);

void displayColumnsAndBars(Classe* classes, double ratio);

void displayBar(double value, double ratio);

void addOrUpdateClasses(Classe** classes, char real, char estimated, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal);

void updateClasse(Classe* pClasse, bool isCorrect);

void addClasse(char real, bool isCorrectEstimation, Classe** classes, Classe* pPrecClasse, int* nbClasses, int* maxTotal);

void updateMaxTotal(int* maxTotal, int total);

void updateSumTotalAndSumNbGoodEstimation(int* sumTotal, bool isCorrectEstimation, int* sumNbGoodEstimation);

Classe* createClasse(char name, bool isCorrectEstimation);

double calculatePourcentage(double numerator, double denominator);