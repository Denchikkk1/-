#ifndef PyrotechnicDeviceH
#define PyrotechnicDeviceH

#include"Pattern.h"


//...........................................................................
enum class NamePyrotechnic: int
{
    Fireworks = 0,
    Petard = 1,
    Flapper = 2,
    RomanCandles = 3,
    Unknown = -1
};

enum class CaliberPyrotechnic: int
{
    ZeroFive = 0,
    OneK= 1,
    OneTwoK = 2,
    OneFourK = 3,
    TwoK = 4,
    ThreeK = 5,
    Unknown = -1
};

enum class TimePyrotechnic: int
{
    OneSecond = 0,
    TenSeconds = 1,
    ThirtySeconds = 2,
    Minute = 3,
    Unknown = -1
};
//...........................................................................



class PyrotechnicDevice
{
protected:

    NamePyrotechnic name;
    CaliberPyrotechnic Caliber;
    bool ExpirationDate; //срок годности
    TimePyrotechnic WorkingHours; // время работы

public:
    //Конструктор
    PyrotechnicDevice() : name(NamePyrotechnic::Unknown), Caliber(CaliberPyrotechnic::Unknown),
                            ExpirationDate( false ), WorkingHours(TimePyrotechnic::Unknown) {}
    //Деструктор
    virtual ~PyrotechnicDevice() {}

    virtual void ignite() const = 0; // зажигание пиротехники

    virtual void defective() const = 0; // бракованная пиротехника

    virtual NamePyrotechnic GetName() const { return name; } // вывод названия

    virtual CaliberPyrotechnic GetCaliber() const { return Caliber; } // вывод калибра

    virtual TimePyrotechnic GetTime() const { return WorkingHours; } // вывод времени работы

    virtual void Vay() {} // определение вау эффекта

    bool Expiration() const { return ExpirationDate; } // просрочен или нет

};



//...........................................................................
class Fireworks : public PyrotechnicDevice
{
public:
    void ignite() const { wcout<< L"Yrrrraaaa, the fireworks have started"<<endl; }
    void defective() const { wcout<< L"Unfortunately marriage"<<endl; }
    NamePyrotechnic GetName() const { return NamePyrotechnic::Fireworks; }
    Fireworks() : PyrotechnicDevice() { Caliber = CaliberPyrotechnic::TwoK; }
    TimePyrotechnic GetTime() const { return TimePyrotechnic::Minute; }
    void Vay()
    {
        if((Caliber == CaliberPyrotechnic::ThreeK || Caliber == CaliberPyrotechnic::TwoK)&&
           (WorkingHours == TimePyrotechnic::Minute || WorkingHours == TimePyrotechnic::ThirtySeconds))
        {
            cout << "VAY EFFECT" << endl;
        }
        else
        {
            cout << "Not a vay effect" << endl;
        }
    }

};

class Petard : public PyrotechnicDevice
{
public:
    void ignite() const { wcout<< L"Yrrrraaaa, the petard have started"<< endl; }
    void defective() const { wcout<< L"Unfortunately marriage"<<endl; }
    NamePyrotechnic GetName() const { return NamePyrotechnic::Petard; }
    Petard() : PyrotechnicDevice() { Caliber = CaliberPyrotechnic::OneK; }
    TimePyrotechnic GetTime() const { return TimePyrotechnic::OneSecond; }
    void Vay()
    {
        if((Caliber == CaliberPyrotechnic::OneFourK )&&
           (WorkingHours == TimePyrotechnic::TenSeconds || WorkingHours == TimePyrotechnic::ThirtySeconds
            || WorkingHours == TimePyrotechnic::Minute))
        {
            cout << "VAY EFFECT" << endl;
        }
        else
        {
            cout << "Not a vay effect" << endl;
        }
    }

};

