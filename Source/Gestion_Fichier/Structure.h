#pragma once
typedef struct Attitude Attitude;
struct Attitude
{
	double roll;
	double pitch;
	double yaw;
};

typedef struct Vector Vector;
struct Vector
{
	double x;
	double y;
	double z;
};

typedef struct Row Row;
struct Row
{
	int id;
	Attitude attitude;
	Vector gravity;
	Vector rotationRate;
	Vector userAcceleration;
};

typedef struct Classe Classe;
struct Classe
{
	int nbRow;
	int sumVectors[1000];
};