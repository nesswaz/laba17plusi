#pragma once
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <stack>

class Node {
public:
    int key;
    Node *left, *right;
    // Node(int data = 0);
    bool isx; //2 для икса
    // Node(int data = 0) : key(data), left(nullptr), right(nullptr) {} //1
    Node(int data = 0, bool x = false) : key(data), left(nullptr), right(nullptr), isx(x) {} //2 изменили под вторую задачу, добавили логический тип для икса

};

class TreeOriginal {
private:
    Node* root;
    void ClearTree(Node*& node) {
        if (node) {
            ClearTree(node->left);
            ClearTree(node->right);
            delete node;
            node = nullptr;
        }
    }
    
    void FileInput(Node*& node, std::istream& in) {
        std::string str;
        if (!(in >> str)) return;
        int num = 0;
        if (str == "+") { //распределение операций по кодам
            num = -1;
        } 
        else if (str == "-") {
            num = -2;
        } 
        else if (str == "*") {
            num = -3;
        } 
        else if (str == "/") {
            num = -4;
        } 
        else if (str == "%") {
            num = -5;
        } 
        else if (str == "^") {
            num = -6;
        }
        if (num != 0) {
            node = new Node(num); //создаем узел для знака
            FileInput(node->left, in); //читаем левое число
            FileInput(node->right, in); //читаем правое
        } else { 
            node = new Node(std::stoi(str)); //если это не знак, то превращаем в число
        }
    }

    void RandomInput(Node*& node, int d) {
        if (d <= 0 || (std::rand() % 3 == 0)) {
            node = new Node(std::rand() % 10);
            return;
        }
        int codes[] = {-1, -2, -3, -4, -5, -6};
        node = new Node(codes[std::rand() % 6]);
        RandomInput(node->left, d - 1);
        RandomInput(node->right, d - 1);
    }

    void Print(Node* node, int h) {
        if (node) {
            Print(node->right, h + 1);
            for (int i = 0; i < h; i++) {
             std::cout << "    ";
            }
            if (node->key < 0) {
                char ops[] = {' ', '+', '-', '*', '/', '%', '^'};
                std::cout << ops[abs(node->key)] << "\n\n";
            } else std::cout << node->key << "\n\n";
            Print(node->left, h + 1);
        }
    }

    void Calculation(Node*& node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return; 
        }

        Calculation(node->left); //считаем лево
        Calculation(node->right); //счит право

        if (node->left != nullptr && node->right != nullptr) { //если у узла есть и лево и право
            if (node->left->key >= 0 && node->right->key >= 0) { //если они числа (по коду операции)
                int a = node->left->key; //берем знач левого
                int b = node->right->key; //юерем знач правого
                int res = 0;
                switch (node->key) { //производим вычисление
                    case -1: {
                        res = a + b;
                        break;
                    }
                    case -2: {
                        res = a - b;
                        break;
                    }
                    case -3: { 
                        res = a * b;
                        break;
                    }
                    case -4: {
                        if (b != 0) {
                            res = a / b;
                        }
                        break;
                    }    
                    case -5: { 
                        if (b != 0) {
                            res = a % b;
                        }
                        break;
                    }
                    case -6:{
                        res = (int)std::pow(a, b);
                        break;
                    }
                    default:
                        break;
                }
                if (res >= 0 && res <= 9) { //по усл иф результат входит в диапазон
                    delete node->left; //удаляем числа слева справа
                    delete node->right;
                    node->left = nullptr; //присваиваем нулевые значения
                    node->right = nullptr;
                    node->key = res; //записываем наш результат в текущий узел
                }
            }
        }
    }   
