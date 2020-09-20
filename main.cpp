
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

struct Vertex{

    float xk =0;
    float x = 0;
    float y =0;
    float x2 =0;
    float y2 = 0;
    float xy = 0;
};

class Calculo{

private:
   // vector<Vertex> v   ;
    bool flagN = true;
//---------------------- checa si esta vacio ----------

//.m=3
bool docVacio(ifstream& doc){

    if ( doc.peek() == ifstream::traits_type::eof() )
        {
          return true;
        }
    return false;
}
//------------------------------------------------------



public:
    string S;
    int contador =0;
    string tempxk = "";
    string tempx = "";
    string tempy = "";
    float x =0;
    float y=0;
    int n = 0;
    bool fcoma = false;
    vector<Vertex> v ;
    bool numeros = false;

    float B1(float sumxy, int N, float avx, float avy,  float sumx2  ){

        float parteArriba = sumxy -(N*avx*avy);
        float parteAbajo = sumx2 -(N*(avx*avx));
        float b1 = parteArriba/parteAbajo;

        return b1;
    }

    float B0(float avy,  float b1, float avx  ){
        float b0 = avy -(b1*avx);

        return b0;
    }

    float R(float sumx,  float sumy, float sumxy, float sumx2, float sumy2, int N  ){

       float parteArriba = (N *sumxy)-(sumx * sumy);
       float parteAbajoDer = (N*sumy2)-(sumy*sumy);
       float parteAbajoIzq =  (N*sumx2)-(sumx*sumx);
       float parteAbajo = parteAbajoDer * parteAbajoIzq;
       float parteAbajoRaiz =  sqrt(parteAbajo);
       float r = parteArriba/parteAbajoRaiz;


        return r;
    }

    float R2(float r  ){
        float r2 = r * r;
        return r2;
    }

    float Yk(float b0,  float b1, float xk  ){
        float yk = b0 +(b1*xk);
        return yk;
    }


    void xyk(ifstream& doc,string name){
        contador = 0 ;

        if(docVacio(doc)){
            cout<<"----------------------------------------------\n";
            cout<<"------- documento vacio o inexistente---------\n";
            cout<<"----------------------------------------------\n";
            exit(0);
        }

        while ( getline(doc, S) ) {
                   v.push_back({0, 0 ,0, 0,0,0});
            //getline(doc, S);
            v[contador].x = 0;
            v[contador].y = 0;
            tempx ="";
            tempy ="";
            n=0;

            if((S[n] == ',') || (S[n] == '.') || (S[n] == '0') || (S[n] == '1')|| (S[n] == '2')|| (S[n] == '3') || (S[n] == '4')|| (S[n] == '5')|| (S[n] == '6')|| (S[n] == '7')|| (S[n] == '8')|| (S[n] == '9')){
                numeros = true;

            }else{
                numeros = false;
            }
            if(!numeros){
                cout<<"---------------------------------------\n";
                cout<<"-----programa con input incorrecto-----\n";
                cout<<"---------------------------------------\n";
                exit(0);
            }
            else if(contador ==0){//------------------- sio es la primera linea va aguardar xk
                while( (S[n] == '0') || (S[n] == '1')|| (S[n] == '2')|| (S[n] == '3') || (S[n] == '4')|| (S[n] == '5')|| (S[n] == '6')|| (S[n] == '7')|| (S[n] == '8')|| (S[n] == '9')){
                    tempxk += S[n] ;
                    n++;
                }
            }else  {
                tempxk = "0" ;
                while((S[n] == ',') || (S[n] == '.') || (S[n] == '0') || (S[n] == '1')|| (S[n] == '2')|| (S[n] == '3') || (S[n] == '4')|| (S[n] == '5')|| (S[n] == '6')|| (S[n] == '7')|| (S[n] == '8')|| (S[n] == '9')){

                        if(S[n] == ',') { // -------checa si hay coma
                            fcoma = true;
                            n++;
                        }else if(fcoma) { //--------si hubo coma por el flag de fcoma, lo guarda en tempy y cada loop le va jhcaiendo un append del siguiente numero
                            tempy += S[n];
                            n++;
                        }
                        else{//-------------------- si no ha habido coma lo guarda en la string  tempx y cada loop le va jhcaiendo un append del siguiente numero
                            tempx += S[n] ;
                            n++;
                        }
                }

                fcoma =false;
                x =stof(tempx); // ---- convierte el string x a flotante y lo guarda en el vertice
                y= stof(tempy); // ---- convierte el string y a flotante y lo guarda en el vertice
                v[contador].x += x;
                v[contador].y += y;
                v[contador].x2 += (x*x);
                v[contador].y2 += (y*y);
                v[contador].xy += (x*y);
            }

            v[contador].xk += stof(tempxk);// --- convierte el estring tempxk flotante y lo guarda en el vertice
            contador ++;
        }
    }
};

