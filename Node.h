#pragma once

struct Node {
    int x;
    int y;
    int value;
    Node* next;
    Node(int vx, int vy, int vval) : x(vx) , y(vy), value(vval), next(nullptr){}

};