//-------------------------------------------------------------------------
    int GetSymbol(int op) { //расставление приоритета по знакам от самого низкого(1) к высокому (3)       
            if (op == -1 || op == -2) { //+ -
                return 1; 
            }
            if (op == -3 || op == -4 || op == -5) { // / * %
                return 2; 
            }
            if (op == -6) { // ^
                return 3; 
            }
            return 0;
    }

    void CreateNode(std::stack<Node*>& nodes, std::stack<int>& ops) {
        if (nodes.size() < 2) return;
        Node* r = nodes.top(); nodes.pop(); //смотрим правое число
        Node* l = nodes.top(); nodes.pop(); //смотрим левое число
        Node* n = new Node(ops.top()); ops.pop(); //создаем узел с номером операции
        n->left = l; //привязываем левое поддерево
        n->right = r; //правое поддерево
        nodes.push(n); //добавляем обратно в стек созданный узел
    }

    void AnalysisStr(std::string str) {
        std::stack<Node*> nodes; //стек для хранения узлов дерева
        std::stack<int> ops; //стек для хранения кодов операций
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ') continue; //пропуск пробелов
            if (str[i] == '(') { //добавляем (
                ops.push(0);
            } 
            else if (str[i] == ')') {
                while (!ops.empty() && ops.top() != 0) { //идем пока не найдем скобку (
                    CreateNode(nodes, ops); //вызов функции создания узла
                }
                if (!ops.empty()) ops.pop();  //удаляем (
            } 
            else if (str[i] == 'x') { //если х
                nodes.push(new Node(0, true)); //создаем новый узел переменную с х и добавляем в стек хранения узлов
            } 
            else if (isdigit(str[i])) { //если число
                int num = 0;
                while (i < str.length() && isdigit(str[i])) {
                    num = num * 10 + (str[i] - '0'); //превращаем из строки в число
                    i++;
                }
                i--;
                nodes.push(new Node(num, false));
            } 
            else { //если встречаем знаки операций
                int pos = 0;
                if (str[i] == '+') { 
                    pos = -1;
                } 
                else if (str[i] == '-') {
                    pos = -2;
                } 
                else if (str[i] == '*') {
                    pos = -3;
                } 
                else if (str[i] == '/') {
                    pos = -4;
                } 
                else if (str[i] == '%') {
                    pos = -5;
                } 
                else if (str[i] == '^') {
                    pos = -6;
                }
                if (pos != 0) {
                    while (!ops.empty() && ops.top() != 0 && GetSymbol(ops.top()) >= GetSymbol(pos)) { //также проверка на приоритет предыдущий знак более приоритетен чем текущий(новый)
                        CreateNode(nodes, ops);
                    }
                    ops.push(pos); //добавляем операцию в стек
                }
            }
        }
        while (!ops.empty()) { //рекурсивно вызываем для того, чтобы рассмотреть все что осталось в стеках
            CreateNode(nodes, ops);
        }
        if (!nodes.empty()) root = nodes.top(); //получается последний оставшийся узел это корень дерева
    }

    void Print2(Node* node, int h, std::ostream& out) {
        if (node) {
            Print2(node->right, h + 1, out); //рекурсивно идем вправо
            out << std::setw(h * 8) << "" << std::right << std::setw(8); //формируем зннакомест. 8 и отступ по правому краю
            if (node->isx) out << "x"; //вывод икса
            else if (node->key < 0) {
                char ops[] = {' ', '+', '-', '*', '/', '%', '^'}; //выводим знак операции
                out << ops[std::abs(node->key)];
            } else out << node->key; //выводим число
            out << "\n";
            Print2(node->left, h + 1, out); //рекурсивно идем влево по усл задачи
        }
    }

    bool ifX(Node* node) { //проверка на наличие икса в дереве ветке
        if (!node) return false;
        if (node->isx) return true;
        return ifX(node->left) || ifX(node->right); //переход и рекурсивно также проверяем
    }

    int Calcul(Node* node, int xvalue) { 
        if (!node) return 0;
        if (node->isx) return xvalue; //подставляем введенное значение икс
        if (node->key >= 0) return node->key; //вывод числа

        int a = Calcul(node->left, xvalue); //считаем левую часть
        int b = Calcul(node->right, xvalue); //считаем правую чась
        switch (node->key) { //выполняем операции
            case -1: { 
                return a + b; 
            }
            case -2: { 
                return a - b; 
            }
            case -3: { 
                return a * b; 
            }
            case -4: { 
                if (b != 0) return a / b;
                return 0;
            }
            case -5: { 
                if (b != 0) return a % b;
                return 0;
            }
            case -6: { 
                return (int)std::pow(a, b); 
            }
        }
        return 0;
    }

    void WithoutX(Node*& node) {
        if (!node || node->key >= 0 || node->isx) return;
        WithoutX(node->left); //идем до конца
        WithoutX(node->right);
        if (!ifX(node)) {
            int val = Calcul(node, 0); //счит знач всей ветки
            ClearTree(node->left); ClearTree(node->right); //удалениелевой и правой ветки из дерева
            node->key = val;
        }
    }

    void RandomInput2(Node*& node, int d) {
        if (d <= 0 || std::rand() % 3 == 0) {
            if (std::rand() % 5 == 0) {
                node = new Node(0, true); //создаем х
            } else {
                node = new Node(std::rand() % 10, false); //создаем число
            }
        } 
        else {
            int opCodes[] = {-1, -2, -3, -4, -5, -6}; //значение операций
            int randomOp = opCodes[std::rand() % 6];
            node = new Node(randomOp, false); //создание рандом операции
            RandomInput2(node->left, d - 1);
            RandomInput2(node->right, d - 1);
        }
    }
public:
    Node* getRoot() { return root; }
    TreeOriginal() : root(nullptr) {}
    ~TreeOriginal() { clear(); }

    void clear() { ClearTree(root); }
    bool isEmpty() { return root == nullptr; }

    void InputFromKeyboard();
    void InputFromFile(const char* filename);
    void InputFromRandom(int n);

    void print() { Print(root, 0); }
    void print2(std::ostream& out = std::cout) { 
        Print2(root, 0, out);
    }
    void Calc() { Calculation(root); }

    void InputFromKeyboard2();
    void InputFromFile2(const char* filename);
    void InputFromRandom2(int n);
    void CalcTree25(int x, const char* outF);
};

class Check {
public:
    static bool isDEmpty(TreeOriginal &tree) {
            if (tree.isEmpty()) {
                std::cout << "Ошибка, дерево пусто" << std::endl;
                return false;
            }
            return true;
        }

    static int getNumb(std::string str) {
        int value;
        while (true) {
            std::cout << str;
            if (std::cin >> value) return value;
            std::cout << "Ошибка, введите число" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

void CalcTree7(TreeOriginal &tree);