#include "email.h"
#include <conio.h>
#include <time.h>

const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d-%m-%Y, %X", &tstruct);
    return buf;
}

void createList(List &L)
{
    firstP(L) = NULL;
}

adrP alokasiP (label lbl)
{
    adrP P;
    P = new ElmListP;

    infoP(P) = lbl;
    nextP(P) = NULL;
    P->prevP = NULL;
    firstC(P) = NULL;
    return P;
}

adrC alokasiC (email eml)
{
    adrC P;
    P = new ElmListC;

    infoC(P) = eml;
    nextC(P) = NULL;
    return P;
}

void createLabelDefault (List &L)
{
    createLabelDefaultHelper(L, "Inbox");
    createLabelDefaultHelper(L, "Draft");
    createLabelDefaultHelper(L, "Sent");
    createLabelDefaultHelper(L, "Trash");
}

void insertLastP (List &L, adrP P)
{

    if (firstP(L) == NULL)
    {
        firstP(L) = P;
        P->prevP = P;
    }
    else
    {
        adrP Q = firstP(L);
        while (nextP(Q) != NULL)
        {
            Q = nextP(Q);
        }
        nextP(Q) = P;
        prevP(P) = Q;
    }
}

void createLabelDefaultHelper(List &L, string namaLabel)
{

    adrP P;
    label lbl;
    lbl.namaLabel = namaLabel;
    lbl.jumEmail = 0;
    lbl.tanggalLabel = "-";

    P = alokasiP(lbl);
    insertLastP(L, P);
}

void insertLastC (List &L, adrP P,adrC C)
{
    if (firstC(P) == NULL)
    {
        firstC(P) = C;
    }
    else
    {
        adrC Q;
        Q = firstC(P);
        while (nextC(Q) != NULL)
        {
            Q = nextC(Q);
        }
        nextC(Q) = C;
    }
}

void createLabel(List &L)
{
    label lbl;
    adrP P;

    cout << "Masukan nama label: ";
    cin>>lbl.namaLabel;
//    cin.ignore(-1);
//    getline(cin,lbl.namaLabel);

    lbl.jumEmail = 0;
    lbl.tanggalLabel = "-";

    P = alokasiP(lbl);
    insertLastP(L, P);
    cout<<"---------- Label berhasil ditambahkan ----------";
    getch();
}

void createEmail(List &L)
{
    email eml;
    adrC C;
    adrP P = firstP(L);
    string label;
    cout << "Masukan Label: ";
    cin >> label;
//    cin.ignore(-1);
//    getline(cin,label);
    while (nextP(P) != NULL && P->infoP.namaLabel != label)
    {
        P = nextP(P);
    }

    if (label == P->infoP.namaLabel)
    {
        cout << "Masukan Pengirim Email: ";
        cin >> eml.pengirimEmail;
        cout << "Masukan Penerima Email: ";
        cin >> eml.tujuanEmail;
        cout << "Masukan Judul Email: ";
        cin >> eml.judulEmail;
//        cin.ignore(-1);
//        getline(cin,eml.judulEmail);
        cout << "Masukan isi Email: ";
        cin >> eml.isiEmail;
//        cin.ignore(-1);
//        getline(cin,eml.isiEmail);
        eml.tanggalEmail = currentDateTime();

        C = alokasiC(eml);
        insertLastC(L, P, C);
        P->infoP.jumEmail =  P->infoP.jumEmail + 1;
        P->infoP.tanggalLabel = eml.tanggalEmail;
        cout << "---------- Email berhasil dimasukkan ----------";
    }
    else
    {
        cout << "---------- Label tidak ditemukan ----------";
    }
    getch();
}

void kirimEmail(List &L)
{
    email eml;
    adrC C;
    adrP P = firstP(L);
    string label;

    label = "Sent";
    while (nextP(P) != NULL && P->infoP.namaLabel != label)
    {
        P = nextP(P);
    }

    if (label == P->infoP.namaLabel)
    {
        cout << "Masukan Pengirim Email: ";
        cin >> eml.pengirimEmail;
        cout << "Masukan Penerima Email: ";
        cin >> eml.tujuanEmail;
        cout << "Masukan Judul Email: ";
        cin >> eml.judulEmail;
//        cin.ignore(-1);
//        getline(cin,eml.judulEmail);
        cout << "Masukan isi Email: ";
        cin >> eml.isiEmail;
//        cin.ignore(-1);
//        getline(cin,eml.isiEmail);
        eml.tanggalEmail = currentDateTime();

        C = alokasiC(eml);
        insertLastC(L, P, C);
        P->infoP.jumEmail =  P->infoP.jumEmail + 1;
        P->infoP.tanggalLabel = eml.tanggalEmail;
        cout<<"---------- Email berhasil dikirim ----------";
    }
    else
    {
        cout << "---------- Label tidak ditemukan ----------";
    }
    getch();
}

