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
//#include "linkedList.hpp"

using namespace std;

using namespace circleList;

void insertElem(set& setName)
{
    int elem;
    cout << setw(5) << "ДОБАВЛЕНИЕ ЭЛЕМЕНТА В МНОЖЕСТВО" << endl;
    cout << setw(5) <<  "Введите элемент: ";
    cin >> elem;
    setName.insert(elem);
}


int main(int argc, const char * argv[]) {
    set A;
    insertElem(A);
    A.print();
    
}
