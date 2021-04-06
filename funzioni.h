#ifndef FUNZIONI_H_INCLUDED
#define FUNZIONI_H_INCLUDED
#include <string>

using namespace std;

struct Rubrica{
    int codice;
    string n_telefono,nome,cognome;
};

void crea(std::fstream &file, Rubrica contatto[],int DIM);
void stampa(std::fstream &file, Rubrica contatto[]);
void ricerca(std::fstream &file);
void modifica(std::fstream &file);

#endif // FUNZIONI_H_INCLUDED
