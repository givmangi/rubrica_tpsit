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

int main()
{
    //! \brief main con menu a scelta

    Rubrica contatto[DIM];
    int op;
    do
    {
        fstream registro("rubrica.dat",ios::in|ios::out|ios::binary);
        do
        {
            cout<<endl<<endl<<"\tINSERIRE OPERAZIONE DA ESEGUIRE:"<<endl;
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
            case 1:crea(registro,contatto,DIM);
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