class Respuesta{

    public:

        void resultados(int xk, float x, float y,int N ,float x2, float y2, float xy){

            if(xk != 0){
                cout << "N: " << N<< "\n";
                cout << "xk: " << xk<< "\n";
            }

            else{
                cout << "x: " << x<< ", ";
                cout << "y: " << y<< "\n";
                cout << "x2: " << x2<< ", ";
                cout << "y2: " << y2<< "\n";
                cout << "xy: " << xy<< "\n ";

            }

        }
        void sumatorias( float x, float y ,float x2, float y2, float xy){
                cout << "suma x: " << x<< ", ";
                cout << "suma y: " << y<< "\n";
                cout << "suma x2: " << x2<< ", ";
                cout << "suma y2: " << y2<< "\n";
                cout << "suma xy: " << xy<< "\n ";
        }

         void average( float sumx, float sumy ){
                cout << "average x: " << sumx<< "\n";
                cout << "average y: " << sumy<< "\n";
        }

           void calc( float b1, float b0, float r, float r2, float yk, float xk, float N){

                printf("N: %.0f \n", N);
                printf("xk: %.0f \n", xk);
                printf("r: %.5f \n", r);
                printf("r2: %.5f \n", r2);
                printf("b0: %.5f \n", b0);
                printf("b1: %.5f \n", b1);
                printf("yk: %.5f \n", yk);

        }
};

//.b=86

//.d=42

int main (){

string archivo;
cin >> archivo ;
vector<Vertex> r;
Calculo calculo;
Respuesta respuesta;
float sumx =0;
float sumy =0;
float sumx2 =0;
float sumy2 =0;
float sumxy =0;
float avx =0;
float avy = 0;
int N =0;
float b1 =0;
float b0=0;
float r1=0 ;
float r2=0 ;
float yk =0;
float xk =0;

ifstream doc(archivo);
int temp = 0;

calculo.xyk(doc,archivo);
N = calculo.contador -1;
xk= calculo.v[0].xk;

for(int i =0; i < calculo.contador; i++ ){

 //   respuesta.resultados(calculo.v[i].xk, calculo.v[i].x, calculo.v[i].y, N ,calculo.v[i].x2, calculo.v[i].y2, calculo.v[i].xy );
    sumx += calculo.v[i].x;
    sumx2 += calculo.v[i].x2;
    sumy += calculo.v[i].y;
    sumy2 += calculo.v[i].y2;
    sumxy += calculo.v[i].xy;

}
avx = sumx/N;
avy = sumy/N;
b1 = calculo.B1(sumxy,N,avx,avy,sumx2);
b0 = calculo.B0(avy,b1,avx);
r1 =calculo.R(sumx,sumy,sumxy,sumx2,sumy2,N);
r2 = calculo.R2(r1);
yk = calculo.Yk(b0, b1, xk);



//respuesta.sumatorias(sumx, sumy,sumx2, sumy2, sumxy);
//respuesta.average(avx,avy);
respuesta.calc(b1,b0, r1, r2,yk,xk,N);


}
