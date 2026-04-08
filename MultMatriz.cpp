#include<iostream>
#include<thread>
#include<chrono>
#include<fstream> // 1. Librería necesaria para archivos

using namespace std;

const int N=3; 

long int arrA[N][N];
long int arrB[N][N];
long int arrC[N][N];

void multiplicarFila(int i){
    for(int j=0; j<N; j++){
        arrC[i][j]=0;
        for(int k=0; k<N; k++){
            arrC[i][j]+=arrA[i][k]*arrB[k][j];
        }
    }
}

// ... (tus funciones pedirDatos y mostrarMatriz se mantienen igual)

void pedirDatosMatrizA(){
    cout<<"Digite los numeros de la primera matriz:\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>arrA[i][j];
        }
    }
}

void pedirDatosMatrizB(){
    cout<<"Digite los numeros de la segunda matriz:\n"; // Corregido el texto
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>arrB[i][j];
        }
    }
}

void mostrarMatrizC(){
    cout<<"La matriz resultante es:\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<arrC[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    pedirDatosMatrizA();
    pedirDatosMatrizB();
    
    auto inicio = chrono::high_resolution_clock::now();
    
    thread hilos[N]; 
    
    for(int i=0; i<N; i++){
        hilos[i]=thread(multiplicarFila,i);
    }
    
    for(int i=0; i<N; i++){
        hilos[i].join();
    }
    
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    
    // --- NUEVA SECCIÓN: VOLCADO A TXT ---
    ofstream archivo;
    // Abrimos en modo "app" para que no borre los tiempos anteriores
    archivo.open("tiempos_ejecucion.txt", ios::app);
    
    if(archivo.is_open()){
        archivo << "Matriz " << N << "x" << N << " | ";
        archivo << "Tiempo: " << duracion.count() << " microsegundos" << endl;
        archivo.close();
        cout << "\n[Sistema] Tiempo guardado en 'tiempos_ejecucion.txt'" << endl;
    } else {
        cout << "\n[Error] No se pudo crear el archivo de registro" << endl;
    }
    // ------------------------------------

    cout<<"Tiempo de ejecucion: "<<duracion.count()<<" microsegundos"<<endl;
    
    mostrarMatrizC();
    
    return 0;
}