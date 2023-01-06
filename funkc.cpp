#include "strukt.h"
#include <string>
using namespace std;

unsigned int zodziai(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}


int pazymiogen()
{
	return rand() % 10 + 1;
}


void ivedimas(vector<duom>& SK, int n)
{
    int temp; // konkretaus namu darbo rezultatas
    for(int i=0; i<n; i++)
    {
        SK.resize(SK.size()+1);
        cout << "Iveskite studento varda: ";
        cin >> SK[i].vard;
        cout << "Iveskite studento pavarde: ";
        cin >> SK[i].pav;
        string pasirinkti;
        cout << "Ar pazymius irasysite patys(P) ar juos parinkti atsitiktinai(A)? P/A: " << endl;
        cin >> pasirinkti;
        if(pasirinkti == "P"||pasirinkti == "p")
        {
            cout << "Iveskite studento egzamino rezultata: ";
            cin >> SK[i].egz;
            while(true) // ivesti arba randominiai skaiciai sukeliami i vektoriaus pabaiga
            {
                cout << "Iveskite namu darbo pazymi, jeigu daugiau pazymiu nera, iveskite 0: " << endl;
                cin >> temp;
                if(temp == 0)
                {
                    break;
                }
                SK[i].ndrez.push_back(temp);
            }
            if(SK[i].ndrez.size()<1)
            {
                cout << "Studentas neturi nei vieno namu darbu pazymio" << endl;
            }
        }
        else if(pasirinkti == "A"||pasirinkti == "a")
        {

            int kiek;
            cout<<"Kiek sugeneruoti nd pazymiu?: ";
            cin>>kiek;
            cout<<"Sugeneruoti nd pazymiai: ";
            for(int z=0; z<kiek; z++)
            {
                SK[i].ndrez.push_back(rand()%10+1);
                cout<<SK[i].ndrez[z]<<" ";
            }
            cout<<endl;
            cout<<"Sugeneruotas egzamino pazymys: ";
            SK[i].egz=1+std::rand()%10;
            cout<<SK[i].egz<<endl;
        }
        else //programos stabdymas, jei ivesties formatas neteisingas
        {
            cout<<"KLAIDA IVEDIME!!!"<<endl;
            return;
        }
    }
}
double vidurkis(double visindrez, int m) // vidurkio funkcija
{
    double vid;
    vid = visindrez/m;
    if(m==0)
        vid = 0;
    return vid;
}
double mediana(duom SK, int n){ // medianos funkcija
    double mediana;
    if(SK.ndrez.size()==0){
        mediana=0;
    }
    else{
        if(SK.ndrez.size()%2==0)
        {
            int k = SK.ndrez.size()/2;
            mediana=(SK.ndrez[k]+SK.ndrez[k-1])/2.0;
        }
        else
            mediana = SK.ndrez[SK.ndrez.size()/2];
    }
    return mediana;
}
double rezultatas(double a, double b){
    double gpaz;
    gpaz = (0.4*a)+(0.6*b);
    return gpaz;
}

void isvedimas(vector<duom> SK, int n){
    cout << left << setw(15) << "Vardas" << left << setw(15) << "pavarde" << left << setw(15) <<"Galutinis (Vid.)" << " / " << setw(15) << "Galutinis (Med.)" << endl;
    for(int k=0; k<60; k++){
    cout << "_";
    }
    cout<<endl;
    for(int i=0; i<n; i++){

        double suma; // vektoriaus elementu suma
        suma = accumulate(SK[i].ndrez.begin(), SK[i].ndrez.end(), 0);
        sort(SK[i].ndrez.begin(), SK[i].ndrez.end());
        cout << left << setw(15) << SK[i].vard << left << setw(15) << SK[i].pav << left << setw(15) << fixed << setprecision(2) << rezultatas(vidurkis(suma, SK[i].ndrez.size()), SK[i].egz)<< left << setw(15) << rezultatas(mediana(SK[i], SK[i].ndrez.size()), SK[i].egz) << endl;
    }
}

void failogen(vector<duom>& SK, int tempvaik)
{
    int randsk;
    randsk = rand()% 3 + 3;
    string failas = "Studentai" + to_string(tempvaik)+".txt";
    ofstream w1(failas);
    w1 << setw(16) << left << "Vardas"
		<< setw(16) << left << "Pavarde";
    for(int n=0; n<randsk; n++)
    {
        w1 << setw(5) << "ND" + to_string(n+1);
    }
    w1 << "Egz." << endl;
    for (int j=0; j<tempvaik; j++)
    {
        w1 << setw(16) << "Vardas" + to_string(j+1)
			<< setw(16) << "Pavarde" + to_string(j+1);
        for(int k=0; k<randsk; k++)
        {
            w1 << setw(5) << pazymiogen();
        }
        w1 << setw(5) << pazymiogen() << endl;
    }
}
void fskaitymas_list (list<duom>& sk, int* kieknd, int tempvaik)
{
    auto start = std::chrono::high_resolution_clock::now();
    string buff, eilute;
    int temp;
    int vaikusk = 0;
    string failas = "Studentai" + to_string(tempvaik)+".txt";
    ifstream r;
    try{
        r.open(failas);
        if(!r)
            throw std::runtime_error("Nepavyko rasti failo");

        getline(r >> ws, buff);
        *kieknd = zodziai(buff) - 3;

        while(true)
        {
            if(r.eof())
            {
                sk.pop_back();
                break;
            }
            duom studentas;
            r >> studentas.vard >> studentas.pav;

            for(int i=0; i<*kieknd; i++)
            {
                r >> temp;
                studentas.ndrez.push_back(temp);
            }
            r >> studentas.egz;

            sk.push_back(studentas);
            vaikusk +=1;
        }
    }
    catch(int e){}
     auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
	std::cout << "Duomenu nuskaitymas su listu uztruko: " << diff.count() << " s\n";
}
void fskaitymas (vector<duom>& SK, int* kieknd, int tempstud)
{
    auto start = std::chrono::high_resolution_clock::now();

    int temp;
    int studsk = 0;
    string buff;
    ifstream r;
    string failas = "Studentai" + to_string(tempstud)+".txt";
    try{
        r.open(failas);
        if(!r)
            throw std::runtime_error("Nepavyko rasti failo");

            getline(r >> std::ws, buff);
            *kieknd = zodziai(buff) - 3;
            while(true)
            {
                SK.resize(SK.size()+1);
                r >> SK.at(studsk).vard;
                if(r.eof())
                {
                    SK.pop_back();
                    break;
                }
                r >> SK.at(studsk).pav;
                for(int i=0; i<*kieknd; i++)
                {
                    r >> temp;
                    SK.at(studsk).ndrez.push_back(temp);
                }
                r >> SK.at(studsk).egz;
                studsk += 1;
            }
            r.close();
    }
    catch(int e){}
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
	std::cout << "Duomenu nuskaitymas su vektorium uztruko: " << diff.count() << " s\n";
}

