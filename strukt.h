#ifndef strukt_H_INCLUDED
#define strukt_H_INCLUDED
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <chrono>
#include <list>

using namespace std;

struct duom{
    string vard; //studento vardas
    string pav; //studento pavarde
    int egz; // egzamino pazymys
    vector<int> ndrez;// namų darbų pazymiai
    double gp;
};
unsigned int zodziai(std::string const& str); //zodziu skaiciavimas
int pazymiogen();//random pazymio generavimas
double vidurkis(double visindrez, int m); //vidurkio radimas
double mediana(duom SK, int n); // medianos radimas
double rezultatas(double a, double b); //galutinio rezultato radimas
void ivedimas(vector<duom>& SK, int n); //duomenu ivedimas ranka
void isvedimas(vector<duom> SK, int n); //isvedimas i ekrana
void failogen(vector<duom>& SK, int tempvaik); //failo generavimas
void fskaitymas_list (list<duom>& sk, int* kieknd, int tempvaik); //duomenu nuskaitymas is failo naudojant list
void fskaitymas (vector<duom>& SK, int* kieknd, int tempvaik);//duomenu nuskaitymas is failo
void fisvedimas (vector<duom> SK, int kieknd); //isvedimas i faila
void fisvedimas_list (list<duom> SK, int kieknd); //isvedimas i faila naudojant list



#endif
