#include <iostream>
#include <string>
#include <list>

using namespace std;

class Caine {
protected:
    int id;
    string rasa;
    string data_nastere;
    string sexul;
    string diagnostic; //sanatos/bolnav
    double greutate;
public:
    Caine(){}
    
    Caine(const int& id_c,const string& r, const string& data, const string& s,const string& d, double g):
        id(id_c),
        rasa(r),
        data_nastere(data),
        sexul(s),
        diagnostic(d),
        greutate(g)
    {}
    
    ~Caine(){}
    
    int get_id() 
    {
        return id;
    }

    string get_rasa()
    {
        return rasa;
    }

    string get_data_nastere()
    {
        return data_nastere;
    }

    string get_sexul()
    {
        return sexul;
    }
    
    string get_diagnostic()
    {
        return diagnostic;
    }

    double get_greutate()
    {
        return greutate;
    }

    void set_diagnostic(const string& diag);
};

void Caine::set_diagnostic(const string& diag)
{
    diagnostic = diag;
}

class CainePete : public Caine {

    string culoarePete;
    CainePete(const CainePete&);
    CainePete& operator=(const CainePete&);
public:
    CainePete(){}

    CainePete(const string &culoare, const int& id_c, const string& r, const string& data, const string& s, const string& d, double g):
        culoarePete(culoare),
        Caine(id_c,r,data,s,d,g)
    {}

    ~CainePete()
    {
        cout << "Destructor caine pete\n";
    }

    string get_culoare_pete()
    {
        return culoarePete;
    }

};

class CaineFaraPete : public Caine{

    string talie;//mica,medie,mare
    CaineFaraPete(const CaineFaraPete&);
    CaineFaraPete& operator=(const CaineFaraPete&);
public:
    CaineFaraPete(){}
    
    CaineFaraPete(const string& t, const int& id_c, const string& r, const string& data, const string& s, const string& d, double g) :
        talie(t),
        Caine(id_c,r,data,s,d,g)
    {}

    ~CaineFaraPete()
    {  
        cout << "Destructor caine fara pete\n";
    } 
};


class Cabinet {
public:
    list<Caine> caini;
    list<Caine>::iterator itr;

public: 
    Cabinet(){}
    
    Cabinet(const list<Caine> &c):
        caini(c)
    {}

    ~Cabinet()
    {
        cout << "Destructor cabinet\n";
    }

    Cabinet(const Cabinet& cab):
        caini(cab.caini)
    {}

    Cabinet& operator=(const Cabinet& cab)
    {
        if (&cab != this)
        {
            caini = cab.caini;
        }

        return *this;
    }

    void adauga_caine(Caine cnou)
    {
        caini.push_back(cnou);
    }

    void sterge_caine(int idc)
    {
        itr = caini.begin();
        while (itr != caini.end())
        {
            if (itr->get_id() == idc)
            {
                caini.erase(itr++);
            }
            else
            {
                ++itr;
            }
        }
    }

    void schimb_diagnostic(int idc, const string& diag)
    {
        
        for (Caine c : caini)
        {
            if (c.get_id() == idc)
            {
                c.set_diagnostic(diag);
                sterge_caine(idc);
                caini.push_back(c);
            }
        }
    }

    void afisare_caini()
    {
        for (Caine c : caini)
        {
            cout << c.get_id() << " " << c.get_rasa() << " " << c.get_data_nastere()<<" "<< c.get_sexul()<<" "<<c.get_diagnostic()<<" "<<c.get_greutate()<<"\n";
        } 
        
        cout<<"\n";
    }

    int verificare_id(int id_caine)
    {
        for (Caine c : caini)
        {
            if (c.get_id() == id_caine)
                return 1;
        }

        return 0;
    }  
};


int main()
{
    list<Caine> listaCaini;

    CainePete c1("negru",100,"dalmatian", "2020-07-02", "masulin", "sanatos", 20.00);
    CaineFaraPete c2("mica",101, "pomeranian", "2017-11-20", "feminin","bolnav", 2.50);
    CaineFaraPete c3("medie",102, "bitchon", "2016-06-23", "masculin", "bolnav", 2.50);
    
    //CaineFaraPete c4(c3); eroare
    //CaineFaraPete c5;
    //c5=c3; eroare

    listaCaini.push_back(c1);
    listaCaini.push_back(c2);
    listaCaini.push_back(c3);

    Cabinet cab(listaCaini);
    Cabinet cab1(cab);
    cab1.afisare_caini();
    
    Cabinet cab2;
    cab2=cab;
    cab2.afisare_caini();

    string culoare_pete, rasa_caine, data_caine, sex_caine, diagnostic_caine, talie_caine;
    int id_caine;
    double greutate_caine;
    int op;
    int op1;
    int nr;
    int id_nou;
    string diagnostic_nou;

    do {
        cout << "Alegeti una din optiuni:\n";
        cout << "1. Adaugare caine.\n";
        cout << "2. Stergere caine.\n";
        cout << "3. Afisare lista caini.\n";
        cout << "4. schimbare diagnostic.\n";
        cout << "5. Iesire.\n";


        cin >> op;

        switch (op)
        {
        case 1:
            cout << "Alegeti tipul de caine pe care doriti sa il introduceti:\n1.Caine cu pete.\n2.Caine fara pete.\n";
            cin >> op1;
            cout << "ID: ";
            cin >> id_caine;
            if (cab.verificare_id(id_caine))
            {
                cout << "Cainele exista in sistem\n";
                break;
            }
            cout << "Rasa: ";
            cin >> rasa_caine;
            cout << "Data nastere: ";
            cin >> data_caine;
            cout << "Sexul cainelui: ";
            cin >> sex_caine;
            cout << "Diagnosticul bolnav/sanatos: ";
            cin >> diagnostic_caine;
            cout << "Greutate: ";
            cin >> greutate_caine;

            if (op1 == 1)
            {
                cout << "Culoare pete :";
                cin >> culoare_pete;
                CainePete cp(culoare_pete, id_caine, rasa_caine, data_caine, sex_caine, diagnostic_caine, greutate_caine);
                cab.adauga_caine(cp);

            }
            else if (op1 == 2) {
                cout << "Talie caine(mica/medie/mare): ";
                cin >> talie_caine;
                CaineFaraPete d(talie_caine, id_caine, rasa_caine, data_caine, sex_caine, diagnostic_caine, greutate_caine);
                cab.adauga_caine(d);

            }
            break;
        case 2:
            cout << "Introduceti id-ul:";
            cin >> nr;
            cab.sterge_caine(nr);
            break;
        case 3:
            cab.afisare_caini();
            break;
        case 4:
            cout << "Introducet id-ul: ";
            cin >> id_nou;
            cout << "Introduceti diagnosticul bolnav/sanatos: ";
            cin >> diagnostic_nou;
            cab.schimb_diagnostic(id_nou, diagnostic_nou);
            break;
        case 5:
            break;

        default:
            break;
        }

    } while (op != 5);
    return 0;
}

