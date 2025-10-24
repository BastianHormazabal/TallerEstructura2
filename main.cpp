#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SparseMatrix.h"
#include "Timer.h"

using namespace std;

void llenarAleatorio(SparseMatrix& M, int cantidad, int maxX, int maxY, int minVal, int maxVal){
    int insertados = 0;
    while (insertados < cantidad) {
        int x = rand() % (maxX + 1);
        int y = rand() % (maxY + 1);
        if (M.get(x,y) == 0){
            int valor = minVal + rand() % (maxVal - minVal + 1);
            M.add(valor , x ,y);
            insertados++;
        }
    }
}

void pruebasTiempo(){
    ofstream archivo("tiempos.csv");
    archivo << "algoritmo,n_datos,densidad,tiempo_ms,dispositivo\n";

    int tamaños[5] = {50, 250, 500, 1000, 5000};
    const int muestras = 10;

    for (int i = 0; i < 5; i++){
        int n = tamaños[i];
        for (int densa = 0; densa < 2; ++densa){
            double totalTiempo = 0;
            for (int m = 0; m < muestras; ++m){
                SparseMatrix M;
                srand(1000 + m);
                Temporizador T;
                llenarAleatorio(M, n, densa ? n/2 : n*2, densa ? n/2 : n*2, 1 , 9);
                totalTiempo += T.milisegundos();

            }
            archivo << "insertar, " << n << "," << (densa ? "ALTA" : "BAJA") << "," << totalTiempo/muestras << ",PC_Test\n";

        }
    }
    archivo.close();
    cout << "archivo 'tiempos.csv' generado.\n";

}

int main(){
    SparseMatrix A, B;
    int op = -1;
    while (op != 0) {
        cout << "\n=== menu matriz dispersa ===\n";
        cout << "1) insertar en A\n2) obtener en A\n3) eliminar en A\n4)imprimir A\n";
        cout << "5) densidad A\n6) insertar en B\n7) multiplicar A*B\n8) pruebas de tiempo\n9)imprimir B\n0) salir\n";
        cout << "Opcion: ";
        cin >> op;

        if(op == 1){
            int x,y,v;
            cout << " ingrese posicion x: ";
            cin >> x;
            cout << " ingrese posicion y: ";
            cin >> y;
            cout << " ingrese valor (!= 0): ";
            cin >> v; 

            A.add(v,x,y);

        } else if (op == 2){
            int x, y;
            cout << " ingrese x: ";
            cin >> x;
            cout << " ingrese y: ";
            cin >> y;

            cout << "Valor: " << A.get(x,y) << endl;

        } else if (op == 3){
            int x,y;
            cout << " ingrese x: ";
            cin >> x;
            cout << " ingrese y: ";
            cin >> y;
            A.remove(x,y);

        } else if (op == 4) {
            A.printStoredValues();

        } else if (op == 5) {
            cout << "densidad: " << A.density() << "%\n";

        } else if (op == 6) { 
            int x,y,v;
            cout << " ingrese posicion x: ";
            cin >> x;
            cout << " ingrese posicion y: ";
            cin >> y;
            cout << " ingrese valor (!= 0): ";
            cin >> v; 
            B.add(v,x,y);

        } else if (op == 7) {
            SparseMatrix* C = A.multiply(&B);
            cout << "Matriz resultante: \n";
            C->printStoredValues();
            delete C;
        } else if (op == 8) { 
            pruebasTiempo();
        } else if (op == 9){
            B.printStoredValues();
            
        }

    }
    return 0;
}
//ola profe