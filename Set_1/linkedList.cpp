//
//  linkedList.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include "linkedList.hpp"

linkedList:: set:: set() {
    head = nullptr;
}

linkedList:: set:: ~set() {
//    makenull();
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

linkedList:: node* linkedList:: set:: searchElem(int x) const
{
    node* temp = head;
    while (temp->x != x)
    {
        if (temp->x == x)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

linkedList:: node* linkedList:: set:: searchPrevByValue(int x) const
{
    node* temp = head;
    while (temp->next->x != x)
    {
        if (temp->next->x != x)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void linkedList:: set:: del(int x)
{
    if (existX(x) == true) //если элемент x есть в множестве
    {
        if (head->x == x) //если это первый элемент в множестве
        {
            if (head->next == nullptr) // если элемент единственный в множестве
            {
                head = nullptr;
                //возможно нужна очистка??
            }
            
            node* t_head = head;
            head = head->next;
            delete t_head;
        }
        else
        {
            //            node* el = searchElem(x);
            //            node* prev = searchPrev(el); //находим предыдущий от el
            //            prev->next = el->next;
            //            delete el; //удаляем элемент
            
            node* prev = searchPrevByValue(x);
            node* el = prev->next;
            prev->next = el->next;
            delete el;
        }
    }
}