class Flapper : public PyrotechnicDevice
{
public:
    void ignite() const { wcout<< L"Yrrrraaaa, the flappers have started"<<endl; }
    void defective() const { wcout<< L"Unfortunately marriage"<<endl; }
    NamePyrotechnic GetName() const { return NamePyrotechnic::Flapper; }
    Flapper() : PyrotechnicDevice() { Caliber = CaliberPyrotechnic::ZeroFive; }
    TimePyrotechnic GetTime() const { return TimePyrotechnic::OneSecond; }
    void Vay()
    {
        cout << "VAYAAYYAYAYYAY" << endl;
    }

};

class RomanCandles : public PyrotechnicDevice
{
public:
    void ignite() const { wcout<< L"Yrrrraaaa, the roman candles have started"<<endl; }
    void defective() const { wcout<< L"Unfortunately marriage"<<endl; }
    NamePyrotechnic GetName() const { return NamePyrotechnic::RomanCandles; }
    RomanCandles() : PyrotechnicDevice() { Caliber = CaliberPyrotechnic::TwoK; }
    TimePyrotechnic GetTime() const { return TimePyrotechnic::ThirtySeconds; }
    void Vay()
    {
        if (WorkingHours == TimePyrotechnic::Minute || WorkingHours == TimePyrotechnic::ThirtySeconds)
        {
            cout << "VAY EFFECT" << endl;
        }
        else
        {
            cout << "Not a vay effect" << endl;
        }
    }

};
//...........................................................................

string PyrotechnicName(const NamePyrotechnic type)
{
    switch (type)
    {
        case NamePyrotechnic::Fireworks : return "Fireworks";
        case NamePyrotechnic::Petard : return "Petard";
        case NamePyrotechnic::Flapper : return "Flapper";
        case NamePyrotechnic::RomanCandles : return "Roman Candles";
        default : return "Unknown";
    }
}

string PyrotechnicCaliber(const CaliberPyrotechnic type)
{
    switch (type)
    {
        case CaliberPyrotechnic::ZeroFive : return "Zero Five";
        case CaliberPyrotechnic::OneK : return "One K";
        case CaliberPyrotechnic::OneTwoK : return "One, Two K";
        case CaliberPyrotechnic::OneFourK : return "One, Four K";
        case CaliberPyrotechnic::TwoK : return "Two K";
        case CaliberPyrotechnic::ThreeK : return "Three K";
        default : return "Unknown";
    }
}

string PyrotechnicTime (const TimePyrotechnic type)
{
    switch (type)
    {
        case TimePyrotechnic::OneSecond : return "One Second";
        case TimePyrotechnic::TenSeconds : return "Ten Seconds";
        case TimePyrotechnic::ThirtySeconds : return "Thirty Seconds";
        case TimePyrotechnic::Minute : return "Minute";
        default : return "Unknown";
    }
}

typedef PyrotechnicDevice *PyrotechnicPtr;


//Итераторы...........................................................................
class VPyrotContIterator : public Iterator<PyrotechnicPtr>
{
private:
    vector<PyrotechnicPtr>::const_iterator it;
    const vector<PyrotechnicPtr> *container;

public:
    VPyrotContIterator(const vector<PyrotechnicPtr> *cont)
    {
        container = cont;
        it = container->begin();
    }

    void First() { it = container->begin(); }
    void Next() { ++it; }
    bool IsDone() const { return it == container->end(); }
    PyrotechnicPtr GetCurrent() const { return *it; }
};

class LPyrotContIterator : public Iterator<PyrotechnicPtr>
{
private:
    list<PyrotechnicPtr>::const_iterator it;
    const list<PyrotechnicPtr> *container;

public:
    LPyrotContIterator(const list<PyrotechnicPtr> *cont)
    {
        container = cont;
        it = container->begin();
    }
    void First() { it = container->begin(); }
    void Next() { ++it; }
    bool IsDone() const { return it == container->end(); }
    PyrotechnicPtr GetCurrent() const { return *it; }
};

class APyrotContIterator : public Iterator<PyrotechnicPtr>
{
private:
    const PyrotechnicPtr* ptr;
    int count;
    int index;

public:
    APyrotContIterator(const PyrotechnicPtr* Ptr, int cou)
    {
        ptr = Ptr;
        count = cou;
        index = 0;
    }

