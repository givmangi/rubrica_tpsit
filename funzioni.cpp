#include "funzioni.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctype.h>

using namespace std;

//! \class [FUNZIONI]

//! \relates FUNZIONI
/*! \fn crea(std::fstream &file,Rubrica contatto[],int DIM)
    \brief crea rubrica salvando dati di input in file e struct
    \param file stream del file
    \param contatto vettore di struct rubrica in cui salvare contenuti
    \param DIM numero contatti
*/

void crea(std::fstream &file,Rubrica contatto[],int DIM)
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        string temp;
        for(int i=0;i<DIM;i++)
        {
            cout<<endl<<"\tInserimento "<<(i+1)<<" contatto:"<<endl;
            contatto[i].codice=(i+1);

            cout<<"Numero di telefono:\t";
            fflush(stdin);
            getline(cin,temp);
            contatto[i].n_telefono=temp;

            cout<<"Cognome:\t";
            getline(cin,temp);
            contatto[i].cognome=temp;

            cout<<"Nome:\t";
            getline(cin,temp);
            contatto[i].nome=temp;

            file.write((char *)&contatto[i],sizeof(contatto[i]));
        }
    }
    file.close();
}

//! relates FUNZIONI
/*! \fn stampa(std::fstream &file, Rubrica contatto[])
    \brief stampa contenuto file
    \param file stream del file
    \param contatto vettore di struct rubrica in cui salvare contenuti
*/

void stampa(std::fstream &file, Rubrica contatto[])
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        int i=0;
        Rubrica appoggio;
        file.clear();
        file.seekg(0,ios::beg);
        while(file.read((char *)&appoggio,sizeof(appoggio)))
        {
            contatto[i]=appoggio;
            i++;
        }
        cout<<endl<<endl<<"\tRUBRICA:"<<endl;
        for(int j=0;j<i;j++)
            cout<<endl<<contatto[j].codice<<"\t"<<contatto[j].n_telefono<<"\t"<<contatto[j].cognome<<" "<<contatto[j].nome;
        file.close();
    }
}

//! relates FUNZIONI
/*! \fn ricerca(std::fstream &file)
    \brief ricerca contatto specifico e lo stampa
    \param file stream del file
*/

void ricerca(std::fstream &file)
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        Rubrica found;
        long pos,ID,ins=0;
        while(file.read((char *)&found,sizeof(found)))
            ins++;
        cout<<"Inserire ID da trovare: ";
        cin>>ID;
        file.clear();
        file.seekg(0,ios::beg);
        if(ID<=ins)
        {
            pos=(ID-1)*sizeof(found);
            file.seekg(pos,ios::beg);
            file.read((char*)&found,sizeof(found));
            cout<<found.codice<<": "<<found.n_telefono<<"\t"<<found.cognome<<" "<<found.nome;
        }
        else
            cout<<"ID non presente nel file.";
    }
    file.close();
}

//! relates FUNZIONI
/*! \fn modifica(std::fstream &file)
    \brief modifica un campo del file
    \param file stream del file
*/

void modifica(std::fstream &file)
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        Rubrica found,sost;
        string newValue;
        int op;
        long pos,ID,ins=0;
        while(file.read((char *)&found,sizeof(found)))
            ins++;
        file.clear();
        file.seekg(0,ios::beg);
        cout<<"Inserire ID del contatto da modificare: ";
        cin>>ID;
        if(ID<=ins)
        {
            pos=(ID-1)*sizeof(found);
            file.seekg(pos);
            file.read((char*)&found,sizeof(found));
            sost=found;
            cout<<endl<<found.codice<<": \t"<<found.n_telefono<<"\t"<<found.cognome<<" "<<found.nome;
            do
            {
                cout<<endl<<"\tInserire campo da sostituire:"<<endl;
                cout<<"1)Numero di telefono"<<endl;
                cout<<"2)Cognome"<<endl;
                cout<<"3)Nome"<<endl;
                cin>>op;
            }
            while(op<1||op>3);
            cout<<"Inserire nuovo valore:";
            cin>>newValue;
            switch(op)
            {
                case 1: sost.n_telefono=newValue;
                        break;
                case 2: sost.cognome=newValue;
                        break;
                case 3: sost.nome=newValue;
                        break;
            }
            file.seekp(pos,ios::beg);
            file.write((char *)&sost, sizeof(sost));
        }
        else
            cout<<"ID non presente nel file.";
    }
    file.close();
}
