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
    delList(tail);
}

void circleList:: set:: copy(set &to, const set &from)
{
    node *temp1 = nullptr; //текущий
    node *temp2 = nullptr; //следующий
    
    if (from.tail == nullptr) //если копируем пустой список
        to.tail = nullptr;
    else
    {
        insertFirst(from.tail->x);
        
        temp1 = to.tail;
        temp2 = from.tail->next;
        
        while (temp2 != from.tail) //пока не закончился исходный список
        {
            if (existX(temp2->x) != true)
                insertInPosition(temp2->x);
            temp2 = temp2->next;
        }
    }
}

circleList::node* circleList:: set:: delList(node *tl)
{ //
    if (tl != nullptr) //лишняя проверка
    {
        
        node *temp1 = tl->next;
        node *temp2 = tl->next;
        while (temp2 != tl)
        {
            temp1 = temp2;
            temp2 = temp2->next;
            delete temp1;
        }
        delete temp2;
    }
    return nullptr;
}

circleList:: set:: set(const set &s)
{
    copy(*this, s);
}

circleList:: set& circleList:: set:: operator=(const set &s) //перегрузка оператора присваивания
{
    if (this == &s) //проверка на самоприсваивание
        return *this;
    
    if (tail != nullptr) //если множество которому присваиваем не пустое
    {
        delList(tail);
    }
    
    if (s.tail == nullptr) //если присваиваемое мн-во пустое
        return *this; //возвращаем пустое мн-во
    
    copy(*this, s);
    return *this;
}

circleList:: node* circleList:: set:: searchPrevByValue(int x) const //поиск предыдущего по значению
{
    node *temp = tail->next;
    while (temp != tail)
    {
        if (temp->x < x && temp->next->x > x)
            return temp;
        temp = temp->next;
    }
    if (temp->x < x && temp->next->x > x)
        return temp;
    return nullptr; //элемента не нашлось
}

circleList:: node* circleList:: set:: searchPrevByPosition(node *el) const
{
    node *temp = tail->next;
    while (temp != tail)
    {
        if (temp->next == el) //если нашли такую позицию
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void circleList:: set:: insertFirst(int x)
 // Вставка в пустое множество
{
    tail = new node();
    tail->x = x;
}


void circleList:: set:: insertInEnd(int x)
// вставка "в конец"
{
    node *next_el = new node(x, tail->next);
    tail->next = next_el;
}

void circleList:: set:: insertFirstOrInEnd(int x) //вставка в позицию
{
    // Вставка в пустое множество
    if (tail == nullptr)
    {
        insertFirst(x);
    }
    else // вставка "в конец"
    {
        insertInEnd(x);
        tail = tail->next;
    }
}

void circleList:: set:: insertInPosition(int x) //используется цикл с поиском места вставки
{
    if (tail == nullptr) //вставка в пустой список
    {
        insertFirst(x);
        return;
    }
    
    int min = tail->next->x, max = tail->x;
    
    if (x < min) //x меньше всех -> вставляется в голову
    {
        node *el = new node(x, tail->next); //вставка после tail
        el->next = tail->next;
        tail->next = el; //связали tail с новым элементом
        return;
    }
    
    if (x > max) //x больше всех -> вставка в хвост
    {
        node *el = new node(x, tail->next); //вставка после tail
        el->next = tail->next;
        tail->next = el; //связали tail с новым элементом
        tail = tail->next; //сместили указатель хвоста
        return;
    }
    
    //вставка в середину
    node *elem_before_x = searchPrevByValue(x);
    node *el = new node(x, elem_before_x->next); //связали новый элемент с тем, что идет после предыдущего
    elem_before_x->next = el; //связали предыдущий с новым элементом
}

bool circleList:: set:: existX(int x) const  //существует ли х?
{
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

void circleList:: set:: insert(int x)
{
    if (existX(x) != true) //если x еще нет в списке
    {
        insertInPosition(x);
    }
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
                node* prev = searchPrevByPosition(tail); //ищем предыдущий от хвоста
                prev->next = tail->next; //скрепили предыдущий от максимального(хвоста) со следующим от него
                tail = prev;
                delete temp; //удаляем содержимое и указатель предыдущего tail
                return;
            }
        }
        
        //удаление "из середины"
        temp = searchX(x); //ищем, где находится элемент в списке
        node *prev = searchPrevByPosition(temp); //ищем предыдущий от temp
        prev->next = temp->next; //скрепляем предыдущий со следующим от темп
        delete temp;
    }
}