void showSemua (List &L)
{
    adrP P = firstP(L);
    adrC C;

    while (P != NULL)
    {
        cout << "Nama Label: " << P->infoP.namaLabel << endl;
        cout << "Jumlah Email: " << P->infoP.jumEmail << endl;
        cout << "Tanggal Terakhir: " << P->infoP.tanggalLabel << endl;

        C = firstC(P);
        while (C != NULL)
        {
            cout << "   Pengirim Email: " << C->infoC.pengirimEmail << endl;
            cout << "   Penerima Email: " << C->infoC.tujuanEmail << endl;
            cout << "   Judul Email: " << C->infoC.judulEmail <<endl;
            cout << "   Isi Email: " <<C->infoC.isiEmail << endl;
            cout << "   Tanggal Email: " <<C->infoC.tanggalEmail << endl << endl;

            C= nextC(C);
        }
        cout << endl;
        P = P->nextP;
    }
    getch();
}

void showEmailbyLabel (List &L)
{
    adrC C;
    adrP P = firstP(L);
    string label;

    cout << "Masukan Label: ";
    cin >> label;
    while (nextP(P) != NULL && P->infoP.namaLabel != label)
    {
        P = nextP(P);
    }

    if (P->infoP.namaLabel == label)
    {
        cout << "Nama Label: " << P->infoP.namaLabel << endl;
        cout << "Jumlah Email: " << P->infoP.jumEmail << endl;
        cout << "Tanggal Terakhir: " << P->infoP.tanggalLabel << endl;

        C = firstC(P);
        while (C != NULL)
        {
            cout << "   Pengirim Email: " << C->infoC.pengirimEmail << endl;
            cout << "   Penerima Email: " << C->infoC.tujuanEmail << endl;
            cout << "   Judul Email: " << C->infoC.judulEmail <<endl;
            cout << "   Isi Email: " <<C->infoC.isiEmail << endl;
            cout << "   Tanggal Email: " <<C->infoC.tanggalEmail << endl << endl;

            C= nextC(C);
        }
    } else {
        cout << "Label tidak ditemukan" << endl;
    }
    getch();
}

void searchPengirim(List L, string pengirim)
{
    bool found = false;
    adrP P = firstP(L);
    adrC C;
    while (P != NULL)
    {
        C = firstC(P);
        while (C != NULL)
        {
            if (C->infoC.pengirimEmail == pengirim)
            {
                cout << "Nama Label: " << P->infoP.namaLabel << endl;
                cout << "   Pengirim Email: " << C->infoC.pengirimEmail << endl;
                cout << "   Penerima Email: " << C->infoC.tujuanEmail << endl;
                cout << "   Judul Email: " << C->infoC.judulEmail <<endl;
                cout << "   Isi Email: " <<C->infoC.isiEmail << endl;
                cout << "   Tanggal Email: " <<C->infoC.tanggalEmail << endl << endl;
                found = true;
            }
            C= nextC(C);
        }
        P = P->nextP;
    }
    if (found == false)
    {
        cout << "---------- Email tidak ditemukan ----------" << endl;
    }
    getch();
}

void searchPenerima(List L, string penerima)
{
    bool found = false;
    adrP P = firstP(L);
    adrC C;
    while (P != NULL)
    {
        C = firstC(P);
        while (C != NULL)
        {
            if (C->infoC.tujuanEmail == penerima)
            {
                cout << "Nama Label: " << P->infoP.namaLabel << endl;
                cout << "   Pengirim Email: " << C->infoC.pengirimEmail << endl;
                cout << "   Penerima Email: " << C->infoC.tujuanEmail << endl;
                cout << "   Judul Email: " << C->infoC.judulEmail <<endl;
                cout << "   Isi Email: " <<C->infoC.isiEmail << endl;
                cout << "   Tanggal Email: " <<C->infoC.tanggalEmail << endl << endl;
                found = true;
            }
            C= nextC(C);
        }
        P = P->nextP;
    }
    if (found == false)
    {
        cout << "---------- Email tidak ditemukan ----------" << endl;
    }
    getch();
}

