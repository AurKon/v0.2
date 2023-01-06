#include "strukt.h"

using namespace std;


int main()
{
    int n, kieknd, tempvaik; // n - mokiniu skaicius, nd - namų darbų pažymys
    vector<duom> A; // vektoriaus strukturos
    list<duom> B;
    string tipas;
    cout << "Pasirinkite, ar duomenis skaityti is failo(F), ar juos sugeneruoti automatiskai(G), ar ivedinesite patys(P)? F/G/P: ";
    cin >> tipas;
    cout << endl;
    if(tipas=="F"||tipas=="f")
    {
        cout << "Iveskite studentu skaiciu: ";
        cin >> tempvaik;
        fskaitymas(A, &kieknd, tempvaik);
        fisvedimas(A, kieknd);
    }
    else if(tipas=="G"||tipas=="g")
    {
        cout << "Iveskite studentu skaiciu: ";
        cin >> tempvaik;
        failogen(A, tempvaik);
        fskaitymas(A, &kieknd, tempvaik);
        fskaitymas_list(B, &kieknd, tempvaik);
        fisvedimas(A, kieknd);
        fisvedimas_list(B,kieknd);
    }
    else if(tipas=="P"||tipas=="p")
    {
        cout << "Iveskite studentu skaiciu: ";
        cin >> n;
        ivedimas(A, n);
        isvedimas(A, n);
    }
    else
    {
        cout<<"KLAIDA IVEDIME!!!"<<endl;
    }
    return 0;
}
