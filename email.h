#ifndef EMAIL_H_INCLUDED
#define EMAIL_H_INCLUDED

#define firstP(L) L.firstP
#define firstC(P) P->firstC
#define nextP(P) P->nextP
#define prevP(P) P->prevP
#define infoP(P) P->infoP
#define infoC(P) P->infoC
#define nextC(P) P->nextC
#include <cstdlib>
#include <iostream>
using namespace std;

struct eml {
    string pengirimEmail;
    string tujuanEmail;
    string judulEmail;
    string isiEmail;
    string tanggalEmail;
};
struct lbl {
    string namaLabel;
    int jumEmail;
    string tanggalLabel;
};
typedef eml email;
typedef lbl label;
typedef struct ElmListP *adrP;
typedef struct ElmListC *adrC;

struct ElmListP{
    label infoP;
    adrP nextP;
    adrP prevP;
    adrC firstC;
};
struct ElmListC{
    email infoC;
    adrC nextC;
};

struct List{
    adrP firstP;
};

void createList(List &L);
adrP alokasiP (label lbl);
adrC alokasiC (email eml);

void insertLastC (List &L, adrP P,adrC C);
void createLabel(List &L);
void menu (List &L);
void createLabelDefault(List &L);
void createLabelDefaultHelper(List &L, string namaLabel);

void deleteLabel(List &L);
void deleteEmail(List &L);
void delAllEmail(List &L);
void inboxToLabel(List &L);
void draftToSent(List &L);
void report(List L);
#endif // EMAIL_H_INCLUDED
