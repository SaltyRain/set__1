//
//  linkedList.hpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#ifndef linkedList_hpp
#define linkedList_hpp

#include <stdio.h>

namespace linkedList {
    
    struct node {
        int x;
        node *next;
        
        node(){}
        node(int data, node *nxt): x(data), next(nxt) {};
    };
    
    class set {
    public:
        set();
        ~set();
        //добавить копирующий конструктор
        
        set unite(const set& b); //объединение множеств
        set intersection(const set& b); //пересечение множеств
        set difference(const set& b); //разность множеств
        
        set& find(const set& b, int x) const; //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
        set& merge(const set& b); //"слить" два множества в одно. возвращаем ссылку на новое множество
        set& assign(const set& b); //присваивание множеству this множество b
        
        void makenull(); //сделать множество пустым
        void insert(int x); //вставка элемента x в множество
        void del(int x); //удалить элемент x из множества
        void print() const; //вывод множества на печать
        int min() const; //возвращает минимальное значение
        int max() const; //возвращает максимальное значение
        
        bool equal(const set& b); //эквивалентность множеств
        bool member(int x); //принадлежность элемента x множеству
        bool empty() const; //проверка на пустоту множества
        bool checkIntersectability() const; //проверить мн-во на пересекаемость
     
    private:
        node *head;
        
        bool existX(int x) const;
        node* searchLast() const; //поиск последнего элемента в множестве
        node* searchPrev(node* elem) const; //ищет предыдущий элемент от elem
        node* searchElem(int x) const; //ищет позицию элемента x в списке
        node* searchPrevByValue(int x) const; //возвращает место предыдущего элемента от x
    };
}

#endif /* linkedList_hpp */
