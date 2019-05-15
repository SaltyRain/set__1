//
//  linkedList.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include <iostream>

#include "linkedList.hpp"

using namespace std;

linkedList:: set fake_set;

linkedList:: set:: set() {
    head = nullptr;
}

linkedList:: set:: ~set() {
//    makenull();
}

linkedList:: set:: set(const set &s) //копирующий конструктор
{
    node *temp1 = nullptr; //текущий
    node *temp2 = nullptr; //следующий
    
    if (s.head == nullptr) //если копируем пустой список
        head = nullptr;
    else
    {
        head = new node; //выделяем память под новую голову
        head->x = s.head->x; //скопировали данные в новую голову
        
        temp1 = head;
        temp2 = s.head->next;
        
        while (temp2 != nullptr) //пока не закончился исходный список
        {
            temp1->next = new node;
            temp1 = temp1->next;
            temp1->x = temp2->x; //скопировали содержимое
            
            temp2 = temp2->next; //переместились к следующему элементу
        }
        temp1->next = nullptr;
    }
    
    
}

bool linkedList:: set:: existX(int x) const {
    node *temp = head;
    while (temp != nullptr) //пока не дошли до конца списка
    {
        if (temp->x == x)
            return true;
        temp = temp->next;
    }
    return false;
}

linkedList:: node* linkedList:: set:: searchLast() const
{
    node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    return temp;
}

void linkedList:: set:: addElemAfterPosition(int x, node* position)
{
    if (head == nullptr) //вставка в пустое множество
        head = new node(x, nullptr); //вставка в голову
    
    else //вставка в позицию со скреплением
    {
        node *el = new node(x, nullptr);
        position->next = el; //скрепили новый элемент с последним
    }
}

void linkedList:: set:: addElemToSet(int x)
{
    if (head == nullptr) //вставка в пустое множество
        head = new node(x, nullptr); //вставка в голову
    
    else //вставка в конец со скреплением
    {
        node *el = new node(x, nullptr);
        node* prev = searchLast();
        prev->next = el; //скрепили новый элемент с последним
    }
}

void linkedList:: set:: insert(int x)
{
    if (existX(x) != true) //если элемента x еще нет в множестве
        addElemToSet(x);
}

