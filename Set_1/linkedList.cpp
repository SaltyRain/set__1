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
    makenull();
}

void linkedList:: set:: copy(set &to, const set &from)
{
    node *temp1 = nullptr; //текущий
    node *temp2 = nullptr; //следующий
    
    if (from.head == nullptr) //если копируем пустой список
        to.head = nullptr;
    else
    {
        to.head = new node; //выделяем память под новую голову
        to.head->x = from.head->x; //скопировали данные в новую голову
        
        temp1 = to.head;
        temp2 = from.head->next;
        
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

void linkedList:: set:: delList(node *hd)
{
    node *temp1;
    node *temp2 = hd;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2->next;
        delete temp1;
    }
    hd = nullptr;
}

linkedList:: set:: set(const set &s) //копирующий конструктор
{
    copy(*this, s);
}

linkedList:: set& linkedList:: set:: operator=(const set &s) //перегрузка оператора присваивания
{
    if (this == &s) //проверка на самоприсваивание
        return *this;
    
    if (head != nullptr) //если множество которому присваиваем не пустое
    {
        delList(head);
    }
    
    if (s.head == nullptr) //если присваиваемое мн-во пустое
        return *this; //возвращаем пустое мн-во
    
    copy(*this, s);
    return *this;
}

bool linkedList:: set:: existX(int x) const {
    node *temp = head;
    if (head != nullptr) //не проверяем на пустом списке
    {
        while (temp != nullptr) //пока не дошли до конца списка
        {
            if (temp->x == x)
                return true;
            temp = temp->next;
        }
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

linkedList:: node* linkedList:: set:: searchPrevByValue(int x) const
{
    node* temp1 = head;
    node* temp2 = nullptr;
    while (temp1 != nullptr)
    {
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
        //сделать проверку на одинаковые значения (разные множества с одинаковым содержимым)
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
            if (same == false) //если элемент не нашелся -> добавляем его в c
            {
                c.addElemAfterPosition(b_temp->x, c_tail); //добавляем элемент в множество после c_tail
                c_tail = c_tail->next; //смещаем хвост
            }
            same = false;
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
        set c; //создаем множество, в котором будет результат операции
        if (head == nullptr || b.head == nullptr) //если хотя-бы одно из множеств пустое
            return c; //возвращаем пустое множество
        
        node *temp_a = head, *temp_b;
        
        while (temp_a != nullptr) //пока не прошлись по всему мн-ву а
        {
            temp_b = b.head; //выставили B в начало / откатили назад B
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
                c.addElemToSet(temp_a->x); //добавить элемент во множество С
            temp_a = temp_a->next; //идем к следующему элементу
        }
    }
    return c; //если А и Б равны вернется пустое
}

void linkedList:: set:: print() const
{
    if (head != nullptr)
    {
        node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->x << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    else
        cout << "Пустое" << endl;
    
}

void linkedList:: set:: makenull()
{
//    if (head != nullptr)
//        delList(head);
    
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

bool linkedList:: set:: empty() const
{
    return head == nullptr;
}

linkedList:: set& linkedList:: set:: merge(const set &b)
{
//    if (checkIntersectability() == false) // используется только на непересекающихся множествах
    {
        node *tail = searchLast(); //находим последний элемент мн-ва А
        node *b_temp = b.head;
        while (b_temp != nullptr) //пока не прошлись по всему b
        {
            addElemAfterPosition(b_temp->x, tail);
            tail = tail->next;
        }
    }
    return *this;
}

linkedList:: set& linkedList:: set:: find(set &b, int x)  //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
{
    if (searchPrevByValue(x) != nullptr)
        return *this;
    if (b.searchPrevByValue(x) != nullptr)
        return b;
    
    return fake_set;
}

int linkedList:: set:: power(node *hd) const //мощность мн-ва
{
    node *temp = hd;
    int pwr = 0;
    while (temp != nullptr)
        pwr++;
    return pwr;
}

bool linkedList:: set:: equalValues(node *hd1, node *hd2) const
{
    node *temp1 = hd1;
    node *temp2 = hd2;
    while (temp1 != nullptr)
    {
        temp2 = hd2;
        while (temp2 != nullptr)
        {
            if (temp1->x != temp2->x) //нашли несовпавшие элементы
                return false;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return true;
}

bool linkedList:: set:: equal(const set &b) const
{
    if (this == &b) //проверка указателей
        return true;
    
    if (head == nullptr && b.head == nullptr) //оба пустых
        return true;
    
    if (head == nullptr || b.head == nullptr) //проверка, если одно пустое другое нет (прошли прошлую проверку)
        return false;
    
    //1) проверка мощностей множеств
    int pwr1 = power(head);
    int pwr2 = power(b.head);
    
    if (pwr1 != pwr2) //мощности не равны
        return false;
    
    //2) если мощности совпали -> поэлементная проверка
    return equalValues(head, b.head);
}

bool linkedList:: set:: member(int x) const
{
    if (head != nullptr) //если не пустое мн-во
    {
        if (head->x == x) //проверка голов
            return true;
        
        return searchPrevByValue(x) != nullptr;
    }
    return false;
}

linkedList:: set& linkedList:: set:: assign(const set &b)
{
    *this = b;
    return *this;
}

bool linkedList:: set:: checkIntersectability(const set &b) const //проверка мн-в на пересекаемость
{
    if (head == nullptr || b.head == nullptr) //если одно из множеств пустое - возвращаем истину т.к. пустое мн-во является подмножеством любого множества
        return true;
    
    if (head->x == b.head->x) //проверка голов
        return true; //совпадение первых элементов мн-в
    
    node *temp = head->next;
    while (temp != nullptr)
    {
        if (b.searchPrevByValue(temp->x) != nullptr)
            return true;
    }
    return false;
}






