
#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED
#include "mylib.h"
class Zmogus
{
protected:
    std::string vardas_;
    std::string pavarde_;
public:
    Zmogus() : vardas_(""), pavarde_("") {}
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() {}

    virtual std::string vardas() const { return vardas_; }
    virtual std::string pavarde() const { return pavarde_; }
    virtual void printInfo(std::ostream& os) const = 0;
};
class Student : public Zmogus
{
private:
    std::vector<int> ND;
    int egz;
    double med,vid;

public:
    Student() : Zmogus(), egz(0), med(0.0),vid(0.0) {}
    Student(std::ifstream& file);
    ~Student() {}

Student(const string& vardas, const string& pavarde, int egz, const vector<int>& ND)
        : Zmogus(vardas,pavarde), ND(ND), egz(egz), vid(0.0), med(0.0) {

    }


    Student(const Student &other)
        : Zmogus(other.vardas_,other.pavarde_), ND(other.ND), egz(other.egz), vid(other.vid){}

    Student& operator=(const Student &other)
    {
        if (this != &other)
        {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            ND = other.ND;
            egz = other.egz;
            vid = other.vid;
            med = other.med;
        }
        return *this;
    }

    void printInfo(std::ostream& os) const override
    {
        os << std::setw(16) << std::left << vardas_
           << std::setw(16) << std::left << pavarde_
           << std::setw(10) << std::left << vid;
    }
    void skaiciuotiVidurki(){
        double sum = 0;
        for (int i = 0; i < ND.size(); i++) {
            sum += ND[i];
        }
        vid = (sum / ND.size() + egz) / 2.0;
    }
    friend std::istream& operator>>(std::istream& is, Student& stud)
    {
        cout << "Iveskite studento varda ir pavarde: ";
        std::string vardas, pavarde;
        is >> vardas >> pavarde;
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        cout<<"Iveskite egzamino pazymi: ";
        is>>stud.egz;
        cout<<"Iveskite namu darbu skaiciu"<<endl;
        int n;
        is>>n;
        stud.ND.clear();
        cout<<"Iveskite namu darbu pazymius"<<endl;

        double sum = 0;
        for (int i=0; i<n; i++){
            int pazymys;
            is>>pazymys;
            stud.ND.push_back(pazymys);
            sum+=pazymys;
        }
        if (n > 0) {
            stud.vid = (sum / n + stud.egz) / 2.0;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& stud)
    {
        stud.printInfo(os);
        return os;
    }

    inline double getVid() const { return vid; }
    inline double getMed() const { return med; }
    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }  
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    inline void setEgz(int egzaminas) { egz = egzaminas; }
    inline void setND(std::vector<int> pazymiai) { ND=pazymiai;}
    inline const std::vector<int>& getND() const { return ND; }

    static bool compareByName(const Student &a, const Student &b) {
    return a.vardas_ < b.vardas_;
    }
    static bool compareByLastName(const Student &a, const Student &b) {
    return a.pavarde_ < b.pavarde_;
    }
    static bool compareByAverage(const Student &a, const Student &b) {
    return a.getVid() > b.getVid();
    }       

    void valymas();
    void namu_darbai();
    void skaitymas(std::ifstream &file);
    void vidurkis();
    double mediana();
    double medSK(std::vector<int> paz);
    
};
class ChronoTimer {
public:
    ChronoTimer() : start_time(std::chrono::high_resolution_clock::now()) {}

    double getElapsedTime() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};
void ivedimas(Student &lok, bool generate); 
void outputVID(const Student &lok);
void valymas();
void vidurkis();
double mediana();
void namu_darbai();
void skaitymas(std::ifstream &file);
int randomize(int min, int max);
void output2(const Student &lok);
void rusiavimas(std::list<Student> &lst1);
bool compare(const Student &a, const Student &b);
bool tikrinam(string &fileName);
void outputMED(const Student &lok);
void rusiavimasPavarde(std::list<Student> &lst1);
void rusiavimasVardas(std::list<Student> &lst1);
void failoGeneravimas();
vector<int> generavimas(int pazymiuSk);
void skirstymas(std::list<Student> &lst1, std::list<Student> &vargsiukai);
void IsvedimasV(const std::list<Student> &vargsiukai);
void IsvedimasK(const std::list<Student> &lst1);
void failai(int pasirinkimas, Student &temp, std::list<Student> &lst1);
void rusiavimasVidurkis(std::list<Student> &list1);
bool compareByAverage(const Student &a, const Student &b);
double medSK(std::vector<int> paz);

#endif // STUD_H_INCLUDED
