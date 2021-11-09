#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#ifndef BALANSIRAJUCESTABLO_CPP
#define BALANSIRAJUCESTABLO_CPP
#include "BalansirajuceStablo.h"

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::FindCvor(Tip x){
    Cvor* t = korijen;
    while(t != nullptr){
        if(t->element == x)
            return t;
        else{
            if(t->element > x)
                t = t->ld;
            else
                t = t->dd;
        }
    }
    return nullptr;
}

template<typename Tip>
void Stablo<Tip>::Obrisi2(Tip x){
    if(!Find(x))
        return;

    Cvor* obrisi = FindCvor(x);
    Cvor* sljedbenik;
    if(obrisi->dd != nullptr){

        sljedbenik = obrisi->dd;
        while(sljedbenik->ld != nullptr){
            sljedbenik = sljedbenik->ld;
        }


        Cvor* c = obrisi;
        Cvor* d = sljedbenik;

        int br(0);
        BrojNajduzih(c,idiDoKraja(d)->trenutniNivo,br);
        if(br > 1){
            sljedbenik->nivoi = obrisi->nivoi;
        }else{
            if(sljedbenik->nivoi + sljedbenik->trenutniNivo - obrisi->trenutniNivo == obrisi->nivoi){
                sljedbenik->nivoi = obrisi->nivoi-1;
            }else{
                sljedbenik->nivoi = obrisi->nivoi;
            }
        }


        Cvor* n = sljedbenik->rod;
        sljedbenik->trenutniNivo = obrisi->trenutniNivo;
        if(sljedbenik->rod == obrisi){
            if(obrisi != korijen){
                if(obrisi == obrisi->rod->ld){
                    obrisi->rod->ld = sljedbenik;
                }else{
                    obrisi->rod->dd = sljedbenik;
                }
            }
            else{
                korijen = sljedbenik;
            }
            if(obrisi->ld != nullptr){
                obrisi->ld->rod = sljedbenik;
            }
            sljedbenik->rod = obrisi->rod;
            sljedbenik->ld = obrisi->ld;
        }
        else{
                bool bilo(false);
                while(n != nullptr){
                    if(n->nivoi == n->ld->nivoi+1 || n->dd == nullptr){
                        if(n->dd == nullptr || n->nivoi != n->dd->nivoi+1){
                            bilo = true;
                            n->nivoi--;
                        }
                        if(!bilo){
                            n->nivoi--;
                        }
                    }
                    n = n->rod;

                }
                if(bilo){
                    while(n != nullptr && (obrisi->ld == nullptr || obrisi->nivoi != obrisi->ld->nivoi+1)){
                        n->nivoi--;
                        n = n->rod;
                    }
                }

            sljedbenik->rod->ld = sljedbenik->dd;
            if(sljedbenik->dd != nullptr){
                Cvor* c = sljedbenik->dd;
                SmanjiNivoZaJedan(c);
            }

            if(sljedbenik->dd != nullptr)
                sljedbenik->dd->rod = sljedbenik->rod;

            if(obrisi->ld != nullptr){
                obrisi->ld->rod = sljedbenik;
                sljedbenik->ld = obrisi->ld;
            }
            sljedbenik->dd = obrisi->dd;
            sljedbenik->rod = obrisi->rod;
            if(obrisi != korijen){
                if(obrisi == obrisi->rod->ld){
                    obrisi->rod->ld = sljedbenik;
                }else{
                    obrisi->rod->dd = sljedbenik;
                }
            }
            else{
                korijen = sljedbenik;
                sljedbenik->dd->rod = sljedbenik;
            }
        }
        delete obrisi;
        broj_elemenata--;
    }
    else {

     Cvor* c = obrisi;
     SmanjiNivoZaJedan(c);

     Cvor* prethodni = c;
     int prepoznavanje(0);
     while(c != nullptr){
        if(c->ld == prethodni){
            prepoznavanje = 1;

        }else if(c->dd == prethodni){
            prepoznavanje = 2;
        }
        if(c->ld == prethodni){

            if(c->dd != nullptr && c->dd->nivoi+1 == c->nivoi){
                break;
            }
            if((prethodni->nivoi+1 == c->nivoi || c->dd == nullptr) || (prepoznavanje == 1 && prethodni->nivoi+2 == c->nivoi)){
                c->nivoi--;
            }else{
                break;
            }
        }

        else if(c->dd == prethodni){

            if(c->ld != nullptr && c->ld->nivoi+1 == c->nivoi){
                break;
            }
            if((prethodni->nivoi+1 == c->nivoi || c->ld == nullptr)|| (prepoznavanje == 2 && prethodni->nivoi+2 == c->nivoi)){
                c->nivoi--;
            }
            else{
                break;
            }
        }
        prethodni = c;
        c = c->rod;
     }


     if(obrisi->ld != nullptr)
       obrisi->ld->rod = obrisi->rod;
    if(obrisi->dd != nullptr)
       obrisi->dd->rod = obrisi->rod;

     if(obrisi == korijen)
        korijen = obrisi->ld;
     else {
        if(obrisi->rod->ld == obrisi){
            obrisi->rod->ld = obrisi->ld;
        }
        else{
            obrisi->rod->dd = obrisi->dd;
        }
     }
    delete obrisi;
    broj_elemenata--;
  }
}