void deleteLabel(List &L)
{
    string namaLab;
    cout<<"Masukkan nama label yang akan di hapus : ";
    cin >> namaLab;
    if ((namaLab=="Inbox")||(namaLab=="Sent")||(namaLab=="Draft")||(namaLab=="Trash"))
    {
        cout<<"---------- Label Default tidak bisa dihapus ----------";
    }
    else
    {
        // cari label yang akan dihapus
        adrP p = firstP(L);
        while ((infoP(p).namaLabel != namaLab)&&(nextP(p) != NULL))
        {
            p = nextP(p);
        }
        // pindah anak dari label yang di delete
        if ((infoP(p).namaLabel == namaLab)&&(p != NULL))
        {
            // cari label trash
            if (firstC(p)!=NULL)
            {
                adrP q = firstP(L);
                while ((infoP(q).namaLabel!="Trash")&&(q!=NULL))
                {
                    q = nextP(q);
                }
                adrC r = firstC(q);
                while (nextC(r)!=NULL)
                {
                    r = nextC(r);
                }
                nextC(r) = firstC(p);
                firstC(p) = NULL;
                infoP(q).jumEmail = infoP(q).jumEmail + infoP(p).jumEmail;
                infoP(q).tanggalLabel = currentDateTime();
                infoP(p).jumEmail = 0;
                infoP(p).tanggalLabel = currentDateTime();
            }
            // delete
            if (p==firstP(L))
            {
                firstP(L) = nextP(p);
                prevP(firstP(L)) = NULL;
                nextP(p) = NULL;
            }
            else if (nextP(p)==NULL)
            {
                adrP l = prevP(p);
                nextP(l) = NULL;
                prevP(p) = NULL;
            }
            else
            {
                adrP pre = prevP(p);
                nextP(pre) = nextP(p);
                prevP(nextP(p)) = pre;
                prevP(p) = NULL;
                nextP(p) = NULL;
            }
            cout<<" ---------- Label berhasil di delete ----------";
        }
        else
        {
            cout<<"---------- Label tersebut tidak ada ----------";
        }
    }
    getch();
};

void deleteEmail(List &L)
{
    string pengirim, penerima, judul;
    cout<<"Masukkan pengirim : ";
    cin>>pengirim;
    cout<<"Masukkan penerima : ";
    cin>>penerima;
    cout<<"Masukkan judul Email : ";
    cin >> judul;
//    cin.ignore(-1);
//    getline(cin,judul);
    bool cek = false;
    adrC r,q;
    adrP p = firstP(L);
    while ((p!=NULL)&&(cek==false))
    {
        if(firstC(p)==NULL)
        {
            p = nextP(p);
        }
        else
        {
            // search email
            q = firstC(p);
            while ((q!=NULL)&&((infoC(q).pengirimEmail!=pengirim)||(infoC(q).tujuanEmail!=penerima)||(infoC(q).judulEmail!=judul)))
            {
                r = q;
                q = nextC(q);
            }
            if (q == NULL)
            {
                cek = false;
                p = nextP(p);
            }
            else
            {
                cek = true;
            }
        }
    }
    if (p!=NULL)
    {
        // delete
        if (q==firstC(p))
        {
            // delete first
            firstC(p) = nextC(q);
            nextC(q) = NULL;
        }
        else if (nextC(q)==NULL)
        {
            //delete last
            nextC(r) = NULL;
        }
        else
        {
            // delete after
            nextC(r) = nextC(q);
            nextC(q) = NULL;
        }
        // cek label
        if (infoP(p).namaLabel=="Trash")
        {
            infoP(p).jumEmail--;
            cout<<"---------- Email berhasil di delete dari Trash ----------";
        }
        else
        {
            // cari label trash
            adrP trash = firstP(L);
            while ((infoP(trash).namaLabel!="Trash")&&(trash!=NULL))
            {
                trash = nextP(trash);
            }
            insertLastC(L,trash,q);
            infoP(trash).jumEmail++;
            infoP(trash).tanggalLabel = currentDateTime();;
            infoP(p).jumEmail--;
            infoP(p).tanggalLabel = currentDateTime();;
            cout<<"---------- Email berhasil di delete dan dipindah ke Trash ----------";
        }
    }
    else
    {
        cout<<"---------- Email tidak ditemukan ----------";
    }
    getch();
};

