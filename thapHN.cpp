#include <iostream>
using namespace std;

void move(int n, char a, char b) {
    cout << "move disk " << n << " from " << a << " to " << b << endl;
}

void hanoiTower(int n, char a, char b, char c) {
    if (n == 1) {
        move(1, a, c);
    }
    else {
        hanoiTower(n-1, a, c, b);
        move(n, a, c);
        hanoiTower(n-1, b, a, c);
    }
}

int main() {
    int n;
    cout << "Enter numbers of disk: " << endl;
    cin >> n;
   
    hanoiTower(n, 'a', 'b', 'c');
}