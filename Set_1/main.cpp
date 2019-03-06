//
//  main.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 06/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include <iostream>

namespace binaryMassiv {
    class set {
    public:
        set();
        set(int border1, int border2);
        ~set();
        
        set& unite(set a, set b); //объединение множеств
        set& intersection(set a, set b); //пересечение множеств
        set& difference(set a, set b); //разность множеств
        
        set& find(set b, int x); //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
        set& merge(set a, set b); //"слить" два множества в одно. возвращаем ссылку на новое множество
        
        void makenull(); //сделать множество пустым
        void insert(int x); //вставка элемента x в множество
        void del(int x); //удалить элемент x из множества
        void print(); //вывод множества на печать
        int min(); //возвращает минимальное значение
        int max(); //возвращает максимальное значение
        bool equal(set b); //эквивалентность множеств
        bool member(int x); //принадлежность элемента x множеству
        bool empty(); //проверка на пустоту множества
        bool check_intersectability(); //проверить мн-во на пересекаемость
        set& assign(set b); //присваивание множеству this множество b
     
    private:
        int left_border; //нижняя граница диапазона
        int right_border; //верхняя граница диапазона
        int arr[]; //бинарный массив
    };
    
    set empty_set; //фиктивное пустое множество, ссылка которого будет возвращаться после вызова функции find, результатом которого будет пустое множество
    
    
}

namespace circleList {
    class set {
    public:
        
    private:
        
    };
}

namespace linkedList {
    class set {
    public:
        
    private:
        
    };
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
