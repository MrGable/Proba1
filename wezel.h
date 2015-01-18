#ifndef WEZEL_HEADER
#define WEZEL_HEADER
#include <iostream>

template <typename T>
class Wezel{

	bool zablokowane_; 

public:
	Wezel<T>* nastepny_wezel_;
	Wezel<T>* poprzedni_wezel_;
	bool wolny_;
	T dane_;
public:
	Wezel():nastepny_wezel_(nullptr),poprzedni_wezel_(nullptr),zablokowane_(false),wolny_(true){
		std::cout << "dupa";
	}
	Wezel(const T & dane) :nastepny_wezel_(nullptr), poprzedni_wezel_(nullptr),zablokowane_(false),wolny_(false),dane_(dane) {
		//dane_ = dane;
		std::cout << "cycki";
	}
	Wezel& operator=(const Wezel& wezel){
		dane_ = wezel.dane_;
		zablokowane_ = wezel.zablokowane_;
		wolny_ = wezel.wolny_;
		poprzedni_wezel_ = wezel.poprzedni_wezel_;
		nastepny_wezel_ = wezel.nastepny_wezel_;
	}
	Wezel* nastepny(){
		return nastepny_wezel_;
	}
	Wezel* poprzedni(){
		return poprzedni_wezel_;
	}
	T dane()const{
		return dane_;
	}
	T & dane(){
		return dane_;
	}
	void nadaj_wartosc(const T & dane){
		dane_ = dane;
	}
	void zablokuj(){
		zablokowane_ = true;
	}
	bool czyZablokowany()const{
		/*
		if (zablokowane_ == true)
			return true;
		else
			return false;
		*/
		return zablokowane_; // jednak prosciej, Biedrzy doesn't approve
	}

};
#endif