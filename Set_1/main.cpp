//
//  main.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 06/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <iomanip>

#include "binaryMassiv.hpp"
#include "circleList.hpp"
#include "linkedList.hpp"

using namespace std;

using namespace linkedList;

void insertElem(set& setName)
{
    int code = 1;
    int elem;
    cout << setw(5) << "ДОБАВЛЕНИЕ ЭЛЕМЕНТА В МНОЖЕСТВО" << endl;
    while (code == 1)
    {
        cout << setw(5) <<  "Введите элемент: ";
        cin >> elem;
        setName.insert(elem);
        setName.print();
        cout << setw(5) << "Элемент добавлен. Добавить еще элемент? (1 - да/ 0 - нет)" << endl;
        cout << setw(5) << "Выбор: ";
        cin >> code;
    }
}

void delElem(set& setName)
{
    int code = 1;
    int elem;
    cout << setw(5) << "УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ МНОЖЕСТВА" << endl;
    while (code == 1)
    {
        cout << setw(5) <<  "Введите элемент: ";
        cin >> elem;
        setName.del(elem);
        setName.print();
        cout << setw(5) << "Элемент удалён. Удалить еще элемент? (1 - да/ 0 - нет)" << endl;
        cout << setw(5) << "Выбор: ";
        cin >> code;
    }
    
}

void menu(set& setName)
{
    int code = 0;
  
    while (code != 100)
    {
        cout << "Выберите операцию над множеством" << endl;
        cout << "Вставка элементом в множество  1" << endl;
        cout << "Удаление элементов из множества  2" << endl;
        cout << "Вывести множество на экран 9" << endl;
        cout << "Завершить программу  100" << endl;
        
        cout << "Команда: ";
        cin >> code;
        cout << code;
        switch (code) {
            case 1:
                insertElem(setName);
                break;
            case 2:
                delElem(setName);
                break;
                
            case 9:
                cout << "\nМножество: ";
                setName.print();
            default:
                code = 0;
                break;
        }
    }
    
}


int main(int argc, const char * argv[]) {
    set A;
    menu(A);
    
}