template<typename Tip>
bool Stablo<Tip>::Find(Tip x){
    Cvor* t = korijen;
    while(t != nullptr){
        if(t->element == x)
            return true;
        else{
            if(t->element > x)
                t = t->ld;
            else
                t = t->dd;
        }
    }
    return false;
}

template<typename Tip>
void Stablo<Tip>::Insert2(Tip x){
    Cvor* prethodni;
    if(broj_elemenata == 0){
        korijen = new Cvor(0,0,x);
        prethodni = korijen;
    }
    else{
        Cvor* t = korijen;
        prethodni = korijen;

        while(t != nullptr){
            prethodni = t;
            if(t->element == x)
                return;
            else{
                if(t->element > x)
                    t = t->ld;
                else
                    t = t->dd;
            }
        }
        Cvor* n;

        if(x > prethodni->element){
            prethodni->dd = new Cvor(0,prethodni->trenutniNivo+1,x,nullptr,nullptr,prethodni);
            n = prethodni;
            Cvor* c = prethodni->dd;
            while(n != nullptr){
                if(c->trenutniNivo - n->trenutniNivo > n->nivoi){
                    if(n == korijen){
                        if(n->dd != nullptr && n->dd == prethodni)
                            n->nivoi = n->dd->nivoi+1;
                        else if(n->ld != nullptr && n->ld == prethodni){
                            n->nivoi = n->ld->nivoi+1;
                        }
                    }else{
                        n->nivoi = c->trenutniNivo - n->trenutniNivo;
                    }
                }
                prethodni = n;
                n = n->rod;
            }
        }
        else{

            prethodni->ld = new Cvor(0,prethodni->trenutniNivo+1,x,nullptr,nullptr,prethodni);
            n = prethodni;
            Cvor* c = prethodni->ld;
            while(n != nullptr){
                if(c->trenutniNivo - n->trenutniNivo > n->nivoi){
                    if(n == korijen){
                        if(n->dd != nullptr && n->dd == prethodni)
                            n->nivoi = n->dd->nivoi+1;
                        else if(n->ld != nullptr && n->ld == prethodni){
                            n->nivoi = n->ld->nivoi+1;
                        }
                    }else{
                        n->nivoi = c->trenutniNivo - n->trenutniNivo;
                    }
                }
                prethodni = n;
                n = n->rod;
            }
        }
    }
    broj_elemenata++;
}