circleList:: set circleList:: set:: unite(const set &b)
{
    if (tail == nullptr) // если множество А пустое
    {
        set c(b); //копируем множество В т.к. А пустое
        return c; // возвращаем множество В
    }

    if (this != &b) //если А и Б - не одно и то же множество (c = a.unite(a))
    {
//        set c(*this); //копируем А в C

        if (b.tail == nullptr) //если Б пустое или множества эквивалентны
            return *this;
        
        if (tail->next->x < b.tail->x) //голова первого больше хвоста второго -> мн-ва не пересекаются -> сливаем в одно
        {
            set c(b); //сначала добавляем меньшие из В
            node *temp = tail->next;
            while (temp != tail)
            {
                c.insertInEnd(temp->x);
                temp = temp->next;
            }
            c.insertInEnd(temp->x);
            return c;
        }
        
        if (b.tail->next->x < tail->x) //голова второго больше хвоста первого -> мн-ва не пересекаются -> сливаем в одно
        {
            set c(*this); //Добавляем меньшее А
            node *temp = b.tail->next;
            while (temp != b.tail)
            {
                c.insertInEnd(temp->x);
                temp = temp->next;
            }
            c.insertInEnd(temp->x);
            return c;
        }
    }
    return *this;
}



circleList:: set& circleList:: set:: checkIfOneEnds(node *temp1, node *temp2, node *temp1tail)
{
    while (temp1 != temp1tail && (temp2->x >= temp1->x)) //пока не закончилось N-e мн-во и пока значение из N множества не больше зн-я из M
    {
        if (temp1->x == temp2->x) //нашли совпавшие значения
        {
            insertFirstOrInEnd(temp1->x);
            return *this;
        }
        temp1 = temp1->next; //ищем дальше
    }
    if (temp1->x == temp2->x) //нашли совпавшие значения
        insertFirstOrInEnd(temp1->x);
    
    return *this;
}


circleList:: set circleList:: set:: intersection(const set &b)
{
    if (this != &b) //если А и Б - не одно и то же множество (c = a.intersection(a))
    {
        set c; //создаем множество, в котором будет результат операции
        if (tail == nullptr || b.tail == nullptr) //если хотя-бы одно из множеств пустое
            return c; //возвращаем пустое множество

        if (tail->next->x > b.tail->x || b.tail->next->x > tail->x) // если первый элемент в одном из множеств больше хвоста другого множества (А: { 1,2,3,4 } B: { 5,6,7,8 } или наоборот)
            return c; //пересечений нет -> возвращаем пустое множество

        node *temp_a = tail->next;
        node *temp_b = b.tail->next;

        while (temp_a != tail && (temp_a->x <= b.tail->x) && (temp_b->x <= tail->x) && temp_b != tail) // пока не закончилось первое множество и пока текущий элемент из А меньше или равен хвосту B (А: 1,2,3,9, 10 В:2,4,5 - дойдет до 2 в А и прервется) и пока текущий из В меньше или равен хвосту А (А: 12, 23, 24, 48, 54, 66 В: 12, 13, 47) или пока не закончилось B
        {
            //ищем совпадение значений
            if (temp_a->x > temp_b->x) //значение в А больше
            {
                temp_b = temp_b->next; //значит двигаемся по B
                continue; //сравниваем следующую пару значений
            }

            if (temp_b->x > temp_a->x) //значение в B больше
            {
                temp_a = temp_a->next; //значит двигаемся по A
                continue; //сравниваем следующую пару значений
            }

            //значения совпали
            c.insertFirstOrInEnd(temp_a->x);

            temp_a = temp_a->next; //смещаем совпавшие значения
            temp_b = temp_b->next; //смещаем совпавшие значения
        }

        // проверка хвостов множеств
        if (temp_a == tail && temp_b == b.tail) //если оба указателя указывают на хвосты списков
        {
            if (temp_a->x == temp_b->x) //если значения совпадают
                c.insertFirstOrInEnd(temp_a->x);
            return c; //множества закончились -> возвращаем результат в с
        }

        //Если первое множество закончилось, но значение текущего во втором множестве меньше хвоста первого (А: 1,2,3,8,11 B: 1,3,5,8,10,11)
        if (temp_a == tail && (temp_b->x <= temp_a->x))
            c.checkIfOneEnds(temp_b, temp_a, b.tail);


        //Если закончилось второе, но значение текущего из первого меньше хвоста второго (множества наоборот)
        if (temp_b == tail && (temp_a->x <= temp_b->x))
            c.checkIfOneEnds(temp_a, temp_b, tail);

        return c;
    }
    return *this; //множества одинаковы - возвращаем одно из них
}

