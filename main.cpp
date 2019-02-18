#include <iostream>
#include <cmath>
#include <thread>

using namespace std;

void f(){
    cout << "Hej, tu watek!";
}

double modul(double var1,double var2){
    return sqrt(pow(var1,2)+pow(var2,2));
}

int mendelbrot(int N, double a, double ib){
    int i=0;
    double var1,var2,tmp1,tmp2;
    var1 = 0;
    var2 = 0;
    int bl = 1;
    while(i<=N){
        if(modul(var1,var2)>=2){
            bl = -1;
            break;
        }
        tmp1 = pow(var1,2)-pow(var2,2);
        tmp2 = 2*var1*var2;
        var1=tmp1+a;
        var2=tmp2+ib;
        i++;
    }
    return bl;
}

void punkty(int P, double a1, double b1, double a2, double b2, string nazwa){
    int i,j;
    double odlg1,odlg2;
    //a1 = -2;
    //b1 = 0.5;
    //a2 = -1.25;
    //b2 = 1.25;
    odlg1 = abs(a1-b1)/P;
    odlg2 = abs(a2-b2)/P;
    const char * c = nazwa.c_str();
    FILE *plik = fopen(c, "w");
    if(plik == NULL){
        cout << "\nNie udalo sie otworzyc pliku!";
    }
    else{
    for(i=0;i<=P;i++){
        for(j=0;j<=P;j++){
            if(mendelbrot(50,a1+i*odlg1,a2+j*odlg2)==1){
                fprintf(plik, "%lf ", a1+i*odlg1);
                fprintf(plik, "%lf\n", a2+j*odlg2);
            }
        }
    }
    }
    fclose(plik);
}

int main()
{
    thread t1 (punkty,10000, -2, -0.75, -1.25, 0, "wynik1.pt");
    thread t2 (punkty,10000, -0.75, 0.5, 0, 1.25, "wynik2.pt");
    thread t3 (punkty,10000, -2, -0.75, 0, 1.25, "wynik3.pt");
    thread t4 (punkty,10000, -0.75, 0.5, -1.25, 0, "wynik4.pt");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
