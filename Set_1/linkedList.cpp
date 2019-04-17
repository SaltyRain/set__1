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

void linkedList:: set:: insert(int x)
{
    if (existX(x) != true) //если элемента x еще нет в множестве
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


linkedList:: set linkedList:: set:: unite(const set &b)
{
    set c(*this); //копируем множество a в новое множество c
    
    node *c_tail = c.searchLast(); //запомнили указатель на последний в с
    node *el = new node;
    el = b.head;
    c_tail->next = el;
    
    node *temp = b.head->next;
    while (temp != nullptr) //ищем по множеству b пока оно не закончилось
    {
        
    }
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
    while (temp->next != nullptr)
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
    while (temp->next != nullptr)
    {
        if (temp->x > max_x) //если нашелся x меньше mix_x
            max_x = temp->x; //x становится min_x
        temp = temp->next;
    }
    return max_x;
}
