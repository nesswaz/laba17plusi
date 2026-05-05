#include "h17.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <limits>

void TreeOriginal::InputFromKeyboard() {
    clear();
    std::cout << "Введите префиксное выражение (например + 5 * 2 3): " << std::endl;
    FileInput(root, std::cin);
    std::cout << "Заполнение выполнено успешно\n";
}

void TreeOriginal::InputFromFile(char const* filename) {
    clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }
    FileInput(root, file);
    file.close();
    std::cout << "Данные успешно считаны из файла\n";
}

void TreeOriginal::InputFromRandom(int n) {
    clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    RandomInput(root, n);
    std::cout << "Заполнение выполнено успешно\n";
}


void CalcTree7(TreeOriginal &tree) {
    if (tree.isEmpty()) { return;}
    std::cout << "Исходное дерево: \n";
    tree.print();

    tree.Calc();
    std::cout << "Указатель на корень: " << tree.getRoot() << std::endl;
    
    std::cout << "Результат: \n";
    tree.print();
}

//---------------------------------------------------------------------------------



void TreeOriginal::InputFromKeyboard2() {
    clear();
    std::cout << "Введите выражение например ((x+5)*2): " << std::endl;
    std::string expr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, expr);
     if (expr.empty()) {
        std::cout << "Ошибка: введена пустая строка!" << std::endl;
    } else {
        AnalysisStr(expr);
        std::cout << "Ввод успешно записан" << std::endl;
    }
}

void TreeOriginal::InputFromFile2(const char* filename) {
    clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }
    std::string line, fullExpr = "";
    while (std::getline(file, line)) fullExpr += line + " ";
    AnalysisStr(fullExpr);
    file.close();
    std::cout << "Ввод успешно записан\n";
}

void TreeOriginal::InputFromRandom2(int n) { 
    clear();
    std::srand((unsigned int)std::time(0));
    RandomInput2(root, n);
    std::cout << "Ввод успешно записан\n";
}

void TreeOriginal::CalcTree25(int x, const char* outF) {
        std::ofstream fout(outF);
        fout << "Результат при x=" << x << ": " << Calcul(root, x) << "\n\n";
        fout << "До: \n";
        Print2(root, 0, fout);

        WithoutX(root);

        fout << "После: \n";
        Print2(root, 0, fout);
        fout.close();
        std::cout << "Ответ успешно записан в файл\n";
}

