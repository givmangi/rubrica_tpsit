#include "funzioni.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctype.h>
#define DIM 5

using namespace std;

    /*! \mainpage <CENTER> Gestione Rubrica </CENTER>
    * \author <B> Mangiacotti Giuseppe Pio </B>
    * \version <B> V1.1 </B>
    * \date <B> Consegna progetto:   29/03/2021 </B>
    * 
    * \section caratteristiche CARATTERISTICHE DEL PROGETTO
    *
    *  Il software permette di:
    * - Generare file rubrica con informazioni inserite da input
    * - Stampare a schermo la rubrica da file 
    * - Modificare campi del file rubrica
    */

void crea(std::fstream &file,Rubrica contatto[])
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


void stampa(std::fstream &file, Rubrica contatto[])
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        int i=0;
        Rubrica appoggio;
        while(file.read((char *)&appoggio,sizeof(appoggio)))
        {
            contatto[i]=appoggio;
            i++;
        }
        cout<<endl<<endl<<"\tRUBRICA:"<<endl;
        for(int i=0;i<DIM;i++)
            cout<<endl<<contatto[i].codice<<"\t"<<contatto[i].n_telefono<<"\t"<<contatto[i].cognome<<" "<<contatto[i].nome;
    }
    file.close();
}

void ricerca(std::fstream &file)
{
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        Rubrica found;
        long ID,ins=0;
        while(file.read((char *)&found,sizeof(found)))
            ins++;
        cout<<"Inserire ID da trovare: ";
        cin>>ID;
        file.clear();
        cout<<"ins: "<<ins;
        if(ID<=ins)
        {
            file.seekg(ID*sizeof(found));
            file.read((char*)&found,sizeof(found));
            cout<<found.codice<<": "<<found.n_telefono<<"\t"<<found.cognome<<" "<<found.nome;
        }
        else
            cout<<"ID non presente nel file.";
    }
}

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
        cout<<"Inserire ID del contatto da modificare: ";
        cin>>ID;
        if(ID<=ins)
        {
            pos=ID*sizeof(found);
            file.seekg(pos);
            file.read((char*)&found,sizeof(found));
            cout<<found.codice<<": "<<found.n_telefono<<"\t"<<found.cognome<<" "<<found.nome;
            do
            {
                cout<<"\tInserire campo da sostituire:"<<endl;
                cout<<"1)Numero di telefono"<<endl;
                cout<<"2)Cognome"<<endl;
                cout<<"3)Nome"<<endl;
                cin>>op;
            }
            while(op<1||op>3);
            sost=found;
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
            file.seekp(pos);
            file.write((char *)&sost, sizeof(sost));
        }
        else
            cout<<"ID non presente nel file.";
    }
}




int main()
{
    //! \brief main con menu a scelta
    fstream registro("rubrica.dat",ios::in|ios::out|ios::binary);
    Rubrica contatto[DIM];
    int op;
    do
    {
        registro.clear();
        do
        {
            cout<<endl<<"\tINSERIRE OPERAZIONE DA ESEGUIRE:"<<endl;
            cout<<"1)Inserimento rubrica"<<endl;
            cout<<"2)Stampa"<<endl;
            cout<<"3)Ricerca per ID"<<endl;
            cout<<"4)Modifica campo"<<endl;
            cout<<"5)Uscita"<<endl;
            cin>>op;
            system("cls");
        }
        while(op<1||op>5);
        switch(op)
        {
            case 1:crea(registro,contatto);
                   break;
            case 2:stampa(registro,contatto);
                   break;
            case 3:ricerca(registro);
                   break;
            case 4:modifica(registro);
                   break;
        }
    }
    while(op!=5);
    return 0;
}
