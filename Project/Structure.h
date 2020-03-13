typedef struct Classe Classe;
struct Classe
{
	char name;
	int nbGoodEstimation;
	int total;
	Classe* pNext;
};