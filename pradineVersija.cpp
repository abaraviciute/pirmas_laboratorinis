#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::sort;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int ndSkaicius;
    int egzaminas;
    double galutinisPazymys;
};

void ivestis(Studentas& Lok, bool generavimas);
void isvestis(Studentas Lok);
double rezultatai(Studentas Lok, string pasirinkimas);

int main() {
    vector<Studentas> Vec1;
    Studentas Temporary;
    int n; //studentu skaicius

    string pasirinkimas;

    while (true) {
        cout << "Ar norite skaiciuoti galutini pazymi pagal \"Vid\" (vidurki) ar \"Med\" (mediana)? ";
        cin >> pasirinkimas;

        if (pasirinkimas == "Vid" || pasirinkimas == "Med") {
            break;
        }
        else {
            cout << "Neteisingas pasirinkimas. Iveskite \"Vid\" arba \"Med\".\n";
        }
    }

    while (true) {
        cout << "Iveskite studentu skaiciu: ";
        cin >> n;

        if (cin.fail() || n <= 0) {
            cout << "Prasome ivesti teigiama skaiciu!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    bool generavimas;

    for (int i = 0; i < n; i++) {
        cout << "Ar norite ivesti pazymius rankiniu budu, ar juos sugeneruoti atsitiktinai? (Iveskite \"R\" arba \"A\"): ";
        string pasirinkimasGeneravimo;
        cin >> pasirinkimasGeneravimo;

        generavimas = (pasirinkimasGeneravimo == "A");

        cout << "Iveskite studento duomenis: " << endl;
        ivestis(Temporary, generavimas);

        Temporary.galutinisPazymys = rezultatai(Temporary, pasirinkimas);
        Vec1.push_back(Temporary);
    }

    string pazymioTipas;
    if (pasirinkimas == "Med") {
        pazymioTipas = "Med";
    }
    else {
        pazymioTipas = "Vid";
    }

    cout << "\n";
    cout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" 
        << setw(3) << right << "Galutinis (" << pazymioTipas << ".)" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int i = 0; i < n; i++)
        isvestis(Vec1.at(i));
    cout << "\n";

    return 0;
}


void ivestis(Studentas& Lok, bool generavimas)
{
    cout << "Iveskite varda: ";
    cin >> Lok.vardas;

    cout << "Iveskite pavarde: ";
    cin >> Lok.pavarde;

    if (generavimas) {
        Lok.ndSkaicius = 5;
        Lok.nd.clear();
        for (int i = 0; i < Lok.ndSkaicius; i++) {
            int pazymys = rand() % 10 + 1; 
            Lok.nd.push_back(pazymys);
        }
        Lok.egzaminas = rand() % 10 + 1;
    }
    else {
        Lok.ndSkaicius = 0;
        cout << "Iveskite namu darbu pazymius (iveskite -1 noredami baigti): " << endl;
        Lok.nd.clear();
        while (true) {
            int pazymys;
            cout << "Pazymys " << (Lok.ndSkaicius + 1) << ": ";
            cin >> pazymys;

            if (pazymys == -1) {
                break;
            }

            if (cin.fail() || pazymys<1 || pazymys>10) {
                 cout << "Galima ivestis nuo 1 iki 10!\n";
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 continue;
            }

            Lok.nd.push_back(pazymys);
            Lok.ndSkaicius++;
        }
   

        while (true) {
            cout << "Iveskite egzamino pazymi: ";
            cin >> Lok.egzaminas;

            if (cin.fail() || Lok.egzaminas<1 || Lok.egzaminas>10) {
                cout << "Galima ivestis nuo 1 iki 10!!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
    }

}

double rezultatai(Studentas Lok, string pasirinkimas)
{

    if (pasirinkimas == "Vid") {
        double vidurkis = 0.0;

        for (int i = 0; i < Lok.ndSkaicius; i++) {
            vidurkis += Lok.nd[i];
        }
        vidurkis /= Lok.ndSkaicius;

        return 0.4 * vidurkis + 0.6 * Lok.egzaminas;
    }

    if (pasirinkimas == "Med") {
        double mediana;
        vector<int> pazymiai = Lok.nd;
        sort(pazymiai.begin(), pazymiai.end());

        if (Lok.ndSkaicius % 2 == 0) {
            mediana = (pazymiai[Lok.ndSkaicius / 2 - 1] + pazymiai[Lok.ndSkaicius / 2]) / 2.0;
        }
        else {
            mediana = pazymiai[Lok.ndSkaicius / 2];
        }

        return 0.4 * mediana + 0.6 * Lok.egzaminas;
    }

    return 0;
}

void isvestis(Studentas Lok)
{
    cout << setw(15) << left << Lok.pavarde << setw(15) << left << Lok.vardas 
        << setw(3) << right << fixed << setprecision(2) << Lok.galutinisPazymys << endl;
}