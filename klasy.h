#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <cmath>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

enum class TypPaczki
{
	zwykla,
	priorytetowa,
	ekspresowa,
};

class Paczka
{
	double m_waga;
	double m_wymiary[3];
	char m_adres[400];
	TypPaczki m_typ;
	double nieUjemna(double wart)
	{
		return (wart > 0) ? wart : 0;
	}

public:
	void setWaga(double w)
	{
		m_waga = nieUjemna(w);
	}
	void setWymiary(double w, double sz, double gl)
	{
		m_wymiary[0] = nieUjemna(w);
		m_wymiary[1] = nieUjemna(sz);
		m_wymiary[2] = nieUjemna(gl);
	}
	void setAdres(const char* adr)
	{
		strncpy_s(m_adres, adr, 400);
	}
	void setTyp(TypPaczki typ)
	{
		m_typ = typ;
	}
};

enum class TypNagrody
{
	okolicznosciowa,
	projakoœciowa,
	okresowa,
};

class Osoba;

class Nagroda
{
	Osoba* m_beneficjent;
	Osoba* m_fundator;
	double m_wysokosc;
	TypNagrody m_typ;
	bool m_czyOdebrana;
public:
	void setBeneficient(Osoba* ben)
	{
		m_beneficjent = ben;
	}
	void setFundator(Osoba* fun)
	{
		m_fundator = fun;
	}
	void setWysokosc(double wys)
	{
		m_wysokosc = (wys > 0) ? wys : 0;
	}
	void setTyp(TypNagrody typ)
	{
		m_typ = typ;
	}
	void Odebrano()
	{
		m_czyOdebrana = true;
	}
};

enum class TypGry
{
	strategiczna,
	ekonomiczna,
	przygodowa,
};

class GraPlanszowa
{
protected:
	char m_tytul[400];
	int m_liczbaGraczy;
	int m_czasTrwania;
	TypGry m_typ;
	double m_ocenaGraczy;
	int m_liczbaOcen;
	double ograniczenie(double wart, double dolne, double gorne)
	{
		if (wart > gorne) return gorne;
		else if (wart < dolne) return dolne;
		else return wart;
	}
public:
	void setTytul(const char* tyt) { strncpy_s(m_tytul, tyt, 400); }
	void setLiczbaGraczy(int lg) { m_liczbaGraczy = (int)ograniczenie(lg, 1, 10); }
	void setCzasTrwania(int czas) { m_czasTrwania = (int)ograniczenie(czas, 10, 720); }
	void setTypGry(TypGry typ) { m_typ = typ; }
	void ocen(double nowaOcena)
	{
		nowaOcena = ograniczenie(nowaOcena, 0.0, 5.0);
		m_ocenaGraczy *= m_liczbaOcen;
		m_ocenaGraczy += nowaOcena;
		m_ocenaGraczy /= ++nowaOcena;
	}
	//Getery naly¿ zdefiniowaæ samodzielnie jeœli oka¿¹ sie niebêdne do realizacji zadania.
};



class Point
{
	int m_x, m_y;
	char m_symbol;
public:
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
	void setSymbol(char sym)
	{
		if (isalpha(sym))
			m_symbol = sym;
		else m_symbol = 0;
	}
	int getX() { return m_x; }
	int getY() { return m_y; }
};

/*double odleglosc(const Point& A, const Point& B)
{
	int dX = A.getX() - B.getX();
	int dY = A.getY() - b.getY();
	return sqrt(dX * dX + dY * dY);
}*/

enum class TypTowaru { ciekly, sypki, paczkowany };
enum class KatPJ { A, B, C, D };

class Pojazd 
{
protected:
	char m_numerRej[9];
	double m_predkosc;
	int m_liczbaPasazerow;
	double m_pojemnosc;
	TypTowaru m_typ;

	void setPredkosc(double i_pred) { m_predkosc = (i_pred > 160) ? i_pred : 160; }
	void setLiczbaPasazerow(int i_lp) { m_liczbaPasazerow = (i_lp > 1) ? i_lp : 1; }
	void setPojemnosc(double i_poj) { m_pojemnosc = (i_poj > 1000) ? i_poj : 1000; }

public:

	double getPredkosc() { return m_predkosc; }

	int getLiczbaPasazerow() { return m_liczbaPasazerow; }