template<typename Tip>
void Stablo<Tip>::Insert(Tip x){
    Cvor* prethodni;
    if(broj_elemenata == 0){
        korijen = new Cvor(0,0,x);
        prethodni = korijen;
    }
    else{
        Cvor* t = korijen;
        prethodni = korijen;
        while(t != nullptr){
            prethodni = t;
            if(t->element == x)
                return;
            else{
                if(t->element > x)
                    t = t->ld;
                else
                    t = t->dd;
            }
        }
        Cvor* n;
        if(x > prethodni->element){
            prethodni->dd = new Cvor(0,prethodni->trenutniNivo+1,x,nullptr,nullptr,prethodni);
            n = prethodni;
            Cvor* c = prethodni->dd;
            Cvor* pr = prethodni;
            while(n != nullptr){  //dio pri insertu koji podešava nivoe elemenata ispod novokreiranog čvora
                if(c->trenutniNivo - n->trenutniNivo > n->nivoi){
                    if(n == korijen){
                        if(n->dd != nullptr && n->dd == pr)
                            n->nivoi = n->dd->nivoi+1;
                        else if(n->ld != nullptr && n->ld == pr){
                            n->nivoi = n->ld->nivoi+1;
                        }
                    }else{
                        n->nivoi = c->trenutniNivo - n->trenutniNivo;
                    }
                }
                pr = n;
                n = n->rod;
            }
        }
        else{
            prethodni->ld = new Cvor(0,prethodni->trenutniNivo+1,x,nullptr,nullptr,prethodni);
            n = prethodni;
            Cvor* c = prethodni->ld;
            Cvor* pr = prethodni;
            while(n != nullptr){
                if(c->trenutniNivo - n->trenutniNivo > n->nivoi){
                    if(n == korijen){
                        if(n->dd != nullptr && n->dd == pr)
                            n->nivoi = n->dd->nivoi+1;
                        else if(n->ld != nullptr && n->ld == pr){
                            n->nivoi = n->ld->nivoi+1;
                        }
                    }else{
                        n->nivoi = c->trenutniNivo - n->trenutniNivo;
                    }
                }
                pr = n;
                n = n->rod;
            }
        }
    }
    broj_elemenata++;


    ProvjeriBalansiranost(prethodni);

}

template<typename Tip>
void Stablo<Tip>::InOrderRek(Cvor* korijen,void(f)(Tip&)){
    if(korijen->ld != nullptr)
        InOrderRek(korijen->ld,f);
    f(korijen->element);
    if(korijen->dd != nullptr)
        InOrderRek(korijen->dd,f);
}

template<typename Tip>
 void Stablo<Tip>::LevelOrderKorijen2(Cvor* korijen){
     if(korijen == nullptr)
        return;
    queue<Cvor*> q;
    q.push(korijen);
    int prethodniNivo = 0;
    while(!q.empty()){
        if(q.front()->trenutniNivo != prethodniNivo)
            cout << endl;
        prethodniNivo = q.front()->trenutniNivo;
        cout << (q.front()->nivoi) << " ";
        if(q.front()->ld != nullptr)
            q.push(q.front()->ld);
        if(q.front()->dd != nullptr)
            q.push(q.front()->dd);
        q.pop();
    }
    cout << endl;
 }

template<typename Tip>
 void Stablo<Tip>::LevelOrderKorijen(Cvor* korijen,void (f)(Tip&)){
     if(korijen == nullptr)
        return;
    queue<Cvor*> q;
    q.push(korijen);
    int prethodniNivo = 0;
    while(!q.empty()){
        if(q.front()->trenutniNivo != prethodniNivo)
            cout << endl;
        prethodniNivo = q.front()->trenutniNivo;
        f(q.front()->element);
        if(q.front()->ld != nullptr)
            q.push(q.front()->ld);
        if(q.front()->dd != nullptr)
            q.push(q.front()->dd);
        q.pop();
    }
 }

template<typename Tip>
Tip Stablo<Tip>::maximum(Cvor* korijen){
    Cvor* trenutni = korijen;
    while(trenutni->dd != nullptr){
        trenutni = trenutni->dd;
    }
    return trenutni->element;
}

template<typename Tip>
Tip Stablo<Tip>::minimum(Cvor* korijen){
    Cvor* trenutni = korijen;
    while(trenutni->ld != nullptr){
        trenutni = trenutni->ld;
    }
    return trenutni->element;
}

