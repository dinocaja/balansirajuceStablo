#include<iostream>
#include<cstdlib>
#include "BalansirajuceStablo.h"

using namespace std;

template <typename Tip>
void Ispisi(Tip &e){
    cout << e << " ";
}

int main(){
    Stablo<int> s;


    for(int i = 1; i < 60;i++){
        int t = rand()%500+1;
        s.Insert(t);
    }

/*
    for(int j = 1; j < 50;j++){
        s.Insert(j);
    }
*/

/*
    s.Insert(1);
    s.Insert(2);
    s.Insert(3);
    s.Insert(14);
    s.Insert(23);
    s.Insert(25);
    s.Insert(33);
    s.Insert(7);
    s.Insert(45);
    s.Insert(49);
    s.Insert(70);
    s.Insert(11);

    s.Obrisi(20); //Kod brisanja ispis po levelima u nekim sluèajevima nije dobar ali to samo ispis nije dobar, struktura je dobra
    s.Obrisi(50);   //to se lako može dokazati ako umjesto elementa ispisujemo trenutniNivo kod LevelOrdera
    s.Obrisi(25);
    s.Obrisi(1);
    s.Obrisi(7);
    s.Obrisi(33);
*/

    cout << endl << endl;
    s.LevelOrder(Ispisi);
    cout << endl << endl;
    s.InOrder(Ispisi);
    cout << endl << endl;
    s.LevelOrder2();
    return 0;
}
