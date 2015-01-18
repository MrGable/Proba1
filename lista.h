#ifndef LISTA_HEADER
#define LISTA_HEADER
#include <iostream>
#include "Blad.h"
#include "wezel.h"
#include <cmath>
#include <vector>

using namespace std;
const int REZERWACJA = 10;
template <typename T>
class Lista{
	Wezel<T> *pierwszy_;
	Wezel<T>* ostatni_;
	int rozmiar_;
	vector<Wezel<T>*> wezly_krytyczne_; //przechowuja adresy poczatkow nowych blokow (alokacji)

public:
	Lista() :rozmiar_(0), pierwszy_(nullptr), ostatni_(nullptr){
		Wezel<T>* tmp = alokuj();
		pierwszy_ = tmp;
		ostatni_ = tmp;
	}
	~Lista(){
		;
	}
	Wezel<T>* alokuj_po_raz_pierwszy(){
		vector<Wezel<T>> tablica;
		tablica.push_back(Wezel<T>); //pierwszy z REZERWACJA(10)
		for (int i = 1; i < REZERWACJA - 1; i++){
			tablica[i].poprzedni_wezel_ = &tablica[i - 1];
			tablica.push_back(Wezel<T>);
			tablica[i].nastepny_wezel_ = &tablica[i + 1];
		}
		tablica.push_back(Wezel<T>); // dziesiaty z REZERWACJA(10)
		tablica[0].nastepny_wezel_ = &tablica[1];
		tablica[REZERWACJA - 1].poprzedni_wezel_ = &tablica[REZERWACJA - 2];

		wezly_krytyczne_.push_back(&tablica[0]);

		return &tablica[0];
	}
	Wezel<T>* alokuj(){
		Wezel<T>* tablica = new Wezel<T>[10];
		for (int i = 1; i < (REZERWACJA - 1); i++){
			tablica[i].poprzedni_wezel_ = &tablica[i - 1];
			tablica[i].nastepny_wezel_ = &tablica[i + 1];
		}
		tablica[0].nastepny_wezel_ = &tablica[1];
		tablica[REZERWACJA].poprzedni_wezel_ = &tablica[REZERWACJA - 1];

		wezly_krytyczne_.push_back(&tablica[0]);

		return &tablica[0];
	}
	Wezel<T>* znajdz_wolny(){
		Wezel<T>* tmp = nullptr;
		for (int i = 0; i < wezly_krytyczne_.size(); i++){
			for (int j = 0; j < REZERWACJA; j++)
			{
				if ((wezly_krytyczne_[i])[j].wolny_ == true){
					tmp = &((wezly_krytyczne_[i])[j]);
					return tmp;
				}

			}
		}
		return tmp; //nullptr
	}
	void dodaj(const T dane){
		Wezel<T>* tmp = nullptr;
		if (znajdz_wolny() != nullptr){

			Wezel<T>* tmp = znajdz_wolny();
		}
		else{
			Wezel<T>* tmp = alokuj();
		}
		tmp->nadaj_wartosc(dane);
		tmp->poprzedni_wezel_ = ostatni_;
		ostatni_->nastepny_wezel_ = tmp;
		ostatni_ = tmp;

		rozmiar_++;
	}

	Wezel<T>& operator[](const int numer)const{
		if (numer >= rozmiar_)
			throw PrzekroczenieZakresu();
		Wezel<T>* tmp = pierwszy_;
		for (int i = 0; i < rozmiar_ - 1; i++)
			tmp = tmp->nastepny_wezel_;
		return *tmp;

	}
	void dodaj(const int gdzie, const T co){
		Wezel<T>* tmp = &(*this)[gdzie];
		Wezel<T>* tmp2 = new Wezel<T>(co);
		tmp2->nastepny_wezel_ = tmp;
		tmp2->poprzedni_wezel_ = tmp->poprzedni_wezel_;
		tmp->poprzedni_wezel_ = tmp2;
		rozmiar_++;
	}
	void wypisz()const{
		Wezel<T>* tmp = pierwszy_;
		for (int i = 0; i < rozmiar_; i++){
			cout << tmp->dane() << endl;
			tmp = tmp->nastepny_wezel_;
		}
	}

	int rozmiar()const;

	friend ostream& operator<<(ostream& str, Lista& lista);
	Lista<T>& operator+(const int position); //operator do wyswietlania innego elementu, nei sluzy do tworzenia nowych
};
#endif