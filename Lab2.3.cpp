#include "klasy.h"
using namespace std;

#define Zad3

#ifdef Zad1


int main()
{

	const char* Rejstracja1 = "RKR 55544";
	const char* Rejstracja2 = "RKR 00025";
	const char* Rejstracja3 = "TWR 12345";
	const char* Rejstracja4 = "LPG 65432";

	SamochodOsobowy osobowka1(160,5,Rejstracja1), 
					osobowka2(130,4,Rejstracja2);

	SamochodCiezarowy ciezarowka1(80,5,TypTowaru::ciekly,Rejstracja3), 
					  ciezarowka2(90,7, TypTowaru::sypki,Rejstracja4);

	Pojazd* pojazdy[4] = { &osobowka1,&ciezarowka1,&osobowka2,&ciezarowka2 };

	for (int i = 0; i < 4; i++)
	{
		cout << "Cena za rejestracje pojazdu nr:" << i+1 << " wynosi: " << pojazdy[i]->opłataRejestrayjna(pojazdy[i]) << endl;

	}
}


#endif 


