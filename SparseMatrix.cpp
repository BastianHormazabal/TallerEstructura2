#include <iostream>
#include <cstdlib>
#include "SparseMatrix.h"

using namespace std;

SparseMatrix::SparseMatrix(){
    start = nullptr;

}

static int compararPos(int x1, int y1, int x2, int y2){
    if (x1 < x2) return -1;
    if (x1 > x2) return 1;
    if (y1 < y2) return -1;
    if (y1 > y2) return 1;
    return 0;
    
}

static Node* buscarPrevio(Node* inicio, int x, int y){
    Node* previo = nullptr;
    Node* actual = inicio;
    while (actual != nullptr){
        int cmp = compararPos(actual->x, actual->y, x, y);
        if (cmp >= 0) break;
        previo = actual;
        actual = actual->next;

    }
    return previo;
}

static void insertarDespues(Node*& inicio, Node* previo , Node* nuevo){
    if (previo == nullptr) {
        nuevo->next = inicio;
        inicio = nuevo;

    }
    else{
        nuevo->next = previo->next;
        previo->next = nuevo;
    }
}

static void recalcularExtremos(Node* inicio, int& maxX, int& maxY){
    maxX = -1;
    maxY = -1;
    Node* actual = inicio;
    while (actual != nullptr){
        if (actual->x > maxX) maxX = actual->x;
        if (actual->y > maxY) maxY = actual->y;
        actual = actual->next;

    }

}

// metodos principales 

void SparseMatrix::add(int value, int xPos, int yPos){
    if (xPos < 0 || yPos < 0){
        cout << "Error coordenadas invalidas.\n";

    }

    if (value == 0){
        remove(xPos, yPos);
        return;
    }

    Node* previo = buscarPrevio(start, xPos, yPos);
    Node* actual = (previo == nullptr) ? start : previo->next;

    if (actual && actual->x == xPos && actual->y == yPos){
        actual->value = value; //actualizar

    } else {
        Node* nuevo = new Node(xPos, yPos, value);
        insertarDespues(start, previo, nuevo);
    }

}

int SparseMatrix::get(int xPos, int yPos){
    Node* previo = buscarPrevio(start, xPos, yPos);
    Node* actual = (previo == nullptr) ? start : previo->next;
    if (actual && actual->x == xPos && actual->y == yPos) return actual->value;
    return 0;

}

void SparseMatrix::remove(int xPos, int yPos) {
    Node* previo = buscarPrevio(start, xPos, yPos);
    Node* actual = (previo == nullptr) ? start : previo->next;

    if (actual && actual->x == xPos && actual->y == yPos) {
        if (previo == nullptr) start == actual->next;
        else previo->next = actual->next;
        delete actual;

    }
}

void SparseMatrix::printStoredValues(){
    if (start == nullptr) {
        cout << "Matriz vacia\n";
        return;

    }

    cout << "Elementos almacenados (x , y) --> valor\n";
    Node* actual = start;
    while (actual != nullptr){
        cout << "(" << actual->x << ", " << actual->y << ") --> " << actual->value << "\n";
        actual = actual->next;

    }
}

int SparseMatrix::density(){
    if (start == nullptr) return 0;
    
    int maxX = -1, maxY = -1;
    int count = 0;

    Node* actual = start;
    while (actual != nullptr){
        count++;
        if (actual->x > maxX) maxX = actual->x;
        if (actual->y > maxY) maxY = actual->y;
        actual = actual->next;

    }
    
    long long total = (long long)(maxX + 1) * (long long)(maxY + 1);
    if (total == 0) return 0 ;
    int dens = (int)((count * 100LL) / total);
    return dens;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second){
    if (second == nullptr) return nullptr;

    SparseMatrix* C = new SparseMatrix();

    for (Node* a = this->start; a != nullptr; a = a->next){
        for (Node* b = second->start; b != nullptr; b = b->next){
            if (a->y == b->x){
                int i = a->x;
                int j = b->y;
                int ValorPrevio = C->get(i,j);
                C->add(ValorPrevio + a->value * b->value, i, j);
            }
        }
    }
    return C;
}

SparseMatrix::~SparseMatrix(){
    Node* actual = start;
    while (actual != nullptr){
        Node* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
}

