//Tema 1
//Realizata cu:
// gcc (GCC) 14.2.1 20240910



#define MARIME_PRODUCATOR 64

#include <iostream>
#include <cstring>
using std::cout;
using std::ostream;
class Autobuz{
    private:
        inline static int nrAutobuze = 0;
        const int idAutobuz;
        int capacitate;
        int nrPersoaneImbarcate;
        char *producator;
    public: 
        //pentru a reprezenta valorile numerice necunoscute folosim -1, si pentru pointer folosim 0
        Autobuz(int capacitate, int nrPersoaneImbarcate, char *producator):idAutobuz(nrAutobuze) {
            //tipul transmite toate validarile esuate printr-un cod
            int exception_type = 0;
            if(capacitate < -1)
                exception_type += 1;
            else
                this->capacitate = capacitate;
            if(nrPersoaneImbarcate < -1)
                exception_type += 2;
            else{
                if(nrPersoaneImbarcate > capacitate && !exception_type)
                    exception_type += 2;
                else
                    this->nrPersoaneImbarcate = nrPersoaneImbarcate;
            }            
            if(producator){
                exception_type += 4;
                if(strlen(producator) <= MARIME_PRODUCATOR)
                    for(int i = 0; producator[i] != 0; i++){
                        if(!std::isspace(producator[i])){
                            exception_type -= 4;
                            this->producator = new char[MARIME_PRODUCATOR];
                            strcpy(this->producator, producator);
                            break;
                        }
                    }                
            }else
                this->producator = producator;
            if(exception_type > 0)
                throw exception_type;
            nrAutobuze++;
        }  

        Autobuz():idAutobuz(nrAutobuze++){
            this->capacitate = -1;
            this->nrPersoaneImbarcate = -1;
            this->producator = 0;
        }

        Autobuz(Autobuz &autobuz):idAutobuz(nrAutobuze){
            capacitate = autobuz.capacitate;
            nrPersoaneImbarcate = autobuz.nrPersoaneImbarcate;
            producator = new char[MARIME_PRODUCATOR];
            strcpy(producator, autobuz.producator);
            nrAutobuze++;
        }


        ~Autobuz(){
            delete[] producator;
        }

        Autobuz operator=(const Autobuz &autobuz){
            if(idAutobuz == autobuz.idAutobuz)
                return *this;
            capacitate = autobuz.capacitate;
            nrPersoaneImbarcate = autobuz.nrPersoaneImbarcate;
            if(producator)
                delete[] producator;
            producator = new char[MARIME_PRODUCATOR];
            strcpy(producator, autobuz.producator);
            return *this;
        }

        friend ostream& operator<<(ostream& os, const Autobuz *autobuz){
            os<<autobuz->idAutobuz<<"; "<<autobuz->capacitate<<"; "<<autobuz->nrPersoaneImbarcate<<"; "<<autobuz->producator;
            return os;
        }
        
        friend bool operator> (const Autobuz& a1, const Autobuz& a2){
            return a1.capacitate > a2.capacitate;
        }

        operator int(){
            return nrPersoaneImbarcate;
        }


        int getNumarLocuriLibere(){
            return capacitate - nrPersoaneImbarcate;
        }

        void display(){
            cout<<"idAutobuz: "<<idAutobuz<<"\r\n";\
            cout<<"capacitate: "<<capacitate<<"\r\n";
            cout<<"nrPersoaneImbarcate: "<<nrPersoaneImbarcate<<"\r\n";
            if(producator)
                cout<<"producator: "<<producator<<"\r\n";
            else
                cout<<"producator: "<<0<<"\r\n";
        }

        //am adaugat mai multe metode de get si set pentru constructorul de copiere
        int getId(){
            return idAutobuz;
        }

        void setProducator(int capacitate){
            this->producator = producator;
        }

        void setCapacitate(int capacitate){
            this->capacitate = capacitate;
        }

        void setNrPersoaneImbarcate(int nrPersoaneImbarcate){
            this->nrPersoaneImbarcate = nrPersoaneImbarcate;
        }

