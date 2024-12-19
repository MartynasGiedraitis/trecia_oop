#include "studentas.h"
#include "mylib.h"

Student::Student(std::ifstream &file)
{
    skaitymas(file);
}
void ivedimas(Student &stud, bool generate)
{
  cin>>stud;
  if(!generate){
    string egz;
    while(true){
    cout<<"Iveskite egzamino pazymi: ";
    cin>>egz;
    try{
      int Egz=stoi(egz);
      if (Egz>0 && Egz<=10){
        stud.setEgz(Egz);
        break;
    } else{
        cout<<"Ivestas egzamino pazymys turi buti intervale nuo 1 iki 10"<<endl;
      }
    } catch (const invalid_argument&) {
      cout<<"Ivestas ne skaicius. Bandykite dar karta"<<endl;
        }
    }
    cin.ignore();
  } 
  else{
    stud.setEgz(randomize(1,10));
  }
}
void outputVID(const Student& stud)
{
  cout<<setw(10)<<left<<stud.vardas()<<setw(13)<<left<<stud.pavarde()<<setw(20)<<left<<fixed<<setprecision(2)<<stud.getVid()<<endl;
}
void outputMED(const Student& stud)
{
 cout<<setw(10)<<left<<stud.vardas()<<setw(13)<<left<<stud.pavarde()<<setw(20)<<left<<fixed<<setprecision(2)<<stud.getMed()<<endl;
}
void output2(const Student& stud)
{
  cout<<setw(10)<<left<<stud.vardas()<<setw(13)<<left<<stud.pavarde()<<setw(20)<<left<<fixed
  <<setprecision(2)<<stud.getVid()<<setw(20)<<left<<fixed<<setprecision(2)<<stud.getMed()<<endl;
}
void Student::valymas(){
    vardas_.clear();  
    pavarde_.clear();
    egz=0;
    ND.clear();
    med=0.0;
    vid=0.0;
}
void Student::vidurkis()
{
    double sum=0;
    for (int pazymys:ND){
        sum+=pazymys;
    }
    double rez=sum/ND.size();
    double finalrez=rez*0.4+egz*0.6;
    vid=round(finalrez*100)/100;
    
}
double Student::mediana()
{   
    double Mediana=medSK(ND);
    med=Mediana*0.4+egz*0.6;
    return med;
}
double Student::medSK(std::vector<int> paz){
    if (paz.empty())
        return 0;
    std::sort(paz.begin(),paz.end());
    size_t n=paz.size();
    return n%2==0 ? (paz[n/2-1]+paz[n/2])/2.0 : paz[n/2];
}
void Student::namu_darbai()
{   
    int counter=1;
    cout<<"Iveskite namu darbu pazymius"<<endl;
    while(true){
        cout<<"Iveskite "<<counter<<" pazymi arba spauskite Enter, jei daugiau pazymiu nera: ";
        string input;
        getline(cin,input);
        if(input.empty())
            break;
        try{
            int temp1=stoi(input);
            if (temp1>0 && temp1<=10){
                ND.push_back(temp1);
                counter++;
            } else{
                cout<<"Ivestas pazymys turi buti intervale nuo 1 iki 10. Bandykite dar karta"<<endl;
            }
        } catch (...) {
            cout<<"Ivestas ne skaicius, pataisykite įvedimą"<<endl;
        }
    }
}
std::random_device rd;
std::mt19937 gen(rd());
int randomize(int min, int max){
    std::uniform_int_distribution<> distrib (min,max);
    return distrib(gen);
}
void Student::skaitymas(std::ifstream &file)
{    
    string line;
    getline(file, line);
    if (line.empty())
        return;
    std::istringstream iss(line);
    iss>>vardas_>>pavarde_;
    ND.clear();
    int pazymys;
    while (iss >> pazymys){
        ND.push_back(pazymys);
    }
    if(!ND.empty()){
       egz=ND.back();
       ND.pop_back();
    }
    else{
        egz=0;
    }
}

void rusiavimasVardas(list<Student> &lst1){
    lst1.sort(Student::compareByName);
}
void rusiavimasPavarde(list<Student> &lst1){
    lst1.sort(Student::compareByLastName);
}
void rusiavimasVidurkis(list<Student> &lst1){
    lst1.sort(Student::compareByAverage);
}