    void First() { index = 0; }
    void Next() { ++index; }
    bool IsDone() const { return index >= count; }
    PyrotechnicPtr GetCurrent() const { return ptr[index]; }
};
//...........................................................................


//Контейнеры...........................................................................
//Создание базового класса контейнера, от которого потом будут созданы контейнеры на основе вектора, списка и массива
class PyrotecCont
{
public:
    virtual void add(PyrotechnicPtr item) = 0; //Добавляет элемент в контейнер
    virtual void remove(PyrotechnicPtr item) = 0; //Удаляет указанный элемент из контейнера
    virtual bool contains(PyrotechnicPtr item) const = 0; //Проверяет, содержится ли указанный элемент в контейнере
    virtual void clear() = 0;//Очищает контейнер, удаляя все его элементы
    virtual int size() const = 0; //Возвращает количество элементов в контейнере
    virtual void displayContents() const = 0; //Выводит содержимое контейнера
    virtual ~PyrotecCont() {}//деструктор для правильного удаления объектов наследников
    virtual Iterator<PyrotechnicPtr>* GetIterator() = 0;
};

//Контейнер на основе вектора
class VectPyrotCont : public PyrotecCont
{
private:
    vector<PyrotechnicPtr> container;

public:
    void add(PyrotechnicPtr item) { container.push_back(item); }
    void remove(PyrotechnicPtr item)
    {
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            if (*it == item)
            {
                container.erase(it);
                break;
            }
        }
    }
    bool contains(PyrotechnicPtr item) const
    {
        for (const auto& elem : container)
        {
            if (elem == item)
            {
                cout << "Yes ";
                return true;
            }
        }
        cout << "No ";
        return false;
    }
    void clear() { container.clear(); }
    int size() const { return container.size(); }
    void displayContents() const
    {
        for (const auto& item : container)
        {
            cout << "Pyrotechnic Device: " << PyrotechnicName(item->GetName()) << endl;
        }
    }

    Iterator<PyrotechnicPtr> *GetIterator()
    {
        return new VPyrotContIterator(&container);
    }
};

//Контейнер на основе списка
class ListPyrotCont : public PyrotecCont
{
private:
    list<PyrotechnicPtr> container;

public:
    void add(PyrotechnicPtr item) { container.push_back(item); }
    void remove(PyrotechnicPtr item) { container.remove(item); }
    bool contains(PyrotechnicPtr item) const
    {
        for (const auto& elem : container)
        {
            if (elem == item)
            {
                cout << "Yes ";
                return true;
            }
        }
        cout << "No ";
        return false;
    }
    void clear() { container.clear(); }
    int size() const { return container.size(); }
    void displayContents() const
    {
        for (const auto& item : container)
        {
            cout << "Pyrotechnic Device: " << PyrotechnicName(item->GetName()) << endl;
        }
    }
    Iterator<PyrotechnicPtr> *GetIterator()
    {
        return new LPyrotContIterator(&container);
    }
};

//Контейнер на основе массива
class ArrayPyrotCont : public PyrotecCont
{
private:
    PyrotechnicPtr* container;
    int capacity; //Вместимость контейнера
    int count; //текущее количество элементов в контейнере

public:
    ArrayPyrotCont(int initialCapacity)
    {
        capacity = initialCapacity;
        count = 0;
        container = new PyrotechnicPtr[capacity];
    }
    ~ArrayPyrotCont() { delete[] container; }
    void add(PyrotechnicPtr item)
    {
        if (count < capacity)
        {
            container[count++] = item;
        }
        else
        {
            cout << "Container is full" << endl;
        }
    }
    void remove(PyrotechnicPtr item)
    {
        for (int i = 0; i < count; ++i)
        {
            if (container[i] == item)
            {
                for (int j = i; j < count - 1; ++j)
                {
                    container[j] = container[j + 1];
                }
                container[count - 1] = nullptr; //очистка последнегог указатель
                --count;
                break;
            }
        }
    }
    bool contains(PyrotechnicPtr item) const
    {
        for (int i = 0; i < count; ++i)
        {
            if (container[i] == item)
            {
                cout << "Yes ";
                return true;
            }
        }
        cout << "No ";
        return false;
    }
    void clear()
    {
        for (int i = 0; i < count; ++i)
        {
            container[i] = nullptr;
        }
        count = 0;
    }
    int size() const { return count; }
    void displayContents() const
    {
        for (int i = 0; i < count; ++i)
        {
            if (container[i] != nullptr)
            {
                cout << "Pyrotechnic Device: " << PyrotechnicName(container[i]->GetName()) << endl;
            }
        }
    }
    Iterator<PyrotechnicPtr> *GetIterator()
    {
        return new APyrotContIterator(container, count);
    }
};
//...........................................................................