circleList:: set circleList:: set:: difference(const set &b) //разность мн-в
{
    set c;
    if (this != &b) //если А и Б - не одно и то же множество (c = a.difference(a))
    {
        if (tail == nullptr)
            return c; //вернуть пустое
        if (b.tail == nullptr)
            return *this; //второе пустое - возвращаем мн-во А
        
        if (tail->x < b.tail->next->x)
            return *this;
        
        
        node *temp_a = tail->next;
        node *temp_b = b.tail->next;
        
        while (temp_a != tail && (temp_a->x < b.tail->x) && (temp_b->x < tail->x) && temp_b != tail) // пока не закончилось первое множество и пока текущий элемент из А меньше или равен хвосту B (А: 1,2,3,9, 10 В:2,4,5 - дойдет до 2 в А и прервется) и пока текущий из В меньше или равен хвосту А (А: 12, 23, 24, 48, 54, 66 В: 12, 13, 47) или пока не закончилось B
        {
            if (temp_a->x < temp_b->x) //если значение из а меньше текущего из B значит точно в B не будет текущего из А значит его можно добавить в С и двигаться дальше по А
            {
                c.insertFirstOrInEnd(temp_a->x);
                temp_a = temp_a->next;
                continue;
            }
            
            if (temp_a->x > temp_b->x) //если значение из А больше значения из В значит в В мы уже точно не найдем значение из А -> двигаемся дальше по В
            {
                temp_b = temp_b->next;
                continue;
            }
            
            //значения равны -> двигаемся дальше по обоим спискам
            temp_a = temp_a->next;
            temp_b = temp_b->next;
        }
        
        //проверка хвостов
        
        //одинаковые хвосты
        if (temp_a == tail && temp_b == b.tail) //если оба указателя указывают на хвосты списков
        {
            if (temp_a->x != temp_b->x) //если значения не совпадают
                c.insertFirstOrInEnd(temp_a->x);
            return c;
        }
        
        //первое стоит на хвосте, но во втором значение меньше значения хвоста первого
        // A(1,2,3,49) B(1,6,7,9,22,48)
        if (temp_a == tail && (temp_b->x < temp_a->x))
        {
            while (temp_b != b.tail && temp_a->x > temp_b->x) //пока не дошли до конца B или не нашли элемент больший хвостаА
                temp_b = temp_b->next;
            
            // дошли до элементов в В больших или равных хвосту А -> если равны -> ничего не происходит. Если не равны -> добавляем
            if (temp_a->x != temp_b->x)
                c.insertFirstOrInEnd(temp_a->x); //добавили несовпавший элемент
            
            return c;
        }
        
        // Элементы А стали больше чем в В значит совпадений уже не будет -> добавляем всё из А
        if (temp_a->x > temp_b->x)
        {
            while (temp_a != tail)
            {
                c.insertFirstOrInEnd(temp_a->x);
                temp_a = temp_a->next;
            }
            c.insertFirstOrInEnd(temp_a->x); //вставка последнего
            return c;
        }
        
        //В на хвосте, но значение хвоста В больше текущего в А
        if (temp_b == b.tail && (temp_b->x >= temp_a->x))
        {
            
            //значит надо сравнивать значения А с хвостом В пока В не закончилось, либо пока мы не найдем совпадение, либо значения А станут больше хвоста В
            while (temp_a != tail && (temp_b->x <= temp_a->x))
            {
                if (temp_b->x == temp_a->x)
                {
                    temp_a = temp_a->next;
                    break;
                }
                c.insertFirstOrInEnd(temp_a->x);
                temp_a = temp_a->next;
                
            }
            // Элементы А стали больше чем в В значит совпадений уже не будет -> добавляем всё из А
            if (temp_a->x > temp_b->x)
            {
                while (temp_a != tail)
                {
                    c.insertFirstOrInEnd(temp_a->x);
                    temp_a = temp_a->next;
                }
                c.insertFirstOrInEnd(temp_a->x); //вставка последнего
                return c;
            }
        }
    }
    return c;
}



void circleList:: set:: makenull()
{
    if (tail != nullptr)
        tail = delList(tail);
}

bool circleList:: set:: empty() const
{
    return (tail == nullptr ? true : false);
}

int circleList:: set:: min() const {
    return tail->next->x;
}

int circleList:: set:: max() const {
    return tail->x;
}

bool circleList:: set:: equal(const set &b) const
{
    if (this == &b) //проверка по адресу
        return true;
    return equalValues(tail, b.tail); //проверка по значениям
}

bool circleList:: set:: equalValues(node *tail1, node *tail2) const //проверка на совпадение значений множеств (разные адреса, одинаковые значения)
{
    if (tail1 == nullptr && tail2 == nullptr) //пустые множества эквивалентны
        return true;
    if (tail1->x != tail2->x) //проверка конечных значений
        return false;
    
    node *temp1 = tail1->next;
    node *temp2 = tail2->next;
    
    while (temp1 != tail && temp2 != tail) //пока не закончились оба множества
    {
        if (temp1->x != temp2->x) //нашли разные значения
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    
    //если одно из мн-в закончилось (пр. А(1,2,3) В(1,2,3,4)
    if (temp1 != tail || temp2 != tail) //если в хотя-бы одном из множеств мы не дошли до конца (следовательно где-то значения не совпали)
        return false;
    else
        return true;
}

void circleList:: set:: print() const
{
    if (tail != nullptr)
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