template<typename Tip>
void Stablo<Tip>::Obrisi(Tip x){
    if(!Find(x))
        return;

    Cvor* obrisi = FindCvor(x);
    Cvor* sljedbenik;

    if(obrisi->dd != nullptr){
        sljedbenik = obrisi->dd;
        while(sljedbenik->ld != nullptr){
            sljedbenik = sljedbenik->ld;
        }


        Cvor* c = obrisi;
        Cvor* d = sljedbenik;
        Cvor* g = sljedbenik->rod; //cvor potreban za balansiranju na kraju funkcije

        int br(0);
        //ovdje vraćamo broj elemenata na istoj visini kao što ima elemenat koji se nalazi na samom dnu(u desno) u odnosu na cvor koji ćemo obrisat
        //da bismo znali da li da mijenjamo broj nivoa(atribut nivoi) ili ne
        BrojNajduzih(c,idiDoKraja(d)->trenutniNivo,br);
        if(br > 1){
            sljedbenik->nivoi = obrisi->nivoi;
        }else{
            if(sljedbenik->nivoi + sljedbenik->trenutniNivo - obrisi->trenutniNivo == obrisi->nivoi){
                sljedbenik->nivoi = obrisi->nivoi-1;
            }else{
                sljedbenik->nivoi = obrisi->nivoi;
            }
        }


        Cvor* n = sljedbenik->rod;
        sljedbenik->trenutniNivo = obrisi->trenutniNivo;

        if(sljedbenik->rod == obrisi){
            if(obrisi != korijen){
                if(obrisi == obrisi->rod->ld){
                    obrisi->rod->ld = sljedbenik;
                }else{
                    obrisi->rod->dd = sljedbenik;
                }
            }
            else{
                korijen = sljedbenik;
            }
            if(obrisi->ld != nullptr){
                obrisi->ld->rod = sljedbenik;
            }
            sljedbenik->rod = obrisi->rod;
            sljedbenik->ld = obrisi->ld;
        }
        else{

            //ovdje podešavamo nivoe ostalih cvorova ako je to potrebno
            bool bilo(false);
            while(n != obrisi){
                if(n->nivoi == n->ld->nivoi+1 || n->dd == nullptr){
                    if(n->dd == nullptr || n->nivoi != n->dd->nivoi+1){
                        bilo = true;
                        n->nivoi--;
                    }
                    if(!bilo){
                        n->nivoi--;
                    }
                }
                n = n->rod;
            }
            if(bilo){
                while(n != nullptr && (obrisi->ld == nullptr || obrisi->nivoi != obrisi->ld->nivoi+1)){
                    n->nivoi--;
                    n = n->rod;
                }
            }

            sljedbenik->rod->ld = sljedbenik->dd;

            if(sljedbenik->dd != nullptr){
                Cvor* c = sljedbenik->dd;
                SmanjiNivoZaJedan(c);
            }

            if(sljedbenik->dd != nullptr)
                sljedbenik->dd->rod = sljedbenik->rod;


            if(obrisi->ld != nullptr){
                obrisi->ld->rod = sljedbenik;
                sljedbenik->ld = obrisi->ld;
            }
            sljedbenik->dd = obrisi->dd;

            sljedbenik->rod = obrisi->rod;

            if(obrisi != korijen){
                if(obrisi == obrisi->rod->ld){
                    obrisi->rod->ld = sljedbenik;
                }else{
                    obrisi->rod->dd = sljedbenik;
                }
            }
            else{
                korijen = sljedbenik;
                sljedbenik->dd->rod = sljedbenik;
            }
        }
        broj_elemenata--;
        delete obrisi;
        ProvjeriBalansiranost(g);
    }
    else {
     Cvor* c = obrisi;
     Cvor* g = nullptr;

    if(obrisi->ld != nullptr)
        g = obrisi->rod;

     //smanjujem trenutniNivo svim elementima ispod ovog cvora za 1
     SmanjiNivoZaJedan(c);

     Cvor* prethodni = c;
     int prepoznavanje(0);
     //ovdje se penjem po stablu i gledam je li ova grana u kojoj sam uklonio element ona najduža tako da se mijenjaju
    //nivoi elemenata iznad njega u stablu,uveden je broj prepoznavanja jer se smanji broj pa ide na poziciju iznad te se tada nivoi razlikuju za 2
     while(c != nullptr){
        if(c->ld == prethodni){
            prepoznavanje = 1;

        }else if(c->dd == prethodni){
            prepoznavanje = 2;
        }
        if(c->ld == prethodni){
            if(c->dd != nullptr && c->dd->nivoi+1 == c->nivoi){
                break;
            }
            if((prethodni->nivoi+1 == c->nivoi || c->dd == nullptr) || (prepoznavanje == 1 && prethodni->nivoi+2 == c->nivoi)){
                c->nivoi--;
            }else{
                break;
            }
        }
        else if(c->dd == prethodni){
            if(c->ld != nullptr && c->ld->nivoi+1 == c->nivoi){
                break;
            }
            if((prethodni->nivoi+1 == c->nivoi || c->ld == nullptr)|| (prepoznavanje == 2 && prethodni->nivoi+2 == c->nivoi)){
                c->nivoi--;
            }
            else{
                break;
            }
        }
        prethodni = c;
        c = c->rod;
     }
     if(obrisi->ld != nullptr)
       obrisi->ld->rod = obrisi->rod;
    if(obrisi->dd != nullptr)
       obrisi->dd->rod = obrisi->rod;

     if(obrisi == korijen)
        korijen = obrisi->ld;
     else {
        if(obrisi->rod->ld == obrisi){
            obrisi->rod->ld = obrisi->ld;
        }
        else{
            obrisi->rod->dd = obrisi->dd;
        }
     }
     broj_elemenata--;
     delete obrisi;
     if(g != nullptr){
        ProvjeriBalansiranost(g);
     }
    }
}