bool tikrinam(string & fileName){
    ifstream inFile(fileName.c_str());
    if(!inFile){
        cout<<"Failas nerastas";
        return false;
    }
    return true;
}
void IsvedimasV(const list <Student>& vargsiukai){
    ofstream Vargsiukai("vargsiukai.txt");
    Vargsiukai<<setw(16)<<left<<"Vardas"<<setw(16)<<left<<"Pavarde"<<setw(10)<<left<<"Galutinis (Vid.)";
    Vargsiukai<<"\n------------------------------------------------------------\n";
    for (const Student &stud:vargsiukai){
        Vargsiukai<<stud<<endl;
    }
    Vargsiukai.close();

}
void IsvedimasK(const list <Student>& kietiakai){
    ofstream Kietiakai("Kietiakai.txt");
    Kietiakai<<setw(16)<<left<<"Vardas"<<setw(16)<<left<<"Pavarde"<<setw(10)<<left<<"Galutinis (Vid.)";
    Kietiakai<<"\n------------------------------------------------------------\n";
     for (const Student &stud:kietiakai){
        Kietiakai<<stud<<endl;
    }
    Kietiakai.close();

}
void failoGeneravimas(){
    const int studentuSk[]={1000, 10000, 100000, 1000000, 10000000};
    for (int studentuSkaicius:studentuSk){
        string fileName=to_string(studentuSkaicius)+"studentu.txt";
        ChronoTimer timerGen;
        ofstream outFile(fileName);
        if (!outFile){
            cout<<"Failas nerastas"<<fileName<<endl;
            return;
    }
    outFile<<setw(16)<<left<<"Vardas"<<setw(16)<<left<<"Pavarde";
    for (int i=1; i<=5; i++){
        outFile<<setw(5)<<left<<"ND"+to_string(i);
    }
    outFile<<setw(5)<<left<<"Egz."<<endl;
    for (int i=1; i<=studentuSkaicius; i++){
        string vardas="Vardas"+to_string(i);
        string pavarde="Pavarde"+to_string(i);
        outFile<<setw(16)<<left<<vardas<<setw(16)<<left<<pavarde;
        vector<int> pazymiai=generavimas(6);
        for (int pazymys:pazymiai){
            outFile<<setw(5)<<left<<pazymys;
        }
        outFile<<"\n";
    }
    outFile.close();
    cout<<"Sukurtas failas: "<<fileName<<", per: "<<timerGen.getElapsedTime()<<"s"<<endl;
    }

}
vector<int> generavimas(int pazymiuSk){
    vector<int> pazymiai;
    for(int i=0; i<pazymiuSk; i++){
        pazymiai.push_back(randomize(1,10));
    }
    return pazymiai;
}
void skirstymas(list<Student> &lst1, list<Student> &vargsiukai){
    for(list<Student>::iterator it=lst1.begin(); it!=lst1.end();){
        if (it->getVid()<5){
            vargsiukai.push_back(std::move(*it));
            it=lst1.erase(it);
        } else{
            it++;
        }
    }
}
void failai(int pasirinkimas,Student &stud, list<Student> &lst1){
    const int studentuSk[]={1000, 10000, 100000, 1000000, 10000000};
    ChronoTimer bendrasTimer;
    for (int studentuSkaicius:studentuSk){
        string fileName=to_string(studentuSkaicius)+"studentu.txt";
        cout<<"Failas: "<<fileName<<endl;
        ChronoTimer nuskaitymasTimer;
       ifstream inFile(fileName);
       if (!inFile){
           cout<<"Failas nerastas"<<fileName<<endl;
           return;
       }
       string pirma;
       getline(inFile,pirma);
       Student temp;
       while(!inFile.eof()){
          temp.skaitymas(inFile);
          if (inFile.eof())
              break;
          temp.vidurkis();
          lst1.push_back(temp); 
       }
       inFile.close();
       cout<<"Failo nuskaitymo ir vidurkio skaciavimo laikas: "<<nuskaitymasTimer.getElapsedTime()<<"s"<<endl;
       list<Student> vargsiukai, kietiakai;
       ChronoTimer skirstymasTimer;
       skirstymas(lst1,vargsiukai);
       cout<<"Studentu skirstymo i dvi grupes laikas: "<<skirstymasTimer.getElapsedTime()<<"s"<<endl;
       ChronoTimer sortinimoTimer;
       if (pasirinkimas ==1){
           rusiavimasVardas(vargsiukai);
           rusiavimasVardas(lst1);
       } else if (pasirinkimas==2){
           rusiavimasPavarde(vargsiukai);
           rusiavimasPavarde(lst1);
       }
       else if (pasirinkimas==3){
           rusiavimasVidurkis(vargsiukai);
           rusiavimasVidurkis(lst1);
       }
       cout<<"Studentu rusiavimo laikas: "<<sortinimoTimer.getElapsedTime()<<"s"<<endl;
       ChronoTimer isvedimasVTimer;
       IsvedimasV(vargsiukai);
       cout<<"Vargsiuku isvedimo laikas: "<<isvedimasVTimer.getElapsedTime()<<"s"<<endl;

       ChronoTimer isvedimasKTimer;
       IsvedimasK(lst1);
       cout<<"Kietiaku isvedimo laikas: "<<isvedimasKTimer.getElapsedTime()<<"s"<<endl;
       cout<<studentuSkaicius<<" studentu failo apdorojimo laikas: "<<bendrasTimer.getElapsedTime()<<"s"<<endl;
       lst1.clear();
       cout<<endl;
       }
    
}