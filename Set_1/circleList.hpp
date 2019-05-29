//
//  circleList.hpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#ifndef circleList_hpp
#define circleList_hpp

#include <stdio.h>

namespace circleList {
    
    struct node
    {
        int x;
        node *next;
        node ()
        {
            x = 0;
            next = this;
        }
        node(int data, node *nxt): x(data), next(nxt) {};
    };
    
    class set {
    public:        
        set();
        ~set();
        set(const set &s); //копирующий конструктор
        
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
        
        bool equal(const set& b) const; //эквивалентность множеств
        bool member(int x) const; //принадлежность элемента x множеству
        bool empty() const; //проверка на пустоту множества
        bool checkIntersectability() const; //проверить мн-во на пересекаемость
        
    private:
        node *tail;
        
        bool existX(int x) const; //ищет x во множестве, если находит возвращает true
        
        void addElemToSet(int x); //добавление элемента к множеству
        
        node* closestEl(int x) const; //ищет ближайший к x элемент в множестве и возвращает его положение
        node* searchPrev(node* el) const; //поиск предыдущего элемента от el
        node* searchX(int x) const; //ищет местоположение x в списке
    };
}

#endif /* circleList_hpp */