template<typename Tip>
void Stablo<Tip>::SmanjiNivoZaJedan(Cvor* c){
    if(c->ld != nullptr)
        SmanjiNivoZaJedan(c->ld);
    c->trenutniNivo--;
    if(c->dd != nullptr)
        SmanjiNivoZaJedan(c->dd);
}

template<typename Tip>
void Stablo<Tip>::BrojNajduzih(Cvor* c,int k,int& br){
    if(c->ld != nullptr)
        BrojNajduzih(c->ld,k,br);
    else{
        if(c->trenutniNivo == k){
            br+=1;
        }
        else
            return;
    }
    if(c->dd != nullptr)
        BrojNajduzih(c->dd,k,br);
    else{
        if(c->trenutniNivo == k){
            br+=1;
        }
        else
            return;
    }
}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::idiDoKraja(Cvor* c){
    Cvor* prethodni = c;
    while(c != nullptr){
        prethodni = c;
        c = c->dd;
    }
    return prethodni;
}

template<typename Tip>
void Stablo<Tip>::DajSveCvorove(Cvor* p,vector<Tip> &v){
    if(p->ld != nullptr)
        DajSveCvorove(p->ld,v);
    v.push_back(p->element);
    if(p->dd != nullptr)
        DajSveCvorove(p->dd,v);
}

template<typename Tip>
void Stablo<Tip>::ObrisiSveCvorove(Cvor* p){ //post order brisanje da ne gubim veze
    if (p == nullptr)
        return;

    ObrisiSveCvorove(p->ld);

    ObrisiSveCvorove(p->dd);

    Obrisi2(p->element);
}

template<typename Tip>
void Stablo<Tip>::Balansiraj(vector<Tip> &v, int s, int k){
    if(s > k)
       return;

    int pola = ((s + k))/2;


    Tip e = v[pola];

    if(!(s == 0 && k == v.size()-1)){
        Insert2(e);
    }

    Balansiraj(v, s, pola-1);
    Balansiraj(v, pola+1, k);

    return;
}

template<typename Tip>
void Stablo<Tip>::ProvjeriBalansiranost(Cvor* prethodni){
    if(prethodni->nivoi+1 >= 2){
        Cvor* p = prethodni;
        p = p->rod;

        while(p != nullptr){
            vector<Tip> v;
            if(prethodni->dd != nullptr && prethodni->dd->rod == prethodni || prethodni->ld != nullptr && prethodni->ld->rod == prethodni){
                if((p->dd != nullptr && p->dd->nivoi > 0 && p->ld == nullptr) || (p->ld != nullptr && p->ld->nivoi > 0 && p->dd == nullptr)
                    || (p->dd != nullptr && p->dd->nivoi == 0 && p->ld->nivoi+1 >= (p->dd->nivoi+1)*2)
                    || (p->ld != nullptr && p->ld->nivoi == 0 && p->dd->nivoi+1 >= (p->ld->nivoi+1)*2)
                    || (p->dd != nullptr && p->ld->nivoi+1 > (p->dd->nivoi+1)*2)
                    || (p->dd != nullptr && p->ld != nullptr) && (p->dd->nivoi >= p->ld->nivoi*2 || p->ld->nivoi >= p->dd->nivoi*2 )){

                    Cvor* c = p;
                    DajSveCvorove(c,v);
                    ObrisiSveCvorove(c);
                    sort(v.begin(),v.end());

                    int br = (v.size()-1)/2; //ovdje prvo dodam srednji elemenat jer mi je potreban pokazivač p za kasnije, inače se obriše i program padne
                    Insert2(v[br]);
                    p = FindCvor(v[br]);

                    Balansiraj(v,0,v.size()-1);
                }
            }
            prethodni = p;

            p = p->rod;
        }
    }
}


#endif // BALANSIRAJUCESTABLO_CPP_INCLUDED
