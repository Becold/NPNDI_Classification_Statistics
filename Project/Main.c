#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "Source.h"

#define NB_DATA 160

int main(int argc, char *argv[])
{
	// Initialization
	Classe *classes = NULL;
	int nbClasses = 0;
	int sumNbGoodEstimation = 0;
	int sumTotal = 0;
	int maxTotal = -1;

	// Customs params
	char realClasses[NB_DATA] =      { '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4', '5', '2', '5', '3', '5', '3', '2', '4' };
	char estimatedClasses[NB_DATA] = { '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4', '5', '5', '1', '2', '1', '3', '2', '4' };

	researchClasses(realClasses, estimatedClasses, NB_DATA, &classes, &nbClasses, &sumNbGoodEstimation, &sumTotal, &maxTotal);

	displayResultsForEachClasses(classes);

	displayAccuracy(sumNbGoodEstimation, sumTotal);

	displayBarCharts(classes, maxTotal, true);

	printf_s("\n");
	return 0;
}

#pragma region METHODS

void researchClasses(char realClasses[], char estimatedClasses[], int size, Classe** classes, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal)
{
	for (int i = 0; i < size; i++)
	{
		char real = realClasses[i];
		char estimated = estimatedClasses[i];

		addOrUpdateClasses(classes, real, estimated, nbClasses, sumNbGoodEstimation, sumTotal, maxTotal);
	}
}

void displayResultsForEachClasses(Classe* classes)
{
	printf_s("%12s | %s | %s | %s \n", "classe", "bien classe", "total", "pourcentage");

	Classe* pClasse = classes;
	while (pClasse != NULL)
	{
		double pourcentage = calculatePourcentage(pClasse->nbGoodEstimation, pClasse->total) * 100;

		printf_s("%12c | %11d | %5d | %.2f%%\n", pClasse->name,
											     pClasse->nbGoodEstimation,
											     pClasse->total,
											     pourcentage);

		pClasse = pClasse->pNext;
	}
}

void displayAccuracy(int sumNbGoodEstimation, int sumTotal)
{
	double accuracy = calculatePourcentage((double)sumNbGoodEstimation, (double)sumTotal) * 100;
	printf_s("L'accuracy est de %.2f %% : %d bonnes estimations sur %d elements au total.\n", accuracy, sumNbGoodEstimation, sumTotal);
}

void displayBarCharts(Classe* classes, int maxTotal, bool isAbsoluteMode)
{
	double ratio = maxTotal < 50 ? 0.5 : (double)maxTotal / 100;
	maxTotal = maxTotal < 50 ? 50 : maxTotal;

	displayLegende();
	displayXaxis(maxTotal, ratio);
	displayColumnsAndBars(classes, ratio);
}

#pragma endregion METHODS

#pragma region PRIVATE 

void displayLegende()
{
	printf_s("Legende :\n");
	printf_s("T : total\n");
	printf_s("F : pas correctement classes\n");
	printf_s("P : nombre de biens classes\n");
}

void displayXaxis(double maxValue, double ratio)
{
	// Display labels
	printf_s("  ");
	for (int i = 1; i <= 101; i++)
	{
		if (i == 2 ||
			i == 4 ||
			i == 20 ||
			i == 40 ||
			i == 60 ||
			i == 80 ||
			i == 100)
		{
			printf_s("%2.0f", i * ratio);
			i++;
		}
		else
		{
			printf_s(" ");
		}
	}
	printf_s("\n");

	// Display X axis
	printf_s("___");
	for (int i = 1; i <= 101; i++)
	{
		if (i == 2 ||
			i == 4 ||
			i == 20 ||
			i == 40 ||
			i == 60 ||
			i == 80 ||
			i == 100 )
		{
			printf_s("|");
		}
		else
		{
			printf_s("_");
		}
	}
	printf_s("\n");
}

void displayColumnsAndBars(Classe* classes, double ratio)
{
	for (int i = 0; i < 3; i++)
	{
		printf_s("  |\n");
	}

	Classe* pClasse = classes;
	while (pClasse != NULL)
	{
		int nbMissEstimation = pClasse->total - pClasse->nbGoodEstimation;

		printf_s(" P|");
		displayBar(pClasse->nbGoodEstimation, ratio);
		printf_s("\n%cN|", pClasse->name);
		displayBar(nbMissEstimation, ratio);
		printf_s("\n T|");
		displayBar(pClasse->total, ratio);
		printf_s("\n  |\n");

		pClasse = pClasse->pNext;
	}
}

void displayBar(double value, double ratio)
{
	int longueur = round(value / ratio);

	for (int i = 0; i < longueur; i++)
	{
		printf_s("-");
	}
	printf_s("    %.2f", value);
}

void addOrUpdateClasses(Classe** classes, char real, char estimated, int* nbClasses, int* sumNbGoodEstimation, int* sumTotal, int* maxTotal)
{
	bool isCorrectEstimation = (real == estimated);

	// Update global variables
	updateSumTotalAndSumNbGoodEstimation(sumTotal, isCorrectEstimation, sumNbGoodEstimation);

	// Update if already exists
	Classe* pPrecClasse = NULL;
	Classe* pClasse = *classes;
	while (pClasse != NULL)
	{
		// Found => Update it.
		if ((*pClasse).name == real)
		{
			updateClasse(pClasse, isCorrectEstimation);
			updateMaxTotal(maxTotal, pClasse->total);
			return;
		}
		pPrecClasse = pClasse;
		pClasse = pClasse->pNext;
	}

	// Not found => Create a new Classe.
	addClasse(real, isCorrectEstimation, classes, pPrecClasse, nbClasses, maxTotal);
}

void updateMaxTotal(int* maxTotal, int total)
{
	if (*maxTotal < total)
		*maxTotal = total;
}

void updateSumTotalAndSumNbGoodEstimation(int* sumTotal, bool isCorrectEstimation, int* sumNbGoodEstimation)
{
	(*sumTotal)++;
	if (isCorrectEstimation)
	{
		(*sumNbGoodEstimation)++;
	}
}

void updateClasse(Classe* pClasse, bool isCorrectEstimation)
{
	pClasse->nbGoodEstimation += isCorrectEstimation ? 1 : 0;
	pClasse->total += 1;
}

void addClasse(char real, bool isCorrectEstimation, Classe** classes, Classe* pPrecClasse, int* nbClasses, int *maxTotal)
{
	Classe* pNewClasse = createClasse(real, isCorrectEstimation);

	if (*classes == NULL)
		*classes = pNewClasse;
	else
		pPrecClasse->pNext = pNewClasse;

	(*nbClasses)++;

	updateMaxTotal(maxTotal, pNewClasse->total);
}

Classe* createClasse(char name, bool isCorrectEstimation)
{
	Classe* pNewClasse = malloc(sizeof(Classe));
	if (pNewClasse == NULL) return NULL; // Out of memory.

	pNewClasse->name = name;
	pNewClasse->nbGoodEstimation = isCorrectEstimation ? 1 : 0;
	pNewClasse->total = 1;
	pNewClasse->pNext = NULL;
	return pNewClasse;
}

double calculatePourcentage(double numerator, double denominator)
{
	if (denominator == 0)
		return (double)NAN;

	return numerator / denominator;
}

int countDigit(double number)
{
	int count = 0;
	while (number > 0) {
		count++;
		number = number / 10;
	}
	return count;
}

#pragma endregion PRIVATE