#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

enum class Studia { stacjonarne, niestacjonarne };
enum class Stopien { inzynierski, magisterski, doktorancki };
enum class StopienNaukowy { mgr, dr, dr_hab, prof };

class Katedra
{
protected:
	char m_nazwa[100] = "";
public:
	Katedra(const char* nazwa) { setNazwa(nazwa); }
	void setNazwa(const char* nazwa) { strncpy_s(m_nazwa, nazwa, 100); }
	const char* getNazwa() const { return m_nazwa; }
};

class Kierunek
{
protected:
	char m_nazwa[100] = "";
public:
	Kierunek(const char* nazwa) { setNazwa(nazwa); }
	void setNazwa(const char* nazwa) { strncpy_s(m_nazwa, nazwa, 100); }
	const char* getNazwa() const { return m_nazwa; }
};


class Osoba
{
protected:
	char m_imie[30] = "";
	char m_nazwisko[40] = "";
	int m_wiek = 18;
public:
	Osoba(const char* imie, const char* nazwisko, int wiek)
	{
		setImie(imie);
		setNazwisko(nazwisko);
		setWiek(wiek);
	}

	virtual int oblicz_pensje()
	{
		return 0;
	}

	void setImie(const char* imie) { strncpy_s(m_imie, imie, 30); }
	void setNazwisko(const char* nazwisko) { strncpy_s(m_nazwisko, nazwisko, 40); }
	void setWiek(int wiek) { m_wiek = (wiek > 0) ? wiek : 0; }

	const char* getImie() const { return m_imie; }
	const char* getNazwisko() const { return m_nazwisko; }
	int getWiek() const { return m_wiek; }
};



class Student :public Osoba
{
protected:
	Kierunek* m_kierunek = nullptr;
	int m_semestr = 1;
	Studia m_rodzajStudiow = Studia::stacjonarne;
	Stopien m_stopien = Stopien::inzynierski;
public:
	Student(Osoba& kandydat, Kierunek* kierunek, int semestr, Studia rodzaj, Stopien stopien)
		: Osoba(kandydat), m_kierunek(kierunek), m_rodzajStudiow(rodzaj), m_stopien(stopien)
	{
		setSemestr(semestr);
	}
	void setKierunek(Kierunek* kierunek) { m_kierunek = kierunek; }
	void setSemestr(int semestr) { m_semestr = (semestr > 0 && semestr < 8) ? semestr : 1; }
	void setRodzajStudiow(Studia rodzaj) { m_rodzajStudiow = rodzaj; }
	void setStopien(Stopien stopien) { m_stopien = stopien; }

	Kierunek* getKierunek() const { return m_kierunek; }
	int getSemestr() const { return m_semestr; }
	Studia getRodzajStudiow() const { return m_rodzajStudiow; }
	Stopien getStopien() const { return m_stopien; }
};

class Pracownik : public Osoba
{
protected:
	int m_stazPracy = 0;
	Katedra* m_katedra = nullptr;
	StopienNaukowy m_stopien = StopienNaukowy::mgr;
public:


	Pracownik(Osoba& osoba, Katedra* katedra, StopienNaukowy stopien)
		:Osoba(osoba), m_katedra(katedra), m_stopien(stopien)
	{}

	void zwiekszStaz() { m_stazPracy++; }
	void setKatedra(Katedra* katedra) { m_katedra = katedra; }
	void setStopienNaukowy(StopienNaukowy stopien)
	{
		m_stopien = stopien;
	}

	int getStaz() const { return m_stazPracy; }
	Katedra* getKatedra() const { return m_katedra; }
	StopienNaukowy getStopienNaukowy() const { return m_stopien; }

	virtual int oblicz_pensje()
	{
		int stawka = 0;
		if (StopienNaukowy::mgr == m_stopien)
		{
			stawka = 2000;
		}
		else if (StopienNaukowy::dr == m_stopien)
		{
			stawka = 3000;
		}
		else if (StopienNaukowy::dr_hab == m_stopien)
		{
			stawka = 4000;
		}
		else
		{
			stawka = 5000;
		}

		int pensja = 100 * m_stazPracy + stawka;
		return pensja;

	}
};



class PracownikNaukowy : public Pracownik
{
protected:
	int m_liczbaPublikacji = 0;
public:

	PracownikNaukowy(Pracownik& pracownik)
		:Pracownik(pracownik)
	{}
	void zwiekszLiczbePublikacji() { m_liczbaPublikacji++; }
	int getLiczbaPublikacji() const { return m_liczbaPublikacji; }

	int oblicz_pensje() override
	{
		int bonus = 50 * m_liczbaPublikacji;
		int calosc_pensji = Pracownik::oblicz_pensje() + bonus;
		return calosc_pensji;
	}
};

class PracownikDydaktyczny : public Pracownik
{
protected:
	int m_liczbaPrzedmiotow = 0;
public:

	PracownikDydaktyczny(Pracownik& pracownik, int lp) :
		Pracownik(pracownik)
	{
		set_liczba_przedmiotow(lp);
	}
	void set_liczba_przedmiotow(int lp) { m_liczbaPrzedmiotow = (lp > 0) ? lp : 0; }
	int get_liczba_przedmiotow() const { return m_liczbaPrzedmiotow; }

