//
//  binaryMassiv.hpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#ifndef binaryMassiv_hpp
#define binaryMassiv_hpp

#include <stdio.h>

// Макросы
#define   SetBit(reg, bit)          reg |= (1<<bit) //поставить 1 в bit
#define   ClearBit(reg, bit)       reg &= (~(1<<bit)) // поставить 0 в bit
#define   InvBit(reg, bit)          reg ^= (1<<bit) //инвертировать бит
#define   BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0) //проверить, стоит ли 1 в бите
#define   BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0) //проверить, стоит ли 0 в бите


namespace binaryMassiv
{
    class set
    {
    public:
        set();
        set(int border1, int border2);
        ~set();
        
        set(const set &s); //копирующий конструктор
        
        set& operator = (const set &s); //перегрузка оператора присваивания
        
        set unite(const set& b); //объединение множеств
        set intersection(const set& b); //пересечение множеств
        set difference(const set& b); //разность множеств
        
        set& find(set& b, int x); //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
        set& merge(const set& b); //"слить" два множества в одно. возвращаем ссылку на новое множество
        set& assign(const set& b); //присваивание множеству this множество b
        
        void makenull(); //сделать множество пустым
        void insert(int x); //вставка элемента x в множество
        void del(int x); //удалить элемент x из множества
        void print() const; //вывод множества на печать
        int min() const; //возвращает минимальное значение
        int max() const; //возвращает максимальное значение
        
        bool equal(const set& b) const; //эквивалентность множеств
        bool member(int x) const; //принадлежность элемента x множеству
        bool empty() const; //проверка на пустоту множества
        bool checkIntersectability(const set &b) const; //проверка мн-в на пересекаемость
        
//        set& unite(set a, set b); //объединение множеств
//        set& intersection(set a, set b); //пересечение множеств
//        set& difference(set a, set b); //разность множеств
//
//        set& find(set b, int x); //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
//        set& merge(set a, set b); //"слить" два множества в одно. возвращаем ссылку на новое множество
//
//        void makenull(); //сделать множество пустым
//        void insert(int x); //вставка элемента x в множество
//        void del(int x); //удалить элемент x из множества
//        void print(); //вывод множества на печать
//        int min(); //возвращает минимальное значение
//        int max(); //возвращает максимальное значение
//        bool equal(set b); //эквивалентность множеств
//        bool member(int x); //принадлежность элемента x множеству
//        bool empty(); //проверка на пустоту множества
//        bool checkIntersectability(); //проверить мн-во на пересекаемость
//        set& assign(set b); //присваивание множеству this множество b
        
    private:
        int left_border; //нижняя граница диапазона
        int right_border; //верхняя граница диапазона
        int *arr; //бинарный массив
        
//        int elem_numbers;
        
        void assignBorders(int border1, int border2); //присвоить правильно границы
        
        int countBorder(int border_value); //высчитывает границу диапазона
        
        //        int countRange(); //высчитывает диапазон
        //        int countElemNumbers(double rng); //посчитать число элементов, нужных для диапазона
        int convertToNumber(int x) const; //преобразование числа x в номер элемента массива
        int convertToValue(int number) const; //преобразование номера элемента массива в значение x
    };
}
#endif /* binaryMassiv_hpp */
