#ifndef LISTA3_HEADER
#define LISTA3_HEADER
#include "wezel.h"
#include "Blad.h"
#include <iostream>
// Daniel to gej
template <typename T>
class Lista{
	Wezel<T> *pierwszy_;
	Wezel<T>* ostatni_;
	int rozmiar_;
public:
	Lista():pierwszy_(nullptr),ostatni_(nullptr),rozmiar_(0){ ; }
	Lista(const T dane):rozmiar_(1){
		Wezel<T>* tmp = new Wezel < T > ;
		pierwszy_ = tmp;
		ostatni_ = tmp;
	}
	~Lista(){
		Wezel<T>* tmp = pierwszy_;
		while (tmp->nastepny_wezel_ != nullptr){
			tmp = tmp->nastepny_wezel_;
			delete tmp->poprzedni_wezel_;
		}
	}
	Wezel<T>* operator[](const int ktory){
		if (ktory > rozmiar_)
			throw PrzekroczenieZakresu();
		Wezel<T>* tmp = pierwszy_;
		for (int i = 0;i < rozmiar_; i++){
			tmp = tmp->nastepny_wezel_;
		}
		if (tmp->czyZablokowany() == true)
			throw ElementZablkowowany();
		return tmp;
	}
	void dodaj(const T dane, int gdzie){
		if (gdzie > (rozmiar_+1))
			throw PrzekroczenieZakresu();
		Wezel<T>* nowy=new Wezel<T>(dane);
		Wezel<T>* stary = (*this)[gdzie];
		nowy->poprzedni_wezel_ = stary->poprzedni_wezel_;
		nowy->nastepny_wezel_ = stary;
		stary->poprzedni_wezel_ = nowy;
		(stary->poprzedni_wezel_)->nastepny_wezel_ = nowy;

		rozmiar_++;
	}
	void usun(const int gdzie){
		if (gdzie > rozmiar_)
			throw PrzekroczenieZakresu();
		Wezel<T>* tmp = (*this)[gdzie];
		(tmp->poprzedni_wezel_)->nastepny_wezel_ = tmp->nastepny_wezel_;
		(tmp->nastepny_wezel_)->poprzedni_wezel_ = tmp->poprzedni_wezel_;
		delete tmp;
	}
	int rozmiar(){
		return rozmiar_;
	}
	void wypisz(){
		Wezel<T>* tmp = pierwszy_;
		while (tmp->nastepny_wezel_ != nullptr){
			cout << tmp->dane_;
		}
	}

};
#endif