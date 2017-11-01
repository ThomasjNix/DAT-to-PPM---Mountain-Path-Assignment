/*
 * Thomas Nix
 * ITCS 3112
 * Professor Subramanian
 * Completed 10/31/2017
 */

//Included dependancies
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class Pair {
    private:
        T first;
        T second;
    public:
        Pair();
        Pair(T firstVal, T secondVal);
        void setFirst(T newVal);
        void setSecond(T newVal);
        T getFirst();
        T getSecond();
        Pair<T> addUp(Pair<T>& thePair);
};


class Complex {
    private:
        float real, imaginary;
    public:
        Complex();
        Complex(float r, float i);
        float getReal();
        float getImaginary();
        float setReal(float inR);
        float setImaginary(float inI);
        Complex operator+(Complex newc);
};

int main(){
	Pair<int> intPair1(5, 10);
	Pair<int> intPair2(15, 1);
	Pair<float> floatPair1(1.5, 3.2);
	Pair<float> floatPair2(2.5, 4.6);
	Pair<string> stringPair1("A man walked ", "He Walked ");
	Pair<string> stringPair2("down the street", "forever.");
	Complex complex1(5.0, 2.2);
	Complex complex2(1.1, 6.3);
	
	cout << "Integer example:\n==========" << endl;
	Pair<int> intResult =	intPair1.addUp(intPair2);
	cout << "Pair1 first:\t" << intPair1.getFirst() <<
		"\nPair1 second:\t" << intPair1.getSecond() <<
		"\nPair2 first:\t" << intPair2.getFirst() << 
		"\nPair2 second:\t" << intPair2.getSecond() <<
		"\n\tResult first:\t" << intResult.getFirst() << 
		"\n\tResult second:\t" << intResult.getSecond() <<
		"\n" << endl;
	
	cout << "Float example:\n==========" << endl;
		Pair<float> floatResult =	floatPair1.addUp(floatPair2);
		cout << "Pair1 first:\t" << floatPair1.getFirst() <<
		"\nPair1 second:\t" << floatPair1.getSecond() <<
		"\nPair2 first:\t" << floatPair2.getFirst() << 
		"\nPair2 second:\t" << floatPair2.getSecond() <<
		"\n\tResult first:\t" << floatResult.getFirst() << 
		"\n\tResult second:\t" << floatResult.getSecond() <<
		"\n" << endl;

	cout << "Float example:\n==========" << endl;
		Pair<string> stringResult =	stringPair1.addUp(stringPair2);
		cout << "Pair1 first:\t" << stringPair1.getFirst() <<
		"\nPair1 second:\t" << stringPair1.getSecond() <<
		"\nPair2 first:\t" << stringPair2.getFirst() << 
		"\nPair2 second:\t" << stringPair2.getSecond() <<
		"\n\tResult first:\t" << stringResult.getFirst() << 
		"\n\tResult second:\t" << stringResult.getSecond() <<
		"\n" << endl;

	cout << "Complex example:\n==========" << endl;
		Complex complexResult =	complex1 + complex2;
		cout << "Complex1 real:\t" << complex1.getReal() <<
		"\nComplex1 imaginary:\t" << complex1.getImaginary() <<
		"\nComplex2 real:\t" << complex2.getReal() << 
		"\nComplex2 imaginary:\t" << complex2.getImaginary() <<
		"\n\tResult Complex real:\t" << complexResult.getReal() << 
		"\n\tResult Complex imaginary:\t" << complexResult.getImaginary() <<
		"\n" << endl;
	

	
	return 0;
}

// Pair contrsuctors
template <class T> 
Pair<T>::Pair(){
}

template <class T> 
Pair<T>::Pair(T firstVal, T secondVal){
	// Set instanced values
	first = firstVal;
	second = secondVal;
}


// Pair getters and setters
template <class T> 
void Pair<T>::setFirst(T newVal){
	first = newVal;
}

template <class T> 
void Pair<T>::setSecond(T newVal){
	second = newVal;
}

template <class T> 
T Pair<T>::getFirst(){
	return first;
}

template <class T> 
T Pair<T>::getSecond(){
	return second;
}

template <class T> 
Pair<T> Pair<T>::addUp(Pair<T>& thePair){
	Pair<T> p;
	p.setFirst(first + thePair.getFirst());
	p.setSecond(second + thePair.getSecond());
	return p;
}

// Complex getters and setters

Complex::Complex(){
	// Set default values
	real = 0.0;
	imaginary = 0.0;
}

Complex::Complex(float r, float i){
	// Set instanced values
	real = r;
	imaginary = i;
}

float Complex::getReal(){
	return real;
}
float Complex::getImaginary(){
	return imaginary;
}
float Complex::setReal(float inR){
	real = inR;
}
float Complex::setImaginary(float inI){
	imaginary = inI;
}

Complex Complex::operator+(Complex newc){
	Complex result;
	result.setReal(real + newc.getReal());
	result.setImaginary(imaginary + newc.getImaginary());
	return result;
}