	double getPojemnosc() { return m_pojemnosc; }

	void setNumerRej(const char* i_num) { strncpy_s(m_numerRej, i_num, 8); }
	const char* getNumerRej() { return m_numerRej; }

	void setTyp(TypTowaru i_typ) { m_typ = i_typ; }
	TypTowaru getTyp() { return m_typ; }


	virtual double op³ataRejestrayjna(Pojazd* pojazd) 
	{
		return 0;
	}

};


class SamochodOsobowy : public Pojazd
{
private:
	using Pojazd::setPredkosc;
public:

	SamochodOsobowy(double i_pred, int i_lp, const char* i_num)
	{
		setPredkosc(i_pred);
		setLiczbaPasazerow(i_lp);
		setNumerRej(i_num);
	}

	double op³ataRejestrayjna(Pojazd* pojazd) override
	{
		int predkosc = pojazd->getPredkosc();
		if (predkosc > 140)
		{
			int nadmiarowaPredkosc = predkosc - 140;
			double wynik = 500 + 50 * pojazd->getLiczbaPasazerow() + 5 * nadmiarowaPredkosc;
			return wynik;
		}
	}
};

class SamochodCiezarowy : public Pojazd
{
private:
	using Pojazd::setPredkosc;
public:

	SamochodCiezarowy(double i_pred, double i_poj, TypTowaru i_typ, const char* i_num)
	{
		if (i_pred>90)
		{
			i_pred = 90;
		}
		setPredkosc(i_pred);
		setPojemnosc(i_poj);
		setNumerRej(i_num);
		setTyp(i_typ);

	}

	double op³ataRejestrayjna(Pojazd* pojazd) override 
	{
		double wynik = 1000 + pojazd->getPojemnosc();
		if (pojazd->getTyp() == TypTowaru::sypki )
		{
			 wynik += 200;
		}
		else if (pojazd->getTyp() == TypTowaru::ciekly)
		{
			 wynik += 400;
		}
		else if (pojazd->getTyp() == TypTowaru::paczkowany)
		{
			 wynik += 100;
		}
		else
		{
			wynik = 0;
		}
		return wynik;
	}
};

class Kierowca
{
private:
	int m_staz;
	KatPJ m_uprawnienie;
public:
	void setUprawnienie(KatPJ i_upr) { m_uprawnienie = i_upr; }
	KatPJ getUprawnienie() { return m_uprawnienie; }
	int getStaz() { return m_staz; }
	void zwiekszStaz() { m_staz++; }
};

class Punkt
{
	double m_x = 0.0, m_y = 0.0;
public:
	void setXY(double x, double y)
	{
		m_x = x;
		m_y = y;
	}
	double getX() const { return m_x; }
	double getY() const { return m_y; }
	Punkt(double x, double y)
		:m_x(x), m_y(y)
	{}
};

class Kolo
{
	double m_promien = 1.0;
	Punkt m_srodek;
public:
	void setPromien(double r)
	{
		m_promien = (r > 0) ? r : 0;
	}
	void setSrodek(Punkt p)
	{
		m_srodek = p;
	}
	double getPromien() const { return m_promien; }
	Punkt getSrodek() const { return m_srodek; }
	Kolo(Punkt sr, double r)
		: m_srodek(sr), m_promien(r)
	{}
};

class Kwadrat
{
	Punkt m_lewy_dolny, m_prawy_gorny;
public:
	void setRogi(Punkt ld, Punkt pg)
	{
		m_lewy_dolny = ld;
		m_prawy_gorny = pg;
	}
	Punkt getLewyDolny() const { return m_lewy_dolny; }
	Punkt getPrawyGorny() const { return m_prawy_gorny; }
	Kwadrat(Punkt ld, Punkt pg)
		:m_lewy_dolny(ld), m_prawy_gorny(pg)
	{}
};

class Wektor
{
	double m_dx = 0.0, m_dy = 0.0;
public:
	void setDXY(double dx, double dy)
	{
		m_dx = dx;
		m_dy = dy;
	}
	double getDX() const { return m_dx; }
	double getDY() const { return m_dy; }
	double dlugosc() const { return sqrt(m_dx * m_dx + m_dy * m_dy); }
	Wektor(double dx, double dy)
		:m_dx(dx), m_dy(dy)
	{}
};

