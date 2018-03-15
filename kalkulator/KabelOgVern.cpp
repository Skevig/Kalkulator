#include "KabelOgVern.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#define SQRT3 1.73205080757
using namespace std;
string forlm_list[7] = { "A1","A2","B1","B2","C","D1","D2" };
float tverrsnitt[5]={1.5, 2.5, 4, 6, 10};
int kv_størrelser[5] = {10, 13, 16, 20, 25 };
float forlm_A1[5]={13.5, 18, 24, 31, 42};
float forlm_A2[5]={13, 17.5, 23, 29, 39};
float forlm_B1[5]={15.5, 21, 28, 36, 50};
float forlm_B2[5]={15, 20, 27, 34, 46};
float forlm_C[5]={17.5, 24, 32, 41, 57};
float forlm_D1[5]={18, 24, 30, 38, 50};
float forlm_D2[5]={19, 24, 33, 41, 54};

float iB;
int iN_kv;
float cosFi;
float virkningsgrad;
int U;
string forlm;
float lengde;

float finn_iB(float p2); 

void KabelOgVern() {
	printf("Skriv inn spenning (U): ");
	scanf_s("%i", &U); 
	printf("\nSkriv inn virkningsgrad: ");
	scanf_s("%f", &virkningsgrad);
	printf("\nSkriv in CosFi: ");
	scanf_s("%f", &cosFi);
	printf("\nSkriv inn forleggningsmåte: ");
	bool true_forlm = false;
	do {
		std::cin >> forlm;
		for (int i = 0; i < 7; i++)
		{
			if (forlm == forlm_list[i])
			{
				true_forlm = true;
				break;
			}
		}
	} while (true_forlm == false);

	printf("\nSkriv inn lengde på kabel:");
	scanf_s("%s", &lengde);
	printf("\n");
	bool true_input = false;
	char har_iB;
	printf("Vet du IB? (y/n)\n");
	do {
		scanf_s("%c", &har_iB);

		if (har_iB == 'y' || har_iB == 'Y')
		{
			printf("Skriv inn iB: ");
			scanf_s("%f",& iB);
			true_input = true;
		}
		else if (har_iB == 'n' || har_iB == 'N')
		{
			float p2;
			printf("Skriv inn p2 (Effekt): \n");
			scanf_s("%f", &p2);
			iB = finn_iB(p2);
			printf("iB: %.2f A\n", iB);
			true_input = true;
		}
	} while (!true_input);
	printf("iN (m.v.) : %.2f A\n", iB);
	for (int i = 0; i < 5; i++) {
		if (iB <= kv_størrelser[i]) { iN_kv = kv_størrelser[i]; break; }
	}
	printf("iN (k.v.): %i A\n", iN_kv);
	
}
	
	float finn_iB(float effekt)
	{
	  int a= cosFi*virkningsgrad*U*sqrt(3);
	  return effekt / a;
	}
