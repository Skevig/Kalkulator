#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include "KabelOgVern.h"
#define PI  3.141592653589793238462643383279502884
#define INT_MAXVAL 2147483647
#define INT_MINVAL -2147483646

float division(float x, float y);
float multiply(float x, float y);
float pluss(float x, float y);
float minus(float x, float y);
float get_sum(float x, char tegn, float y);
void trekant_areal();
void matrix_calc();
void cosinus();
void equation();

int main(void) {

	KabelOgVern();
	bool true_input = true;
	int valg;
	do {
		printf("1. Matrix kalkulator \n2. Areal av trekant\n3. Cosinus av vinkel.\n4. Likning\n");
		scanf_s("%i", &valg);
		switch (valg)
		{
		case 1:
			matrix_calc();
			break;
		case 2:
			trekant_areal();
			break;
		case 3:
			cosinus();
			break;
		case 4:
			equation();
			break;
		default:
			break;
		}
	} while (!true_input);
}

void matrix_calc()
{
	float tall_1;
	float tall_2;
	float sum;
	char tegn;
	bool first_loop = true;

	printf("Dette er en matrise-kalkulator! Gyldeige opperatorer (+,-,*,/). Skriv '=' som opperator for � avslutte.\n\n");
	printf("Skriv inn tall 1\n");
	scanf_s("%f", &tall_1);
	do {
		printf("Skriv inn operator\n");
		scanf_s("%c", &tegn);
		if (tegn == '=') {
			printf("Sum: %f \n\n", sum);
			break;
		}
		printf("Skriv inn tall 2\n");
		scanf_s("%f", &tall_2);
		if (first_loop == true) {
			sum = get_sum(tall_1, tegn, tall_2);
			first_loop = false;
		}
		else
		{
			sum = get_sum(sum, tegn, tall_2);
		}
		printf("%.3f\n", sum);
	} while (true);
}

float get_sum(float x, char tegn, float y)
{
	float sum;

	switch (tegn) {
	case '+':
		sum = pluss(x, y);
		break;
	case '-':
		sum = minus(x, y);
		break;
	case '*':
		sum = multiply(x, y);
		break;
	case '/':
		sum = division(x, y);
		break;

	}
	return sum;
}




float division(float x, float y)
{
	float sum = x / y;
	return sum;
}
float multiply(float x, float y)
{
	float sum = x * y;
	return sum;
}

float pluss(float x, float y)
{
	float sum = x + y;
	return sum;
}

float minus(float x, float y)
{
	float sum = x - y;
	return sum;
}
void trekant_areal()
{
	float areal;
	float grunnlinje;
	float h�yde;

	printf("Skriv inn grunnlinje\n");
	scanf_s("%f", &grunnlinje);
	printf("Skriv inn h�yde\n");
	scanf_s("%f", &h�yde);
	areal = (grunnlinje*h�yde) / 2;
	printf("Areal av trekant er: %f", areal);
	printf("\n\n");
}

void cosinus()
{
	double vinkel;
	printf("Skriv inn vinkel\n");
	scanf_s("%lf", &vinkel);
	vinkel = vinkel * (PI / 180);
	double cosinus_vinkel = cos(vinkel);
	printf("COS av %lf i RADIAN: %lf \n", vinkel, cosinus_vinkel);
}

void equation()
{
	int x;
	int times_x;
	int right_side;
	int left_side;
	printf("How many times X");
	scanf_s("%i", &times_x);
	printf("Enter left side (including operators) \n");
	scanf_s("%i", &left_side);
	printf("LEFT SIDE = = %i\n", left_side);
	printf("Enter right side \n");
	scanf_s("%i", &right_side);
	for (int i = -100000; i <= INT_MAXVAL; i++)
	{
		printf("%i\n",i);
		if (times_x*i + left_side == right_side)
		{
			x = i;
			printf("%iX + %i, = %i\n", times_x, left_side, right_side);
			printf("X = %i \n", x);
			Sleep(10000);
			std::cin.ignore();
			break;
		}

	}
	
}