	int oblicz_pensje() override
	{
		int bonus = 100 * m_liczbaPrzedmiotow;
		int calosc_pensji = Pracownik::oblicz_pensje() + bonus;
		return calosc_pensji;
	}

};

class Doktorant : public Pracownik, public Student
{
public:
	Doktorant(Osoba& osoba, Katedra* katedra, Kierunek* kierunek, int semestr, Studia rodzaj) :
		Pracownik(osoba, katedra, StopienNaukowy::mgr),
		Student(osoba, kierunek, semestr, rodzaj, Stopien::doktorancki)
	{};

	int oblicz_pensje() override {
		int bonus;
		if (m_semestr > 1)
		{
			bonus = 200 * (m_semestr / 2);
		}
		else
		{
			bonus = 0;
		}
		int calos_pensji = 1500 + bonus;
		return calos_pensji;
	}
};

int koszty_uczelni(Osoba** const osoby, int iloscosob)
{
	int calkowity_koszt = 0;
	int koszt_studentow = 0;
	int koszt_pracownikow = 0;

	Osoba* osoba;

	for (size_t i = 0; i < iloscosob; i++)
	{
		osoba = osoby[i];
		if (dynamic_cast<Student*>(osoba))
		{
			koszt_studentow += 100;
		}
		else if (dynamic_cast<PracownikDydaktyczny*>(osoba))
		{
			koszt_pracownikow = koszt_pracownikow + osoba->oblicz_pensje();
		}
		else if (dynamic_cast<PracownikNaukowy*>(osoba))
		{
			koszt_pracownikow = koszt_pracownikow + osoba->oblicz_pensje();
		}
	}
	calkowity_koszt = koszt_studentow + koszt_pracownikow;
	return calkowity_koszt;
}


int main()
{
	Kierunek* informatyka_p = new Kierunek("Informatyka_przemys³owa");
	Kierunek* stosusunki_m = new Kierunek("Stosunki_Miedzynarodowe");

	Katedra* katedra_i = new Katedra("Katedra_informatyki");
	Katedra* katedra_e = new Katedra("Katedra_europejska");

	//Osoby
	Osoba osoba1 = Osoba("Mateusz", "Zygar", 20);
	Osoba osoba2 = Osoba("Mateusz", "Lewandowski", 30);
	Osoba osoba3 = Osoba("Marek", "Kowalski", 21);
	Osoba osoba4 = Osoba("Joanna", "Mickiewicz", 19);
	Osoba osoba5 = Osoba("Konrad", "Jaklik", 22);

	Student student1 = Student(osoba1, informatyka_p, 2, Studia::stacjonarne, Stopien::inzynierski);
	Student student2 = Student(osoba2, stosusunki_m, 3, Studia::niestacjonarne, Stopien::magisterski);
	Student student3 = Student(osoba3, informatyka_p, 4, Studia::stacjonarne, Stopien::inzynierski);
	Student student4 = Student(osoba4, informatyka_p, 1, Studia::stacjonarne, Stopien::inzynierski);
	Student student5 = Student(osoba5, stosusunki_m, 3, Studia::stacjonarne, Stopien::magisterski);

	//Pracownicy
	Osoba osoba6 = Osoba("Katarzyna", "Kowalczyk", 45);
	Osoba osoba7 = Osoba("Adam", "Zielinski", 50);
	Osoba osoba8 = Osoba("Agnieszka", "Czerwiñska", 40);
	Osoba osoba9 = Osoba("Zbigniew", "Baranski", 35);
	Osoba osoba10 = Osoba("Zofia", "Beben", 56);
	Osoba osoba11 = Osoba("£ukasz", "Kopec", 42);

	Pracownik pracownik1 = Pracownik(osoba6, katedra_i, StopienNaukowy::dr);
	PracownikNaukowy* pracownik_n1 = new PracownikNaukowy(pracownik1);
	Pracownik pracownik2 = Pracownik(osoba7, katedra_e, StopienNaukowy::prof);
	PracownikNaukowy* pracownik_n2 = new PracownikNaukowy(pracownik2);
	Pracownik pracownik3 = Pracownik(osoba8, katedra_i, StopienNaukowy::dr_hab);
	PracownikNaukowy* pracownik_n3 = new PracownikNaukowy(pracownik3);

	Pracownik pracownik4 = Pracownik(osoba9, katedra_e, StopienNaukowy::dr);
	PracownikDydaktyczny* pracownik_n4 = new PracownikDydaktyczny(pracownik4, 6);
	Pracownik pracownik5 = Pracownik(osoba10, katedra_i, StopienNaukowy::prof);
	PracownikDydaktyczny* pracownik_n5 = new PracownikDydaktyczny(pracownik5, 2);
	Pracownik pracownik6 = Pracownik(osoba11, katedra_e, StopienNaukowy::mgr);
	PracownikDydaktyczny* pracownik_n6 = new PracownikDydaktyczny(pracownik6, 15);

	const int rozmiar = 11;
	Osoba* tablica_osob[rozmiar] = { &student1,&student2,&student3, &student4,&student5,pracownik_n1,pracownik_n2,pracownik_n3,pracownik_n4,pracownik_n5,pracownik_n6 }; 
		cout << "Calkowity koszt uczelni wynosi: " << koszty_uczelni(tablica_osob, rozmiar) << "zl" << endl;
}