        char* getProducator(){
            return this->producator;
        }

        int getCapacitate(){
            return this->capacitate;
        }

        int getNrPersoaneImbarcate(){
            return this->capacitate;
        }
};



//int Autobuz::nrAutobuze = 0;

void displayConstructorError(int type){
    if(type){
        cout<<"Erori de validare:\r\n";
        if(type >= 4){
            cout<<"producator invalid\r\n";
            type -= 4;
        } 
        if(type >= 2){
            cout<<"nrPersoaneImbarcate invalid\r\n";
            type -= 2;
        } 
        if(type){
            cout<<"capacitate invalida\r\n";
        } 
    }
}

void testConstructor(int capacitate, int nrPersoaneImbarcate, char *producator){
    cout<<"capacitate="<<capacitate<<";nrPersoaneImbarcate="<<nrPersoaneImbarcate<<";producator=";
    if(producator)
        cout<<producator;
    else
        cout<<0;
    cout<<"\r\n";
    try{
        Autobuz *autobuz = new Autobuz(capacitate, nrPersoaneImbarcate, producator);
        cout<<"Fara erori\r\n";
        delete autobuz;
    } catch (int type){
        displayConstructorError(type);
    }

}
 


int main(){
    //test validare 
    
    testConstructor(5, 50 , 0);
    cout<<"\r\n";
    testConstructor(-3, 1, "Mercedes");
    cout<<"\r\n";
    testConstructor(-3, 1, 0);
    cout<<"\r\n";
    testConstructor(19, 25, "  ");
    cout<<"\r\n";
    testConstructor(25, 25, "BMC Truck&Bus");

    cout<<"\r\n----------------------------------------\r\n";
    
    cout<<"test constructor de copiere si metode get\r\n";
    {
        Autobuz *autobuz1 = new Autobuz(2, 1, "Ikarus");
        Autobuz *autobuz2 = new Autobuz(*autobuz1);
        autobuz1->display();
        cout<<"\r\n"; 
        autobuz2->display();
        delete autobuz1;
        delete autobuz2;
    }
    cout<<"\r\n----------------------------------------\r\n";
    cout<<"testare operator<< (nu am inteles daca operatorul ar trebui sa afiseze sau daca ar trebui folosit pentru afisare asa ca am mers pe a doua varianta)\r\n";
    {
        Autobuz *autobuz1 = new Autobuz(2, 1, "Ikarus");
        Autobuz *autobuz2 = new Autobuz(5, 1, "Mercedes");
        cout<<autobuz1<<"\r\n";
        cout<<autobuz2<<"\r\n";
        delete autobuz1;
        delete autobuz2;
    }

    cout<<"\r\n----------------------------------------\r\n";
    cout<<"testare getNumarLocuriLibere()\r\n";
    {
        Autobuz *autobuz = new Autobuz(5, 1, "Mercedes");
        cout<<"Nr locuri libere: "<<autobuz->getNumarLocuriLibere()<<"\r\n";;
        delete autobuz;
    }
    cout<<"\r\n----------------------------------------\r\n";
    cout<<"test operator cast int\r\n";
    {
        Autobuz *autobuz = new Autobuz(5, 1, "Mercedes");
        cout<<(int) *autobuz<<"\r\n";
        cout<<0 + *autobuz<<"\r\n";

        delete autobuz;
    }
    cout<<"\r\n----------------------------------------\r\n";
    cout<<"test operator>\r\n";
    {
        Autobuz *autobuz1 = new Autobuz(2, 1, "Ikarus");
        Autobuz *autobuz2 = new Autobuz(5, 1, "Mercedes");
        cout<<"autobuz2>autobuz1: "<<(autobuz2>autobuz1 ? "adev" : "fals")<<"\r\n";
        cout<<"autobuz1>autobuz2: "<<(autobuz1>autobuz2 ? "adev" : "fals")<<"\r\n";
        delete autobuz1;
        delete autobuz2;
    }

    

    
    return 0;
}