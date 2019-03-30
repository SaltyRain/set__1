//
//  binaryMassiv.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include "binaryMassiv.hpp"

#include <iostream>
#include <cmath>
#include <iomanip>


binaryMassiv::set empty_set; //фиктивное пустое множество, ссылка которого будет возвращаться после вызова функции find, результатом которого будет пустое множество


binaryMassiv:: set:: set()
{
    
}

void binaryMassiv:: set:: assignBorders(int border1, int border2)
{
    if (border1 <= border2)
    {
        left_border = border1;
        right_border = border2;
    }
    else
    {
        left_border = border2;
        right_border = border1;
    }
}

//    int binaryMassiv:: set:: countRange()
//    {
//        int rng = abs(left_border + right_border);
//        //  если сумма по модулю равна сумме без модуля
//        if (rng == left_border + right_border)
//            rng = rng + 1; //добавляем ноль
//        return rng;
//    }

binaryMassiv:: set:: set(int border1, int border2)
{
    assignBorders(border1, border2);
    double range = right_border - left_border + 1;
    elem_numbers = ceil(range/32);
    std::cout << elem_numbers << std::endl;
    arr = new int[elem_numbers];
    // заполнение массива нулями
    //НЕПРАВИЛЬНО! нулями должны заполняться байты, а не сами значения массива
    //ПРАВИЛЬНО!! если нулями заполнить значения, то и байты заполняются нулями
    for (int i = 0; i < elem_numbers; i++)
    {
        arr[i] = 0;
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

binaryMassiv:: set:: ~set()
{
    
}

int binaryMassiv:: set:: convertToNumber(int x)
{
    return 0;
}
int binaryMassiv:: set:: convertToValue(int number)
{
    return 0;
}

void binaryMassiv:: set:: insert(int x)
{
    // нужно число x "отсчитать" в массиве битов и вставить 1 на это место
    int x_number, //номер числа x в представлении
    i_nubmer, //номер элемента в массиве, в который будет осущ. вставка
    bit_number; //номер бита в элементе, в который будет осущ. вставка
    
    if (x == 0) //0 всегда последний бит последнего элемента
    {
        x_number = 0;
        i_nubmer = elem_numbers;
        bit_number = 0;
        SetBit(arr[i_nubmer], bit_number);
    }
    //        if (x > 0)
    //        {
    //            x_number = x + 1; //добавляем сдвиг из-за нуля
    //        }
    
    SetBit(arr[1], 0);
    //        //сперва x нужно преобразовать в значение
    //        int item_number = convertToNumber(x);
    //        if (arr[item_number] != 1) //если такого элемента еще нет в множестве
    //            arr[item_number] = 1; //добавить
}
void binaryMassiv:: set:: del(int x)
{
    int item_number = convertToNumber(x);
    if (arr[item_number] != 0) //если такой элемент есть
        arr[item_number] = 0; //удалить
}

int binaryMassiv:: set:: min()
{
    int minNumber = 0; //минимальное значение в виде номера массива
    //.. вычисление
    int value = convertToValue(minNumber);
    return value;
}
int binaryMassiv:: set:: max()
{
    int maxNumber = 0; //минимальное значение в виде номера массива
    //.. вычисление
    int value = convertToValue(maxNumber);
    return value;
}


