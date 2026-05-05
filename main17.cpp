#include <iostream>
#include "h17.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <limits>
#ifdef _WIN64
#include <windows.h>
#endif

int main() {
    using namespace std;
    #ifdef _WIN64
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    #endif
    int choice;
    TreeOriginal tree;
    do {
        cout << "1. CalcTree7" << endl;
        cout << "2. CalcTree25" << endl;
        cout << "0. Выход" << endl;
        // choice = Check::getNumb("Выберите: ");
        cout << "Выберите: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int choice1;
                do {
                    cout << "\n1. Заполнение с клавиатуры" << endl;
                    cout << "2. Заполнение на рандом" << endl;
                    cout << "3. Заполнение из файла" << endl;
                    cout << "4. Показать дерево" << endl;
                    cout << "5. CalcTree7" << endl;
                    cout << "0. Выход" << endl;
                    cout << "Выберите: ";
                    cin >> choice1;
                    switch (choice1) {
                    case 1: {
                            tree.InputFromKeyboard();
                        break;
                        }
                        case 2: {
                            tree.InputFromRandom(3);
                            break;
                        }
                        case 3: {
                            tree.InputFromFile("b.txt");
                            break;
                        } 
                        case 4: {
                            tree.print();
                            break;
                        }
                        case 5: {
                            CalcTree7(tree);
                            break;
                        }
                        case 0: {
                            cout << "Выход из программы\n\n";
                            break;
                        }
                    }
                } while (choice1 != 0); 
                break;
            }
            case 2: {
                int choice2;
                do {
                    cout << "\n1. Заполнение с клавиатуры" << endl;
                    cout << "2. Заполнение на рандом" << endl;
                    cout << "3. Заполнение из файла" << endl;
                    cout << "4. Показать дерево" << endl;
                    cout << "5. CalcTree25" << endl;
                    cout << "0. Выход" << endl;
                    cout << "Выберите: ";
                    cin >> choice2;
                    switch (choice2) {
                    case 1: {
                            tree.InputFromKeyboard2();
                        break;
                        }
                        case 2: {
                            tree.InputFromRandom2(3);
                            break;
                        }
                        case 3: {
                            tree.InputFromFile2("b.txt");
                            break;
                        } 
                        case 4: {
                            tree.print2();
                            break;
                        }
                        case 5: {
                            int x = Check::getNumb("Введите значение x: ");
                            tree.CalcTree25(x, "a.txt");
                            break;
                        }
                        case 0: {
                            cout << "Выход из программы\n\n";
                            break;
                        }
                    }
                } while (choice2 != 0); 
                break;
            }
            case 0: {
                cout << "Выход из программы\n";
                break;
            }
            default:
                cout << "Введено неверное значение\n";
        }
    } 
    while (choice != 0);
    return 0;
}