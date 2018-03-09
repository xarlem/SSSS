#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>

struct Zadanie 
{
	int R, P, Q, nr; 
};


bool operator< (const Zadanie& pierwsze, const Zadanie& drugie)
{

	return pierwsze.nr < drugie.nr;
}

struct sortR
{
	bool operator() (const Zadanie pierwsze, const Zadanie ostatnie)
	{
		return (pierwsze.R < ostatnie.R);
	}
};

bool wczytaj(std::string nazwa_pliku, std::vector<Zadanie>& v);
void sortuj(std::vector<Zadanie>& v);
int Cmax(std::vector<Zadanie>& v);
void wyswietl(std::vector<Zadanie>& v);
void wyswietl_kolejnosc(std::vector<Zadanie>& v);
void przeglad_zupelny(std::vector<Zadanie>& v);

int main(int argc, char** argv)
{
	clock_t t1, t2, czas_programu;
	std::vector<Zadanie> v1;

	t1=clock();
	std::cout<<"Wczytywanie..\n";
	wczytaj("plik2.txt", v1);
	std::cout<<"Wyswietlanie..\n";
	wyswietl(v1);
	sortuj(v1);
	std::cout<<"Wyswietlanie..\n";
	wyswietl(v1);
	std::cout<<"Cmax = "<<Cmax(v1)<<"\n";
	t2=clock();

	przeglad_zupelny(v1);

	//std::cout<<t1<<" "<<t2<<" "<<CLOCKS_PER_SEC<<"\n";
	czas_programu=((t2-t1)/(double)CLOCKS_PER_SEC);
	//std::cout<<"Czas wykonywania programu: "<<czas_programu<<"\n";

	return 0;
}

bool wczytaj(std::string nazwa_pliku, std::vector<Zadanie>& v)
{
	std::fstream plik;
	int N=3;
	plik.open(nazwa_pliku.c_str());

	if(!plik.good())	
		return false;

	Zadanie zad;
	int n=1;
	//while(!plik.eof())
		for(int i=0; i<N; i++)
	{
		plik>>zad.R>>zad.P>>zad.Q;
		zad.nr=n++;
		v.push_back(zad);
		std::cout<<zad.R<<" "<<zad.P<<" "<<zad.Q<<"\n";
	}

	plik.close();
	return true;
}

void sortuj(std::vector<Zadanie>& v)
{
	std::sort(v.begin(), v.end(), sortR());
}

void wyswietl(std::vector<Zadanie>& v)
{
	for(std::vector<Zadanie>::iterator it=v.begin(); it!=v.end(); it++)
	{
		std::cout<<(*it).R<<" "<<(*it).P<<" "<<(*it).Q<<"\n";
	}
}

void wyswietl_kolejnosc(std::vector<Zadanie>& v)
{
	for(std::vector<Zadanie>::iterator it=v.begin(); it!=v.end(); it++)
	{
		std::cout<<(*it).nr<<" ";
	}
	std::cout<<"\n";
}

int Cmax(std::vector<Zadanie>& v)
{
	int t=0, c_max=0;
	for(std::vector<Zadanie>::iterator it=v.begin(); it!=v.end(); it++)
	{
		t = std::max((*it).R, t) + (*it).P;
		c_max = std::max(c_max, t+(*it).Q);
	}
	return c_max;
}

void przeglad_zupelny(std::vector<Zadanie>& v)
{	
	std::vector<int> min;
	std::sort(v.begin(), v.end());
	// for(std::vector<Zadanie>::iterator it=v.begin(); it!=v.end(); it++)
	// {
	// 	std::cout<<(*it).nr<<" ";
	// }
	// std::cout<<"\n";
	int i=0;
	do
	{
		for(std::vector<Zadanie>::iterator it=v.begin(); it!=v.end(); it++)
		{
			std::cout<<(*it).nr<<" ";
		}
		min.push_back(Cmax(v));
		std::cout<<"   "<<Cmax(v);
		std::cout<<"\n";
	}
	while (std::next_permutation(v.begin(), v.end()));//, &operator<));

	for(std::vector<int>::iterator it=min.begin(); it!=min.end(); it++)
	{
		std::cout<<(*it)<<" ";
	}

	std::sort(min.begin(), min.end());
	std::cout<<"Minimum = "<<min[0]<<"\n";
}