void delAllEmail(List &L)
{
    string namaLab;
    cout<<"masukkan nama Label : ";
    cin>>namaLab;

    // cari label
    adrP p = firstP(L);
    while ((infoP(p).namaLabel!=namaLab)&&(nextP(p)!=NULL))
    {
        p = nextP(p);
    }
    if (infoP(p).namaLabel==namaLab)
    {
        if (firstC(p)==NULL)
        {
            cout<<"---------- Email dalam Label tersebut tidak ada ----------";
        }
        else
        {
            if (namaLab == "Trash")
            {
                firstC(p) = NULL;
            }
            else
            {
                // cari Label trash
                adrP q = firstP(L);
                while ((infoP(q).namaLabel!="Trash")&&(q!=NULL))
                {
                    q = nextP(q);
                }
                // cari last child
                adrC r = firstC(p);
                while (nextC(r)!=NULL)
                {
                    r = nextC(r);
                }
                // email dr label cut ke trash
                eml x;
                adrC s = firstC(p);
                while (s!=NULL)
                {
                    x = infoC(s);
                    adrC baru = alokasiC(x);
                    insertLastC(L,q,baru);
                    s = nextC(s);
                }
                firstC(p) = NULL;
                infoP(q).jumEmail = infoP(q).jumEmail + infoP(p).jumEmail;
                infoP(q).tanggalLabel = currentDateTime();;
                infoP(p).jumEmail = 0;
                infoP(p).tanggalLabel = currentDateTime();;
            }
            cout<<"---------- Semua email berhasil di delete ----------";
        }
    }
    else
    {
        cout<<"---------- Label tersebut tidak ditemukan ----------";
    }
    getch();
};

void inboxToLabel(List &L)
{
    string pengirim;
    string judul;
    string namaLab;
    cout<<"Masukkan pengirim email      : ";
    cin>>pengirim;
    cout<<"Masukkan judul               : ";
    cin >> judul;
//    cin.ignore(-1);
//    getline(cin,judul);
    cout<<"Masukkan nama Label tujuan   : ";
    cin>>namaLab;
    // cari parent Inbox
    adrP p = firstP(L);
    while ((infoP(p).namaLabel!="Inbox")&&(p!=NULL))
    {
        p = nextP(p);
    }
    if (firstC(p)==NULL)
    {
        cout<<endl<<"---------- Tidak ada email dalam Inbox ----------";
    }
    else
    {
        // cari email di inbox
        adrC q = firstC(p);
        while ((infoC(q).pengirimEmail!=pengirim)&&(infoC(q).judulEmail!=judul)&&(q!=NULL))
        {
            q = nextC(q);
        }
        if ((q==NULL)||(infoC(q).pengirimEmail!=pengirim)||(infoC(q).judulEmail!=judul))
        {
            cout<<"---------- Email tidak ditemukan ----------";
        }
        else
        {
            // cari Label yg ditunjuk
            adrP r = firstP(L);
            while ((r!=NULL)&&(infoP(r).namaLabel!=namaLab))
            {
                r = nextP(r);
            }
            if ((r != NULL)&&(infoP(r).namaLabel == namaLab))
            {
                // copy email
                eml x;
                x.pengirimEmail = pengirim;
                x.tujuanEmail = infoC(q).tujuanEmail;
                x.judulEmail = judul;
                x.isiEmail = infoC(q).isiEmail;
                x.tanggalEmail = infoC(q).tanggalEmail;
                adrC s = alokasiC(x);
                //insert last child
                insertLastC(L,r,s);
                infoP(r).jumEmail++;
                infoP(r).tanggalLabel = currentDateTime();;
                cout<<"---------- Email berhasil di edit dan dipindah ----------";
            }
            else
            {
                cout<<"---------- Label tersebut tidak ada ----------";
            }
        }
    }
    getch();
};

