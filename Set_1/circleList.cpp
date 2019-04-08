//
//  circleList.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 31/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include "circleList.hpp"

#include <iostream>
using namespace std;

circleList:: set:: set() {
    tail = nullptr;
}

circleList:: set:: ~set() {
    makenull();
}

void circleList:: set:: makenull() {
}

bool circleList:: set:: empty() const
{
    return (tail == nullptr ? true : false);
}

bool circleList:: set:: existX(int x) const {
    node *temp = tail;
    if (tail != nullptr)
    {
        do
        {
            if (temp->x == x) //если элемент нашелся
                return true;
            else
                temp = temp->next; //не нашелся, ищем дальше по списку
        } while (temp != tail); //пока не вернулись к изначальному элементу
    }
    return false;
}

int circleList:: set:: min() const {
    if (tail != nullptr)
        return tail->next->x;
    else
        return NULL;
    
}
int circleList:: set:: max() const {
    if (tail != nullptr)
        return tail->x;
    else
        return NULL;
    
    
}

circleList:: node* circleList:: set:: closestEl(int x) const
{
    node *temp = tail;
    do
    {
        if (temp->x < x && temp->next->x > x)
            return temp;
        else
            temp = temp->next;
    } while (temp != tail);
    return nullptr; //по идее он не может вернуть nullptr..
}

void circleList:: set:: insert(int x)
{
    if (existX(x) != true) //если x еще нет в списке
    {
        if (tail == nullptr) //если список пуст
        {
            tail = new node(x, tail); //создаем первый элемент
            return;
        }
        
        int min = tail->next->x, max = tail->x;
        if (x > max || x < min) //всегда добавляется после tail
        {
            node *el = new node(x, tail->next);
            tail->next = el;
            if (x > max)
                tail = tail->next; //если значение больше max, то он становится новым хвостом
            return;
        }
        
        node* elem_before_x = closestEl(x);
        node *el = new node(x, elem_before_x->next); //связали новый элемент с тем, что идет после предыдущего
        elem_before_x->next = el; //связали предыдущий с новым элементом
    }
}

circleList:: node* circleList:: set:: searchPrev(node *el) const
{
    node *temp = tail;
    do
    {
        if (temp->next == el) //если нашли такую позицию
            return temp;
        temp = temp->next;
    } while (temp != tail);
    return nullptr; //не нашли
}

circleList:: node* circleList:: set:: searchX(int x) const
{
    node *temp = tail;
    do
    {
        if (temp->x == x) //если элемент нашелся
            return temp;
        else
            temp = temp->next; //не нашелся, ищем дальше по списку
    } while (temp != tail); //пока не вернулись к изначальному элементу
    return nullptr;
}

void circleList:: set:: del(int x)
{
    if (existX(x) == true) //если x есть в списке
    {
        if (x == min())
        {
            tail->next = tail->next->next; //меняем tail->next
            delete tail->next;
        }
        if (x == max())
        {
            node* prev = searchPrev(tail);
            prev->next = tail->next; //скрепили предыдущий от максимального со следующим от него
            node *temp = tail;
            tail = tail->next;
            delete temp;
        }
        
        node *temp = searchX(x);
        node* prev = searchPrev(temp);
        prev->next = temp->next;
        delete temp;
    }
}

void circleList:: set:: print() const
{
    node* temp = tail;
    do
    {
        std::cout << temp->x << " ";
        if (temp->next != nullptr) // если мн-во состоит больше чем из одного элемента
            temp = temp->next;
    } while (temp != tail);
}
