//
//  main.cpp
//  Set_1
//
//  Created by Тимур Гарипов on 06/03/2019.
//  Copyright © 2019 Timur. All rights reserved.
//

#include <iostream>
#include <math.h>

// Макросы
#define   SetBit(reg, bit)          reg |= (1<<bit) //поставить 1 в bit
#define   ClearBit(reg, bit)       reg &= (~(1<<bit)) // поставить 0 в bit
#define   InvBit(reg, bit)          reg ^= (1<<bit) //инвертировать бит
#define   BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0) //проверить, стоит ли 1 в бите
#define   BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0) //проверить, стоит ли 0 в бите

namespace binaryMassiv
{
    class set
    {
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
        bool checkIntersectability(); //проверить мн-во на пересекаемость
        set& assign(set b); //присваивание множеству this множество b
     
    private:
        int left_border; //нижняя граница диапазона
        int right_border; //верхняя граница диапазона
        int *arr; //бинарный массив
        
        int elem_numbers;
        
        void assignBorders(int border1, int border2); //присвоить правильно границы
//        int countRange(); //высчитывает диапазон
//        int countElemNumbers(double rng); //посчитать число элементов, нужных для диапазона
        int convertToNumber(int x); //преобразование числа x в номер элемента массива
        int convertToValue(int number); //преобразование номера элемента массива в значение x
    };
    
    set empty_set; //фиктивное пустое множество, ссылка которого будет возвращаться после вызова функции find, результатом которого будет пустое множество
    
  
    binaryMassiv:: set:: set()
    {
        
    }
    
    void binaryMassiv:: set:: assignBorders(int border1, int border2)
    {
        if (border1 <= border2)
        {
            left_border = border1;
            right_border = border2;
        }
        else
        {
            left_border = border2;
            right_border = border1;
        }
    }
    
//    int binaryMassiv:: set:: countRange()
//    {
//        int rng = abs(left_border + right_border);
//        //  если сумма по модулю равна сумме без модуля
//        if (rng == left_border + right_border)
//            rng = rng + 1; //добавляем ноль
//        return rng;
//    }
    
    binaryMassiv:: set:: set(int border1, int border2)
    {
        assignBorders(border1, border2);
        double range = right_border - left_border + 1;
        elem_numbers = ceil(range/32);
        std::cout << elem_numbers << std::endl;
        arr = new int[elem_numbers];
        // заполнение массива нулями
        //НЕПРАВИЛЬНО! нулями должны заполняться байты, а не сами значения массива
        //ПРАВИЛЬНО!! если нулями заполнить значения, то и байты заполняются нулями
        for (int i = 0; i < elem_numbers; i++)
        {
            arr[i] = 0;
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }
    
    binaryMassiv:: set:: ~set()
    {
        
    }
    
    int binaryMassiv:: set:: convertToNumber(int x)
    {
        return 0;
    }
    int binaryMassiv:: set:: convertToValue(int number)
    {
        return 0;
    }
    
    void binaryMassiv:: set:: insert(int x)
    {
        // нужно число x "отсчитать" в массиве битов и вставить 1 на это место
        int x_number, //номер числа x в представлении
        i_nubmer, //номер элемента в массиве, в который будет осущ. вставка
        bit_number; //номер бита в элементе, в который будет осущ. вставка
        
        if (x == 0) //0 всегда последний бит последнего элемента
        {
            x_number = 0;
            i_nubmer = elem_numbers;
            bit_number = 0;
            SetBit(arr[i_nubmer], bit_number);
        }
//        if (x > 0)
//        {
//            x_number = x + 1; //добавляем сдвиг из-за нуля
//        }
        
        SetBit(arr[1], 0);
//        //сперва x нужно преобразовать в значение
//        int item_number = convertToNumber(x);
//        if (arr[item_number] != 1) //если такого элемента еще нет в множестве
//            arr[item_number] = 1; //добавить
    }
    void binaryMassiv:: set:: del(int x)
    {
        int item_number = convertToNumber(x);
        if (arr[item_number] != 0) //если такой элемент есть
            arr[item_number] = 0; //удалить
    }
    
    int binaryMassiv:: set:: min()
    {
        int minNumber = 0; //минимальное значение в виде номера массива
        //.. вычисление
        int value = convertToValue(minNumber);
        return value;
    }
    int binaryMassiv:: set:: max()
    {
        int maxNumber = 0; //минимальное значение в виде номера массива
        //.. вычисление
        int value = convertToValue(maxNumber);
        return value;
    }
    
}

//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________

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
        