void fisvedimas(vector<duom> SK, int kieknd)
{
    auto start1 = std::chrono::high_resolution_clock::now();
    ofstream w1, w2;
    w1.open("Vargsiukai.txt");
    w2.open("Kietiakai.txt");
    w1 << left << setw(17) << "Vardas" << left << setw(17) << "Pavarde"
        << left << setw(22) << "Galutinis(vid.)/" << left << setw(22)
        << "Galutinis(med.)\n";

    w2 << left << setw(17) << "Vardas" << left << setw(17) << "Pavarde"
        << left << setw(22) << "Galutinis(vid.)/" << left << setw(22)
        << "Galutinis(med.)\n";

    for(int k=0; k<70; k++)
    {
        w1 << "_" ;
        w2 << "_" ;
    }
    w1 << endl;
    w2 << endl;


    for(int i=0; i<SK.size(); i++)
    {
        double suma; // vektoriaus elementu suma
        suma = accumulate(SK[i].ndrez.begin(), SK[i].ndrez.end(), 0);
        sort(SK[i].ndrez.begin(), SK[i].ndrez.end());

        if(rezultatas(vidurkis(suma, SK[i].ndrez.size()),SK[i].egz)<5)
           {
                w1 << left << setw(17) << SK[i].vard << left << setw(17) << SK[i].pav
                    <<left << setw(22) << fixed << setprecision(2) << rezultatas(vidurkis(suma, SK[i].ndrez.size()), SK[i].egz)
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(mediana(SK[i], SK[i].ndrez.size()), SK[i].egz) << endl;
           }
           else
            {
                w2 << left << setw(17) << SK[i].vard << left << setw(17) << SK[i].pav
                    <<left << setw(22) << fixed << setprecision(2) << rezultatas(vidurkis(suma, SK[i].ndrez.size()), SK[i].egz)
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(mediana(SK[i], SK[i].ndrez.size()), SK[i].egz) << endl;
            }
    }

    w1.close();
    w2.close();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    std::cout << "Duomenu isvedimas i du failus su vektorium uztruko: " << diff1.count() << " s\n";
}




void fisvedimas_list (list<duom> SK, int kieknd)
{
    auto start1 = std::chrono::high_resolution_clock::now();
    ofstream w1, w2;
    w1.open("Vargsiukai_List.txt");
    w2.open("Kietiakai_List.txt");
    w1 << left << setw(17) << "Vardas" << left << setw(17) << "Pavarde"
        << left << setw(22) << "Galutinis(vid.)/" << left << setw(22)
        << "Galutinis(med.)\n";

    w2 << left << setw(17) << "Vardas" << left << setw(17) << "Pavarde"
        << left << setw(22) << "Galutinis(vid.)/" << left << setw(22)
        << "Galutinis(med.)\n";

    for(int k=0; k<70; k++)
    {
        w1 << "_" ;
        w2 << "_" ;
    }
    w1 << endl;
    w2 << endl;


    double suma;
    vector<int> temp1;
    for(std::list<duom>::iterator it = SK.begin(); it != SK.end(); ++it){
        temp1 = it->ndrez;

        suma = accumulate(temp1.begin(), temp1.end(), 0);
        sort(temp1.begin(), temp1.end());

        if(rezultatas(vidurkis(suma, temp1.size()),it->egz)<5)
           {
                w1 << left << setw(17) << it->vard << left << setw(17) << it->pav
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(vidurkis(suma, it->ndrez.size()), it->egz)
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(mediana(*it, it->ndrez.size()), it->egz) << endl;
           }
           else
            {
                w2 << left << setw(17) << it->vard << left << setw(17) << it->pav
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(vidurkis(suma, it->ndrez.size()), it->egz)
                    << left << setw(22) << fixed << setprecision(2) << rezultatas(mediana(*it, it->ndrez.size()), it->egz) << endl;
            }
    }
     w1.close();
     w2.close();

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    std::cout << "Duomenu isvedimas i du failus su listu uztruko: " << diff1.count() << " s\n";

}