void draftToSent(List &L)
{
    string penerima,judul;
    cout<<"Masukkan nama penerima : ";
    cin>>penerima;
    cout<<"Masukkan judul Email : ";
    cin >> judul;
//    cin.ignore(-1);
//    getline(cin,judul);

    // cari label Draft
    adrP p = firstP(L);
    while (infoP(p).namaLabel!="Draft")
    {
        p = nextP(p);
    }
    // cari email di Draft
    if (firstC(p)==NULL)
    {
        cout<<"---------- Tidak ada email di draft ----------";
    }
    else
    {
        adrC q = firstC(p);
        adrC r;
        while ((infoC(q).tujuanEmail!=penerima)&&(infoC(q).judulEmail!=judul)&&(q!=NULL))
        {
            r = q;
            q = nextC(q);
        }
        if ((q==NULL)||(infoC(q).tujuanEmail!=penerima)||(infoC(q).judulEmail!=judul))
        {
            cout<<"---------- Email tidak ditemukan ----------";
        }
        else
        {
            cout<<"Penerima : "<<infoC(q).tujuanEmail<<endl;
            cout<<"Judul    : "<<infoC(q).judulEmail<<endl;
            cout<<"Isi      : "<<infoC(q).isiEmail<<endl;
            cout<<"---------- EDIT ----------"<<endl;
            cout<<"Penerima     : ";
            cin>>infoC(q).tujuanEmail;
            cout<<"\njudul Email  : ";
            cin >> infoC(q).judulEmail;
//            cin.ignore(-1);
//            getline(cin,infoC(q).judulEmail);
            cout<<"\nIsi Email  : ";
            cin >> infoC(q).isiEmail;
//            cin.ignore(-1);
//            getline(cin,infoC(q).isiEmail);

            // delete email di draft
            if (q==firstC(p))
            {
                firstC(p) = nextC(q);
            }
            else if (nextC(q)==NULL)
            {
                nextC(r) = NULL;
            }
            else
            {
                nextC(r) = nextC(q);
                nextC(q) = NULL;
            }
            infoP(p).jumEmail--;
            infoP(p).tanggalLabel = currentDateTime();

            // cari label sent
            adrP a = firstP(L);
            while (infoP(a).namaLabel!="Sent")
            {
                a = nextP(a);
            }
            //insert child
            insertLastC(L,a,q);
            infoP(a).jumEmail++;
            infoP(a).tanggalLabel = currentDateTime();
            cout<<"---------- Email berhasil di kirim ----------";
        }
    }
    getch();
};

void report(List L)
{
    adrP p = firstP(L);
    cout<<"Nama Label               |   Jumlah Email"<<endl;
    cout<<"--------------------------------------------" << endl;
    while (p!=NULL)
    {
        cout<<infoP(p).namaLabel<<"                    : ";
        cout<<infoP(p).jumEmail<<" email\n";
        p = nextP(p);
    }
    getch();
};

void menu (List &L)
{
    int pil=0;
    createLabelDefault(L);
    while (pil>=0 && pil<= 14)
    {
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "--------------------------------------------------------" << endl<<endl;
        cout << " 1. Tambah Label" << endl;
        cout << " 2. Masukan Email" << endl;
        cout << " 3. Kirim Email" << endl;

        cout << " 4. Edit Email dari Inbox pindah ke Label Lain" << endl;
        cout << " 5. Edit Email dari Draft dan kirim" << endl;

        cout << " 6. Delete Label" << endl;
        cout << " 7. Delete Email" << endl;
        cout << " 8. Delete semua email di Label tertentu" << endl;

        cout << " 9. Lihat Semua" << endl;
        cout << "10. Lihat Email Pada Label" << endl;

        cout << "11. Cari Email berdasarkan Pengirim" << endl;
        cout << "12. Cari Email berdasarkan Tujuan"<< endl;

        cout << "13. Report Jumlah Email" << endl;
        cout << "14. EXIT" << endl<<endl;
        cout << "--------------------------------------------------------" << endl;

        cout<<"Pilih menu : ";
        cin >> pil;
        if (pil == 1)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            createLabel(L);
        }
        else if (pil == 2)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            createEmail(L);
        }
        else if (pil == 3)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            kirimEmail(L);
        }
        else if (pil == 4)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            inboxToLabel(L);
        }
        else if (pil == 5)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            draftToSent(L);
        }
        else if (pil == 6)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            deleteLabel(L);
        }
        else if (pil == 7)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            deleteEmail(L);
        }
        else if (pil == 8)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            delAllEmail(L);
        }
        else if (pil == 9)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            showSemua(L);
        }
        else if (pil == 10)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            showEmailbyLabel(L);
        }
        else if (pil == 11)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            string pengirim;
            cout << "Masukan Email Pengirim: ";
            cin >> pengirim;
            searchPengirim(L, pengirim);
        }
        else if (pil == 12)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            string penerima;
            cout << "Masukan Email Penerima: ";
            cin >> penerima;
            searchPenerima(L, penerima);
        }
        else if (pil == 13)
        {
            cout << "--------------------------------------------------------" << endl<<endl;
            report(L);
        }
        else if (pil == 14)
        {
            break;
        }
        cout << endl;
        system("CLS");

    }
}