        set& unite(set a, set b); //объединение множеств
        set& intersection(set a, set b); //пересечение множеств
        set& difference(set a, set b); //разность множеств
        
        set& find(set b, int x); //поиск элемента x в мн-вах this и b. Возвращаем ссылку на множество, в котором находится элемент или ссылку фиктивного пустого множества
        set& merge(set a, set b); //"слить" два множества в одно. возвращаем ссылку на новое множество
        
        void makenull(); //сделать множество пустым
        void insert(int x); //вставка элемента x в множество
        void del(int x); //удалить элемент x из множества
        void print(); //вывод множества на печать
        int min() const; //возвращает минимальное значение
        int max() const; //возвращает максимальное значение
        bool equal(set b); //эквивалентность множеств
        bool member(int x); //принадлежность элемента x множеству
        bool empty(); //проверка на пустоту множества
        bool checkIntersectability(); //проверить мн-во на пересекаемость
        set& assign(set b); //присваивание множеству this множество b
        
    private:
        node *tail;
        
        bool existX(int x) const; //ищет x во множестве, если находит возвращает true
        
        node* closestEl(int x) const; //ищет ближайший к x элемент в множестве и возвращает его положение
        node* searchPrev(node* el) const; //поиск предыдущего элемента от el
        node* searchX(int x) const; //ищет местоположение x в списке
        
        void clearList();
    };
}

circleList:: set:: set() {
    tail = nullptr;
}

circleList:: set:: ~set() {
    makenull();
}

void circleList:: set:: makenull() {
    if (tail != nullptr)
    {
        clearList();
    }
}

bool circleList:: set:: existX(int x) const {
    node *temp = tail;
    do
    {
        if (temp->x == x) //если элемент нашелся
            return true;
        else
            temp = temp->next; //не нашелся, ищем дальше по списку
    } while (temp != tail); //пока не вернулись к изначальному элементу
    return false;
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

int circleList:: set:: min() const { return tail->next->x; }
int circleList:: set:: max() const { return tail->x; }

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
    return nullptr;
}
void circleList:: set:: insert(int x)
{
    if (existX(x) != true) //если x еще нет в списке
    {
        if (tail == nullptr) //если список пуст
            tail = new node(x, tail); //создаем первый элемент
        
        if (x > max() || x < min()) //всегда добавляется после tail
        {
            node *el = new node(x, tail->next);
            tail->next = el;
            if (x > max())
                tail = tail->next; //если значение больше max, то он становится новым хвостом
        }
        
        
        
//        if (x < min())
//        {
//            node *el = new node(x, tail->next);
//            tail->next = el;
//        }
//        if (x > max())
//        {
//            node *el = new node(x, tail->next);
//            tail->next = el;
//            tail = tail->next;
//        }
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
    
//    position temp = head;
//    while (temp != nullptr)
//    {
//        if (temp->next == p) //нашли эту позицию
//            return temp;
//        temp = temp->next; //ищем и двигаемся по списку
//    }
//    return nullptr; //не нашли такую позицию
}
void circleList:: set:: del(int x)
{
    if (existX(x) == true) //если x есть в списке
    {
        if (x == min())
        {
            tail->next = tail->next->next;
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
//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________

namespace linkedList {
    class set {
    public:
        
    private:
        
    };
}

using namespace binaryMassiv;
int main(int argc, const char * argv[]) {
    set A(44, 0);
    A.insert(0);
    
}



//        if ((left_border < 0 && right_border < 0) || (left_border > 0 && right_border > 0))
//        if ((left_border < 0 && right_border > 0) || (left_border > 0 && right_border < 0))