linkedList:: node* linkedList:: set:: searchPrev(node *elem) const
{
    node* temp = head;
    while (temp->next != elem)
    {
        if (temp->next == elem)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

linkedList:: node* linkedList:: set:: searchPrevByValue(int x) const
{
    node* temp1 = head;
    node* temp2 = nullptr;
    while (temp1 != nullptr) {
        temp2 = temp1;
        temp1 =  temp1->next;
        if (temp1->x == x)
            return temp2;
    }
    return nullptr; //нет такого элемента
}

void linkedList:: set:: del(int x)
{
    if (existX(x) == true) //если элемент x есть в множестве
    {
        if (head->x == x) //если это первый элемент в множестве
        {
            if (head->next == nullptr) // если элемент единственный в множестве
                head = nullptr;
            else
            {
                node* t_head = head;
                head = head->next;
                delete t_head;
            }
        }
        
        else
        {
            node* el_prev = searchPrevByValue(x);
            if (el_prev->next->next != nullptr) //если элемент не последний во множестве
            {
                node* el_next = el_prev->next->next;
                delete el_prev->next; //удаляем элемент
                el_prev->next = el_next; //связали предыдущий от элемента и следующий от него
            }
            else
            {
                //если элемент - последний во множестве
                el_prev->next = nullptr;
            }
        }
    }
}



linkedList:: set linkedList:: set:: unite(const set &b) //объединение мн-в
{
    if (head == nullptr) // если множество А пустое
    {
        set c(b); //копируем множество B так как А пустое
        return c; //возвращаем множество B
    }
    
    if (this != &b) //если А и Б - не одно и то же множество (c = a.unite(a))
    {
        set c(*this);
        
        if (b.head == nullptr) //если Б пустое или множества эквивалентны
            return c;
        
        node *c_initalTail = c.searchLast(); //запомнили указатель на последний в с
        node *c_tail = c_initalTail; //этот указатель будет смещаться и находить место для вставки новых элементов
        node *c_temp = c.head;
        node *b_temp =  b.head;
        
        bool same = false; //проверяет, нашелся ли в с элемент из б
        
        while (b_temp != nullptr) //ищем по множеству b пока оно не закончилось
        {
            while (c_temp != c_initalTail) //пока не дошли до изначального конца с
            {
                if (b_temp->x == c_temp->x) //если в множестве с нашлось b
                {
                    same = true;
                    break;
                }
                
                c_temp = c_temp->next; //иначе ищем совпадение дальше. переходим к следующему из с
            }
            if (same == false) //если элемент не нашелся -> добавляем в c
            {
                c.addElemAfterPosition(b_temp->x, c_tail); //добавляем элемент в множество после c_tail
                c_tail = c_tail->next; //смещаем хвост
            }
            same = true;
            c_temp = c.head; //возвращаем temp в начало множества
            b_temp = b_temp->next;
        }
         return c;
    }
    return *this;
}

linkedList:: set linkedList:: set:: intersection(const set &b) //пересечение мн-в
{
    if (this != &b) //если А и Б - не одно и то же множество (c = a.intersection(a))
    {
        set c;
        if (head == nullptr || b.head == nullptr) //если хотя-бы одно из множеств пустое
            return c; //возвращаем пустое множество
        
        node *temp_a = head, *temp_b;
        
        while (temp_a != nullptr) //пока не прошлись по всему мн-ву а
        {
            temp_b = b.head; //откатили назад B
            while (temp_b != nullptr) //пока не прошлись по всему мн-ву b
            {
                if (temp_a->x == temp_b->x) //если нашли в B такой же элемент как из А
                {
                    c.addElemToSet(temp_a->x);//добавить элемент во множество С
                    break;
                }
                temp_b = temp_b->next; //иначе ищем дальше
            }
            temp_a = temp_a->next; //идем к следующему элементу
        }
        return c;
    }
    return *this;
}

linkedList:: set linkedList:: set:: difference(const set &b) //разность мн-в
{
    set c;
    if (this != &b) //если А и Б - не одно и то же множество (c = a.difference(a))
    {
        if (head == nullptr)
            return c; //вернуть пустое множество
        if (b.head == nullptr)
            return *this; //вернуть множество A
        
        node *temp_a = head, *temp_b;
        int flag;
        while (temp_a != nullptr) //пока не прошлись по всему мн-ву а
        {
            temp_b = b.head; //откатили назад B
            flag = 0;
            while (temp_b != nullptr) //пока не прошлись по всему мн-ву b
            {
                if (temp_a->x == temp_b->x) //если нашли в B такой же элемент как из А
                {
                    flag = 1;
                    break;
                }
                temp_b = temp_b->next; //иначе ищем дальше
            }
            if (flag != 1)
                c.addElemToSet(temp_a->x);//добавить элемент во множество С
            temp_a = temp_a->next; //идем к следующему элементу
        }
    }
    return c; //если А и Б равны вернется пустое
}

void linkedList:: set:: print() const
{
    node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->x << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void linkedList:: set:: makenull()
{
    node* temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

int linkedList:: set:: min() const
{
    node* temp = head;
    int min_x = temp->x;
    while (temp != nullptr)
    {
        if (temp->x < min_x) //если нашелся x меньше mix_x
            min_x = temp->x; //x становится min_x
        temp = temp->next;
    }
    return min_x;
}

int linkedList:: set:: max() const
{
    node* temp = head;
    int max_x = temp->x;
    while (temp != nullptr)
    {
        if (temp->x > max_x) //если нашелся x меньше mix_x
            max_x = temp->x; //x становится min_x
        temp = temp->next;
    }
    return max_x;
}
