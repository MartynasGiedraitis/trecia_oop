#include "mylib.h"
#include "studentas.h"
#include <iostream>
#include <iomanip>  
#include <vector>
#include <string>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

int main (){
    srand(time(0));
    list<Student>lst1;
    Student temp;
    int c,k,p,n,r,j,g,pasirinkimas;
    string fileName;
    while (true) {
    cout << "Ar norite sugeneruoti/naudotis jau sugeneruotais failais? (1 - sugeneruoti,"
    "2 - naudotis jau sugeneruotais, 3 - kita, 4 - constructor'iu patikrinimas): ";
    string input;
    cin >> input;
    try {
        g = stoi(input); 
        if (g >= 1 && g <= 4) {
            break;  
        } else {
            cout << "Netinkama ivestis. Pasirinkimas turi buti 1, 2 arba 3." << endl;
        }
    } catch (const invalid_argument&) {
        cout << "Ivestas ne skaicius. Bandykite dar karta." << endl;
    } catch (const out_of_range&) {
        cout << "Ivestas skaicius yra per didelis. Bandykite dar karta." << endl;
    }
}
    if (g==1){
        cout<<"Pagal ka norite ruosiuoti (1 - pagal varda, 2 - pagal pavarde, 3 - pagal galutini pazymi): "; 
        cin>>pasirinkimas;
        failoGeneravimas();
        failai(pasirinkimas,temp,lst1);
    }
    else if (g==2){
        cout<<"Pagal ka norite ruosiuoti (1 - pagal varda, 2 - pagal pavarde, 3 - pagal galutini pazymi): ";
        cin>>pasirinkimas;
        failai(pasirinkimas,temp,lst1);
    }
    else if(g==3){
    cout<<"Rezultatus ivesite ranka ar iš failo? (1 - ranka, 2 - failas): ";
    cin>>r;
    }
    else if(g==4){
    // bandymas sukurti zmogaus objekta
    // Zmogus zmogus1("Vardas", "Pavarde");    
    Student student1;
    cin >> student1; 
    cout << "Student info: " << student1 << endl;

    Student student2 = student1;
    cout << "Copied student (student2, using copy constructor): " << student2 << endl;

    Student student3;
    student3 = student1;
    cout << "Copied student (student3, using copy assignment): " << student3 << endl;

    }
    else{
        cout<<"Klaidingas pasirinkimas";
        return 0;
    }
    if (r==1 && g==3){ 
        cout<<"Pagal ka norite rusiuoti? (1 - vardas, 2 - pavarde): ";
        cin>>j;
        cout<<"Ka noresite skaiciuoti? (1 - vidurki, 2 - mediana):";
        cin>>c;
        cout<<"Keliu studentu duomenis ivesite? ";
        cin>>k;
        cout<<"Ar norite kad pazymiai butu sugeneruoti automatiskai? (1 - taip, 2 - ne): ";
        cin>>p;
        bool generate=(p==1);
        if (generate){
        cout<<"kiek namu darbu norite, kad butu sugeneruota? ";
        cin>>n;
        }
        for(int i=0;i<k;i++)
        {
            cout<<"Iveskite "<<i+1<<" studento duomenis "<<endl;
            temp.valymas();
            ivedimas(temp,generate);
            vector<int> randomND;
            if (generate) {
                for (int j=0; j<n; j++){
                    randomND.push_back(randomize(1,10));
                }
            temp.setND(randomND);
        } 
            else{
                temp.namu_darbai();
            }
            if (c == 1) {
            temp.vidurkis();
        } 
            else if (c == 2) {
            temp.mediana();
            }
            lst1.push_back(temp);

        }
        if (j==1){
            rusiavimasVardas(lst1);
        }
        else if (j==2){
            rusiavimasPavarde(lst1);
        }
     if (c==1) {
            cout << setw(10) << left << "Vardas" << setw(12) << left << "Pavardė" << setw(20) << left << "Galutinis (Vid.)"<<setw(15)<<left<< "Saugojimo ad.";
            cout<<"\n---------------------------------------------------------\n";

            for(list<Student>::iterator it=lst1.begin();it!=lst1.end();it++)
                outputVID(*it);
    } else if (c==2) {
            cout << setw(10) << left << "Vardas" << setw(10) << left << "Pavardė" << setw(20) << left << "Galutinis (Med.)"<<setw(15)<<left<< "Saugojimo ad.";
            cout<<"\n--------------------------------------------\n";
            for(list<Student>::iterator it=lst1.begin();it!=lst1.end();it++)
                outputMED(*it);
    } 
    else {
            cout<<"Klaidingas pasirinkimas";
            return 0;
    }
    } 

    cout << "Press Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    return 0;
}