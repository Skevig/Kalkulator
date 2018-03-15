#include "KabelOgVern.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

string forlm_Str_list[7] = { "A1","A2","B1","B2","C","D1","D2" };
float tverrsnitt[5]={1.5, 2.5, 4, 6, 10};
int kv_størrelser[5] = {10, 13, 16, 20, 25 };
float forlm_A1[5]={13.5, 18, 24, 31, 42};
float forlm_A2[5]={13, 17.5, 23, 29, 39};
float forlm_B1[5]={15.5, 21, 28, 36, 50};
float forlm_B2[5]={15, 20, 27, 34, 46};
float forlm_C[5]={17.5, 24, 32, 41, 57};
float forlm_D1[5]={18, 24, 30, 38, 50};
float forlm_D2[5]={19, 24, 33, 41, 54};
enum forlegningsmåter{A1=0, A2, B1, B2, C, D1, D2} forlm_num;
float iB;
float iN_mv;
int iN_kv;
float iZ;
float cosFi;
float virkningsgrad;
int U;
string forlm_Str;
int valgt_forlm;

float lengde;
int valgt_tverrsnitt;

void get_motorVariables();
float calculate_iB(float p2); 
float søk_NEK(float x[]);
void get_iB();
void get_iZ();

void KabelOgVern() {

	get_motorVariables();
	get_iB();
	printf("Ib: %.2f A\n", iB);
	iN_mv = iB;
	printf("\nIn (m.v.) : %.2f A\n", iN_mv);
	// Get iB_kv size
	for (int i = 0; i < 5; i++) {
		if (iB <= kv_størrelser[i]) { iN_kv = kv_størrelser[i]; break; }
	}
	printf("In (k.v.): %2.i A\n", iN_kv);
	get_iZ();
	printf("\nTverrsnitt: %.2f mm^2 Iz: %.2f A\n", tverrsnitt[valgt_tverrsnitt], iZ);
	printf("------------------------------------\n\n");
	printf("Ib: %.2fA\n", iB);
	printf("In(m.v): %.2fA\n", iN_mv);
	printf("In(k.v): %iA\n", iN_kv);
	printf("Iz: %.2fA\n", iZ);
	printf("\nPress any key to continue...\n");
	_getch();
}
	
float calculate_iB(float effekt)
{
  float a= cosFi*virkningsgrad*U*sqrt(3);
  return effekt / a;
}

float søk_NEK(float iZ[], float tverrsnitt[])
{
	for (int i = 0; i < 5; i++)
	{
		printf("Sjekker %.2f mm^2 (%.2fA) i NEK-52B-4\n", tverrsnitt[i], iZ[i]);
		if (iN_mv <= iZ[i])
		{
			valgt_tverrsnitt= i;
			return iZ[i];
		}
		else if(i==4)
		{
			printf("ERROR, FINNER IKKE iZ!!\n");
		}
	}
}

void get_motorVariables()
{
	printf("\n------KALKULATOR FOR KABEL OG VERN------\n NB: Bruk '.' og ikke ',' for desimaltall!!\n\n");
	printf("Skriv inn spenning (U): ");
	scanf_s("%i", &U);
	printf("\nSkriv inn virkningsgrad: ");
	scanf_s("%f", &virkningsgrad);
	printf("\nSkriv in CosFi: ");
	scanf_s("%f", &cosFi);
	bool true_forlm = false;
	// Check if forlm is valid
	do {
		printf("\nSkriv inn forl.m. (Eks. A1, C): ");
		std::cin >> forlm_Str;
		for (int i = 0; i < 7; i++)
		{
			if (forlm_Str == forlm_Str_list[i])
			{
				true_forlm = true;
				valgt_forlm = i;
				break;
			}
		}
	} while (true_forlm == false);

	printf("\nSkriv inn lengden til kabel:");
	scanf_s("%f", &lengde);
	printf("\n");
}

void get_iB()
{
	bool true_input = false;
	char har_iB;
	printf("Vet du IB? (y/n)\n");
	do {
		scanf_s(" %c", &har_iB);

		if (har_iB == 'y' || har_iB == 'Y')
		{
			printf("Skriv inn iB: ");
			scanf_s("%f", &iB);
			true_input = true;
		}
		else if (har_iB == 'n' || har_iB == 'N')
		{
			float p2;
			printf("Skriv inn p2 (Effekt): \n");
			scanf_s("%f", &p2);
			iB = calculate_iB(p2);
			true_input = true;
		}
	} while (!true_input);
}

void get_iZ()
{
	switch (valgt_forlm)
	{
	case A1:
		iZ = søk_NEK(forlm_A1, tverrsnitt);
		break;
	case A2:
		iZ = søk_NEK(forlm_A2, tverrsnitt);
		break;
	case B1:
		iZ = søk_NEK(forlm_B1, tverrsnitt);
		break;
	case B2:
		iZ = søk_NEK(forlm_B2, tverrsnitt);
		break;
	case C:
		iZ = søk_NEK(forlm_C, tverrsnitt);
		break;
	case D1:
		iZ = søk_NEK(forlm_D1, tverrsnitt);
		break;
	case D2:
		iZ = søk_NEK(forlm_D2, tverrsnitt);
		break;
	default:
		printf("ERROR FINDING iZ, EXITING. . .\n");
	}
}