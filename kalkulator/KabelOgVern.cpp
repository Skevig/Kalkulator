#include "KabelOgVern.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#define SIZE_KV_STØRRELSER 10
#define RohCU 0.0175

using namespace std;

string forlm_Str_list[7] = { "A1","A2","B1","B2","C","D1","D2" };
float tverrsnitt[5]={1.5, 2.5, 4, 6, 10};
int kv_størrelser[SIZE_KV_STØRRELSER] = {10, 13, 16, 20, 25, 32, 40, 50, 63, 80};
float forlm_A1[5]={13.5, 18, 24, 31, 42};
float forlm_A2[5]={13, 17.5, 23, 29, 39};
float forlm_B1[5]={15.5, 21, 28, 36, 50};
float forlm_B2[5]={15, 20, 27, 34, 46};
float forlm_C[5]={17.5, 24, 32, 41, 57};
float forlm_D1[5]={18, 24, 30, 38, 50};
float forlm_D2[5]={19, 24, 33, 41, 54};
enum forlegningsmåter{A1=0, A2, B1, B2, C, D1, D2} forlm_num;
float p2;
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

bool first_search;
void get_motorVariables();
float calculate_iB(float p2); 
float søk_NEK(float iZ[], float tverrsnitt[]);
void get_iB();
void get_iZ();
void print_result();//Prints the results
float spenningsfall(float tverrsnitt);

void KabelOgVern() {
	printf("\n------KALKULATOR FOR KABEL OG VERN------\n NB: Bruk '.' og ikke ',' for desimaltall!!\n\n");
	get_motorVariables();
	get_iB();
	printf("Ib: %.2f A\n", iB);
	iN_mv = iB;
	// Get iB_kv size
	for (int i = 0; i < SIZE_KV_STØRRELSER; i++) {
		if (iB <= kv_størrelser[i]) { iN_kv = kv_størrelser[i]; break; }
	}
	first_search = true;
	get_iZ();
	printf("\nTverrsnitt: %.2f mm^2 Iz: %.2f A\n", tverrsnitt[valgt_tverrsnitt], iZ);
	print_result();
	printf("\nBeregner spenningsfall: \n");
	bool ok_spenningsfall = false;
	do {
		float deltaU = spenningsfall(tverrsnitt[valgt_tverrsnitt]);
		printf("Delta U: %.2f prosent av %i V\n", deltaU, U);
		if (deltaU >= 5)
		{
			valgt_tverrsnitt++;
			get_iZ();
			printf("\nNy Iz = %.2f A (%.1f mm^2)- pga. for stort spenningstap.\n\n", iZ, tverrsnitt[valgt_tverrsnitt]);
		}
		else
		{
			printf("Spenningsfall OK...\n");
			ok_spenningsfall = true;
		}
	} while (!ok_spenningsfall);
	print_result();
	printf("\nPress any key to continue...\n");
	_getch();
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

float søk_NEK(float iZ[], float tverrsnitt[])
{
	for (int i = 0; i < 5; i++)
	{
		if (first_search == true) 
		{
			printf("Sjekker %.2f mm^2 (%.2fA) i NEK-52B-4\n", tverrsnitt[i], iZ[i]);
		}
		if (iN_mv <= iZ[i])
		{
			if (first_search == true) {
				valgt_tverrsnitt = i;
			}
			first_search = false;
			return iZ[valgt_tverrsnitt];
		}
		else if(i==4)
		{
			printf("ERROR, FINNER IKKE iZ!!\n");
		}
	}
}

void get_motorVariables()
{
	printf("Skriv inn spenning (V): ");
	scanf_s("%i", &U);
	printf("\nSkriv inn virkningsgrad: ");
	scanf_s("%f", &virkningsgrad);
	printf("\nSkriv in CosPhi: ");
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

	printf("\nSkriv inn lengden til kabel (M):");
	scanf_s("%f", &lengde);
	printf("\n");
}

float calculate_iB(float effekt)
{
	float a = cosFi * virkningsgrad*U*sqrt(3);
	return effekt / a;
}

void get_iB()
{
	bool true_input = false;
	char har_iB;
	printf("Vet du IB? (y/n)");
	do {
		scanf_s(" %c", &har_iB);

		if (har_iB == 'y' || har_iB == 'Y')
		{
			printf("\nSkriv inn iB (A): ");
			scanf_s("%f", &iB);
			p2 = iB * cosFi*virkningsgrad*sqrt(3)*U;
			printf("\nP2 = %.2fW\n", p2);
			true_input = true;
		}
		else if (har_iB == 'n' || har_iB == 'N')
		{
			
			printf("\nSkriv inn p2 (W): ");
			scanf_s("%f", &p2);
			iB = calculate_iB(p2);
			true_input = true;
			printf("\n");
		}
	} while (!true_input);
}

float spenningsfall(float tverrsnitt)
{
	float delta = (RohCU*lengde*iB*sqrt(3)*cosFi*1.2) / tverrsnitt; // Delta u formel
	delta = (delta / U) * 100; // Delta u som prosent av total spenning
	return delta;
}

void print_result()
{
	printf("\n------------------------------------\n\n");
	printf("Ib: %.2fA\n", iB);
	printf("In(m.v): %.2fA\n", iN_mv);
	printf("In(k.v): %iA\n", iN_kv);
	printf("Iz: %.2fA (%.2f mm^2)\n", iZ, tverrsnitt[valgt_tverrsnitt]);
	printf("\n------------------------------------\n");
}