#include<vector>
using namespace std;
#ifndef BALANSIRAJUCESTABLO_H_INCLUDED
#define BALANSIRAJUCESTABLO_H_INCLUDED

template<typename Tip>
class Stablo{
    struct Cvor{
        Tip element;
        int nivoi; //broj nivoa ispod gledanog cvora
        int trenutniNivo;
        //int brojacNajduzih; //za svaki cvor èuva informaciju koliko ima elemenata na najveæim udaljenostima od njega samog prema dnu
        Cvor* ld;
        Cvor* dd;
        Cvor* rod;
        Cvor(int nivoi,int trenutniNivo,Tip element = Tip(),Cvor* ld = nullptr,Cvor* dd = nullptr,Cvor* rod = nullptr):
            nivoi(nivoi),trenutniNivo(trenutniNivo),element(element),ld(ld),dd(dd),rod(rod){}
    };

    Cvor* korijen;
    int broj_elemenata;

    Tip maximum(Cvor* korijen);
    Tip minimum(Cvor* korijen);

    Cvor* FindCvor(Tip x);

    void SmanjiNivoZaJedan(Cvor* c);
    void BrojNajduzih(Cvor* c,int k,int& br);
    Cvor* idiDoKraja(Cvor* c);

    void DajSveCvorove(Cvor* p,vector<Tip> &v);
    void ObrisiSveCvorove(Cvor* p);
    void Balansiraj(vector<Tip> &v, int s, int k);
    void ProvjeriBalansiranost(Cvor* prethodni);

    void Insert2(Tip x);
    void Obrisi2(Tip x);

    void InOrderRek(Cvor* korijen, void (f)(Tip&));
    void LevelOrderKorijen(Cvor* korijen,void (f)(Tip&));
    void LevelOrderKorijen2(Cvor* korijen);
public:
    Stablo():korijen(nullptr),broj_elemenata(0){}
    ~Stablo(){for(int i = 0; i < broj_elemenata;i++) Obrisi2(maxi()); korijen = nullptr;}

    Tip maxi() {maximum(korijen);}
    Tip mini() {minimum(korijen);}

    bool Find(Tip x);
    void Insert(Tip x);
    void Obrisi(Tip x);

    void InOrder(void (f)(Tip&)){ InOrderRek(korijen,f);}
    void LevelOrder(void (f)(Tip&)){ LevelOrderKorijen(korijen,f);}
    void LevelOrder2(){ LevelOrderKorijen2(korijen);}
};

#include "BalansirajuceStablo.cpp"
#endif // BALANSIRAJUCESTABLO_H_INCLUDED
