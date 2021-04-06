#ifndef FUNZIONI_H_INCLUDED
#define FUNZIONI_H_INCLUDED

using namespace std;
struct Rubrica{
    int codice;
    string n_telefono,nome,cognome;
};

void crea(std::fstream &registro, Rubrica contatto[]);
void stampa();
void ricerca();
void modifica();

#endif // FUNZIONI_H_INCLUDED
