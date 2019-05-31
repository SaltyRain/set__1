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
//    node *temp = tail;
//    do
//    {
//        if (temp->x < x && temp->next->x > x)
//            return temp;
//        else
//            temp = temp->next;
//    } while (temp != tail);
//    return nullptr; //по идее он не может вернуть nullptr..
    
    node *temp = tail->next;
    while (temp != tail)
    {
        if (temp->x < x && temp->next->x > x)
            return temp;
        temp = temp->next;
    }
    return nullptr; //элемента не нашлось
}

bool circleList:: set:: existX(int x) const {
    if (tail != nullptr) // не проверяем на пустом списке
    {
        node *temp = tail->next;
        while (temp != tail) //пока не дошли до конца списка
        {
            if (temp->x == x)
                return true;
            temp = temp->next;
        }
        if (temp->x == x)
            return true;
    }
    return false;
}

void circleList:: set:: addElemToSet(int x)
{
    
}

void circleList:: set:: insert(int x)
{
    if (existX(x) != true) //если x еще нет в списке
    {
        //вставка в пустой
        if (tail == nullptr) //если список пуст
        {
            tail = new node();
            tail->x = x;
            return;
        }
        
        int min = tail->next->x, max = tail->x;
        
        //вставка "в конец"
        if (x > max || x < min) //Если элемент меньше меньшего или больше большего, то он всегда добавляется после tail
        {
            node *el = new node(x, tail->next); //вставка после tail
            el->next = tail->next;
            tail->next = el; //связали tail с новым элементом
            if (x > max)
                tail = tail->next; //если значение больше max, то он становится новым хвостом
            return;
        }
        
        //вставка "в середину"
        node *elem_before_x = closestEl(x);
        node *el = new node(x, elem_before_x->next); //связали новый элемент с тем, что идет после предыдущего
        elem_before_x->next = el; //связали предыдущий с новым элементом
    }
}

circleList:: node* circleList:: set:: searchPrev(node *el) const
{
    node *temp = tail->next;
    while (temp != tail)
    {
        if (temp->next == el) //если нашли такую позицию
            return temp;
        temp = temp->next;
    }
    return nullptr;
//    do
//    {
//        if (temp->next == el) //если нашли такую позицию
//            return temp;
//        temp = temp->next;
//    } while (temp != tail);
//    return nullptr; //не нашли
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
        node *temp;
        
        //удаление головы
        if (x == tail->next->x)
        {
            temp = tail->next; //храним значение, чтобы в дальнейшем иметь к нему доступ для удаления
            tail->next = tail->next->next; //меняем указатель next хвоста на следующий после удаляемой головы
            delete temp; //удаляем содержимое и указатель предыдущей головы
            return;
        }
        
        //удаление хвоста
        if (x == tail->x)
        {
            if (tail->next == tail) //если в списке один элемент
            {
                delete tail;
                tail = nullptr;
            }
            else
            {
                temp = tail; //храним значение, чтобы в дальнейшем иметь к нему доступ для удаления
                node* prev = searchPrev(tail); //ищем предыдущий от хвоста
                prev->next = tail->next; //скрепили предыдущий от максимального(хвоста) со следующим от него
                tail = prev;
                delete temp; //удаляем содержимое и указатель предыдущего tail
                return;
            }
        }
        
        //удаление "из середины"
        temp = searchX(x); //ищем, где находится элемент в списке
        node *prev = searchPrev(temp); //ищем предыдущий от temp
        prev->next = temp->next; //скрепляем предыдущий со следующим от темп
        delete temp;
    }
}

void circleList:: set:: print() const
{
//    node* temp = tail;
//    do
//    {
//        std::cout << temp->x << " ";
//        if (temp->next != nullptr) // если мн-во состоит больше чем из одного элемента
//            temp = temp->next;
//    } while (temp != tail);
    
    if (tail->next != nullptr)
    {
        node *temp = tail->next;
        while (temp != tail)
        {
            cout << temp->x << " ";
            temp = temp->next;
        }
        cout << temp->x << " ";
        cout << endl;
    }
    else
        cout << "Пустое" << endl;
}
