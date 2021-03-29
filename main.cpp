#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#define DIM 5
using namespace std;

struct Rubrica{
    int codice;
    string n_telefono,nome,cognome;
}contatto[DIM];

void crea()
{
    ofstream file("rubrica.dat",ios::out|ios::binary);
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

void stampa()
{
    ifstream file("rubrica.dat",ios::in|ios::binary);
    if(!file)
        cout<<"ERRORE NELL'APERTURA DEL FILE";
    else
    {
        for(int i=0;i<DIM;i++)
            file.read((char *)&contatto[i],sizeof(contatto[i]));
        cout<<endl<<endl<<"\tRUBRICA:"<<endl;
        for(int i=0;i<DIM;i++)
            cout<<endl<<contatto[i].codice<<"\t"<<contatto[i].n_telefono<<"\t"<<contatto[i].cognome<<" "<<contatto[i].nome;
    }
    file.close();
}

void ricerca()
{
    ifstream file("rubrica.dat",ios::in|ios::binary);
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
        if(ID<=ins)
        {
            file.seekg(ID*sizeof(found));
            file.read((char*)&found,sizeof(found));
            cout<<found.codice<<": "<<found.n_telefono<<"\t"<<found.cognome<<" "<<found.nome;
        }
        else
            cout<<"ID non presente nel file.";
    }
    file.close();
}

void modifica()
{
    fstream file("rubrica.dat",ios::in|ios::out|ios::binary);
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
    file.close();
}

int main()
{
    int op;
    do
    {
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
            case 1:crea();
                   break;
            case 2:stampa();
                   break;
            case 3:ricerca();
                   break;
            case 4:modifica();
                   break;
        }
    }
    while(op!=5);
    return 0;
}