//Декораторы...........................................................................
class DateItDecorator : public Iterator<PyrotechnicPtr> //декоратор пропускает элементы, у которых срок годности истек
{
private:
    Iterator<PyrotechnicPtr>* iterator;

public:
    DateItDecorator(Iterator<PyrotechnicPtr>* it) { iterator = it; }
    void First()
    {
        iterator->First();
        while (!iterator->IsDone() && iterator->GetCurrent()->Expiration())
        {
            iterator->Next();
        }
    }
    void Next()
    {
        iterator->Next();
        while (!iterator->IsDone() && iterator->GetCurrent()->Expiration())
        {
            iterator->Next();
        }
    }
    bool IsDone() const { return iterator->IsDone(); }
    PyrotechnicPtr GetCurrent() const { return iterator->GetCurrent(); }
};


class TimeItDecorator : public Iterator<PyrotechnicPtr> //декоратор фильтрует элементы по времени работы
{
private:
    Iterator<PyrotechnicPtr>* iterator;
    TimePyrotechnic targetTime;

public:
    TimeItDecorator(Iterator<PyrotechnicPtr>* it, TimePyrotechnic time)
    {
        iterator = it;
        targetTime = time;
    }
    void First()
    {
        iterator->First();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetTime() != targetTime)
        {
            iterator->Next();
        }
    }
    void Next()
    {
        iterator->Next();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetTime() != targetTime)
        {
            iterator->Next();
        }
    }
    bool IsDone() const { return iterator->IsDone(); }
    PyrotechnicPtr GetCurrent() const { return iterator->GetCurrent(); }
};


class CaliberItDecorator : public Iterator<PyrotechnicPtr> //декоратор фильтрует элементы по калибру
{
private:
    Iterator<PyrotechnicPtr>* iterator;
    CaliberPyrotechnic targetCaliber;

public:
    CaliberItDecorator(Iterator<PyrotechnicPtr>* it, CaliberPyrotechnic caliber)
    {
        iterator = it;
        targetCaliber = caliber;
    }
    void First()
    {
        iterator->First();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetCaliber() != targetCaliber)
        {
            iterator->Next();
        }
    }
    void Next()
    {
        iterator->Next();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetCaliber() != targetCaliber)
        {
            iterator->Next();
        }
    }
    bool IsDone() const { return iterator->IsDone(); }
    PyrotechnicPtr GetCurrent() const { return iterator->GetCurrent(); }
};


class NameItDecorator : public Iterator<PyrotechnicPtr> //фильтрует элементы по названию
{
private:
    Iterator<PyrotechnicPtr>* iterator;
    NamePyrotechnic targetName;

public:
    NameItDecorator(Iterator<PyrotechnicPtr>* it, NamePyrotechnic name)
    {
        iterator = it;
        targetName = name;
    }
    void First()
    {
        iterator->First();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetName() != targetName)
        {
             iterator->Next();
        }
    }
    void Next()
    {
        iterator->Next();
        while (!iterator->IsDone() && iterator->GetCurrent()->GetName() != targetName)
        {
            iterator->Next();
        }
    }
    bool IsDone() const { return iterator->IsDone(); }
    PyrotechnicPtr GetCurrent() const { return iterator->GetCurrent(); }
};

//...........................................................................



#endif // PyrotechnicDeviceH
