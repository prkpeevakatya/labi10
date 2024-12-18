#include <iostream>
#include <locale.h>

using namespace std;

// Тип данных, описывающий каждый отдельно взятый узел списка
struct Node
{
    int info;     // полезная информация, хранящаяся в этом узле
    Node* next;  // адрес следующего узла списка
    // (nullptr, если данный элемент является последним)
};

bool is_prime(int x)
{
    if (x == 1) return false;
    int r = sqrt(x);
    for (int d = 2; d <= r; d++)
        if (x % d == 0) return false;

    return true;
}
bool list_is_prime(Node* top)
{
    Node* p = top;
    while (p != nullptr)
    {
        if (is_prime(p->info)) return true;
        p = p->next;
    }
    return false;
}
bool is_not_prime(int x)
{
    if (x == 1) return true;
    int r = sqrt(x);
    for (int d = 2; d <= r; d++)
        if (x % d == 0) return true;

    return false;
}
bool list_is_not_prime(Node * top)
{
    Node * p = top;
    while (p != nullptr)
    {
        if (is_prime(p->info)) return false;
        p = p->next;
    }
    return true;
}




// Распечатать список
void print_list(Node* top)
{
    Node* p = top;  // Адрес текущего элемента списка
    while (p != nullptr) {
        cout << p->info << " ";  // Печатаем полезную информацию текущего узла
        p = p->next;  // Адрес следующего узла становится текущим
    }
}

// Функция, проверяющая, что все элементы списка с вершиной `top`
// упорядочены по неубыванию.
bool list_is_sorted(Node* top)
{
    Node* p = top; // Адрес текущего узла списка

    while (p->next != nullptr) {
        // Сравниваем числа в текущем узле и следующем
        if (p->info >= p->next->info)
            return false;
        else
            p = p->next;  // Адрес следующего узла становится текущим
    }

    return true;
}

bool is_sorted2(Node * top)
{
    Node * p = top;
    int q = p->info;
    int w = p->next->info;
    while (q > 10) q /= 10;
    while (w > 10) w /= 10;
    while (p->next != nullptr) {
        if ((((p->info) % 10) > ((p->next->info) % 10)) || (q > w)) return true;
        p = p->next;
    }
    return false;
}

bool contains_157(int x)
{
    while (x > 0)
    {
        int d = x % 10;
        if ((d == 1) || (d == 5) || (d == 7)) return true;
        x /= 10;
    }
    return false;
}

bool list_contains_157(Node* top)
{
    Node* p = top;
    while (p != nullptr)
    {
        if (contains_157(p->info)) return true;
        p = p->next;
    }
    return false;
}

// Отсортировать список по неубыванию (алгоритм сортировки обменами)
void sort_list(Node * top)
{
    for (Node * a = top; a->next != nullptr; a = a->next)
        for (Node * b = a->next; b->next != nullptr; b = b->next)
            if (a->info > b->info) swap(a->info, b->info);
}

// Продублировать в списке все элементы, делящиеся на 3
void duplicate_numbers(Node* top)
{
    Node* p = top;
    while (p != nullptr) {
        // Если число в текущем узле делится на 3
        if (list_is_prime(top)) {
            if (list_contains_157(top))
            {
                Node* q = new Node;  // Создаём новый узел
                q->info = p->info;    // и заполняем содержимое,
                q->next = p->next;    // а также прописываем адреса.
                p->next = q;
                p = q->next;
            }
        }
        else {
            p = p->next;  // Иначе адрес следующего узла становится текущим.
        }
    }
}



// Удалить из списка все элементы
void remove_numbers(Node * &top)
{
    while (top != nullptr && is_not_prime(top->info))
    {
        Node* temp = top->next;
        delete top;
        top = temp;
    }
    
    Node * p = top;
    while(p != nullptr && p->next != nullptr)
    {
        Node * temp = p->next;
        if (is_not_prime(temp->info))
        {
            p->next = temp->next;
            delete temp;
        }
        else
        {
            p = temp;
        }

   
    }
}






int main()
{
    setlocale(LC_ALL, "Russian");
    // Объявим переменную, в которой будет храниться адрес
    // первого узла списка (то есть адрес его вершины).
    // Изначально список пуст и узлов у него нет, даже вершины.
    // Поэтому top вначале равняется nullptr.
    Node* top = nullptr;

    int n;    // Количество элементов последовательности,
    cin >> n; // которое мы предварительно читаем с клавиатуры.

    // Первый элемент последовательности читаем отдельно, потому что
    // он разместится в вершине списка.
    int x;
    cin >> x;

    // Создаём вершину списка и размещаем в ней число `x`.
    top = new Node;
    top->info = x;
    top->next = nullptr;

    // Объявим вспомогательную переменную `pp`, в которой будем
    // хранить адрес последнего узла списка.
    // Пока что последний совпадает с первым.
    Node* pp = top;

    // Все остальные элементы последовательности читаем в цикле.
    for (int i = 1; i < n; i++) {
        cin >> x;
        Node* p = new Node;  // Создаём новый узел и получаем его адрес
        pp->next = p;  // Записываем адрес нового узла у предыдущего
        p->info = x;  // Записываем прочитанное число в новый узел
        p->next = nullptr;  // Пока что новый узел последний, и следующего у него нет.
        pp = p;  // на следующей итерации цикла новый узел станет предыдущим
    }

    cout << endl;
    cout << "Введённый список: ";
    print_list(top);

    cout << endl;

    if (is_sorted2(top))
    {
        remove_numbers(top);
        duplicate_numbers(top);
        

    }
    else sort_list(top);


    cout << endl;
    cout << "Введённый список: ";
    print_list(top);

    cout << endl;




    return 0;
}
