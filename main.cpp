#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include "sqlite3.h"
using namespace std;
#include "PyrotechnicDevice.h"

PyrotechnicPtr createRandomPyrotechnic()
{
    switch (rand() % 4)
    {
        case 0:
            return new Fireworks();
        case 1:
            return new Petard();
        case 2:
            return new Flapper();
        case 3:
            return new RomanCandles();
        default:
            return nullptr;
    }
}

void ContRandomPyrot(PyrotecCont* container, int count)
{
    for (int i = 0; i < count; ++i)
    {
        PyrotechnicPtr ptr = createRandomPyrotechnic();
        if (ptr != nullptr)
        {
            container->add(ptr);
        }
    }
}

void displayAllItemsWithVay(PyrotecCont* container, Iterator<PyrotechnicPtr>* iterator)
{
    for (iterator->First(); !iterator->IsDone(); iterator->Next())
    {
        PyrotechnicPtr cur = iterator->GetCurrent();
        cout << "Name: \t\t" << PyrotechnicName(cur->GetName())<< endl;
        cout << "Caliber: \t" << PyrotechnicCaliber(cur->GetCaliber()) <<endl;
        cout << "Time: \t\t" << PyrotechnicTime(cur->GetTime()) << endl << endl;
        if(cur->GetName() == NamePyrotechnic::Flapper)
        {
            cout<<endl;
            cur->ignite();
            cur->Vay();
            cout<<endl <<endl;
        }
    }
}


//БАЗА ДАННЫХ................................................
class SQLContIt
{
private:
    sqlite3* Db;
    int ind;
    int numColumns;

public:
    sqlite3_stmt *SQLStatement;

    SQLContIt(sqlite3 *database)
    {
        Db = database;
        sqlite3_prepare_v2(
                Db,
                "SELECT name, Caliber, ExpirationDate, WorkingHours FROM PyrotechnicDevice",
                 -1,
                 &SQLStatement,
                 NULL);
        numColumns = sqlite3_column_count(SQLStatement);
    };

    ~SQLContIt() { sqlite3_finalize(SQLStatement); }

    void First() { ind = 0; }

	void Next() { ind++; }

	bool IsDone() const { return ind >= numColumns;}

    string GetCurrent() const
    {
        if (SQLStatement == NULL || numColumns == 0) {
            return "";
        }

        const unsigned char *text = sqlite3_column_text(SQLStatement, ind);
        if (text != NULL)
        {
            return string(reinterpret_cast<const char *>(text));
        }
        else { return ""; }
    }
};

class SQLCont
{
private:
    sqlite3* Db;
    sqlite3_stmt *SQLStatement;

public:
    void CreateTable()
    {
        const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS PyrotechnicDevice ("
                "name TEXT,"
                "Caliber TEXT,"
                "ExpirationDate INTEGER,"
                "WorkingHours TEXT"
                ");";

        char *errmsg;
        int execResult = sqlite3_exec(
                Db,
                createTableSQL,
                NULL,
                NULL,
                &errmsg);

        if (execResult != SQLITE_OK)
        {
                cout << errmsg << endl;
                cout << "Error create Table" << endl;
        }
    }

    SQLCont()
    {
        int open = sqlite3_open16( "C://Users//Denchik//Desktop//C++//pyrotechnik//BazaDannich.db", &Db);
        if(open != SQLITE_OK){ cout << "Db open error" << sqlite3_errmsg(Db) << endl; }
        else { cout << "Db open OK " << endl; }
        CreateTable();
    };

    ~SQLCont()
    {
        char *errmsg;
        int execResult = sqlite3_exec(
            Db,
            "DELETE FROM PyrotechnicDevice",
            NULL,
            NULL,
            &errmsg);
        if (execResult != SQLITE_OK) { cout << "Error Delete table" << errmsg << endl; }
        else { cout << "Db table delete OK" << endl; }
        sqlite3_close(Db);
    };

    int Kol_vo()
    {
        int execResult  = sqlite3_prepare_v2(
            Db,
            "SELECT count(*) FROM PyrotechnicDevice",
            -1,
            &SQLStatement,
            NULL);
        int exec = sqlite3_step(SQLStatement);
        int kolvo = sqlite3_column_int(SQLStatement, 0);
        cout << "||||Pyrotechnic Device: " << kolvo << " ||||" << endl << endl;

    };

    void AddPyroDev()
    {
        NamePyrotechnic Name = static_cast<NamePyrotechnic>(rand()%4);
        CaliberPyrotechnic Caliber = static_cast<CaliberPyrotechnic>( rand()%6 );
        bool ExpirationDate = bool(rand()%2);
        TimePyrotechnic WorkingHours = static_cast<TimePyrotechnic>(rand()%4);

        string time;
        string name;
        string caliber;

        switch(Name)
        {
            case NamePyrotechnic::Fireworks : name = "Fireworks";
                    break;
            case NamePyrotechnic::Petard: name = "Petard";
                    break;
            case NamePyrotechnic::Flapper: name = "Flapper";
                    break;
            case NamePyrotechnic::RomanCandles: name = "RomanCandles";
                    break;
            default: name = "Unknown";
        }

        switch(Caliber)
        {
            case CaliberPyrotechnic::ZeroFive: caliber = "ZeroFive";
                    break;
            case CaliberPyrotechnic::OneK: caliber = "OneK";
                    break;
            case CaliberPyrotechnic::OneTwoK: caliber = "OneTwoK";
                    break;
            case CaliberPyrotechnic::OneFourK: caliber = "OneFourK";
                    break;
            case CaliberPyrotechnic::TwoK: caliber = "TwoK";
                    break;
            case CaliberPyrotechnic::ThreeK: caliber = "ThreeK";
                    break;
            default: caliber = "Unknown";
        }

        switch(WorkingHours)
        {
            case TimePyrotechnic::OneSecond: time = "One Second";
                    break;
            case TimePyrotechnic::TenSeconds: time = "Ten Seconds";
                    break;
            case TimePyrotechnic::ThirtySeconds: time = "Thirty Seconds";
                    break;
            case TimePyrotechnic::Minute: time = "Minute";
                    break;
            default: time = "Unknown";
        }

        string insertPD =
            "INSERT INTO PyrotechnicDevice (name, Caliber, ExpirationDate, WorkingHours) VALUES('"+name+"','" +time+"',"+(ExpirationDate ? "1" : "0")+",'"+caliber+"');";

        char *errmsg;
        int Result = sqlite3_exec(
            Db,
            insertPD.c_str(),
            NULL,
            NULL,
            &errmsg);

        if (Result != SQLITE_OK) { cout << "Error executing SQL statement: " << errmsg << endl; }
    }

    void countExpiredDevices()
    {
        sqlite3_stmt* statement;
        const char* tail;

        string query = "SELECT COUNT(*) FROM PyrotechnicDevice WHERE ExpirationDate = 1";

        int result = sqlite3_prepare_v2(
                    Db,
                    query.c_str(),
                    -1,
                    &statement,
                    &tail);

        result = sqlite3_step(statement);
        if (result == SQLITE_ROW)
        {
            int count = sqlite3_column_int(statement, 0);
            wcout << L"|||| Количество устройств пиротехники с истекшим сроком годности: " << count << " ||||" << endl << endl;
        }
    }
    SQLContIt *GetIterator() { return new SQLContIt(Db); }
};


int main()
{
    /*srand(time(0));

    VectPyrotCont vCon;
    ListPyrotCont lCon;
    ArrayPyrotCont aCon(10);

    ContRandomPyrot(&vCon, rand()%100);
    ContRandomPyrot(&lCon, rand()%100);
    ContRandomPyrot(&aCon, 10);

    cout << "Contents of vector container:" << endl << endl;
    cout <<"SIZE VECTOR: " <<vCon.size() << endl;
    vCon.displayContents();

    cout << "\nContents of list container:" << endl << endl;
    cout <<"SIZE LIST: " <<lCon.size() << endl;
    lCon.displayContents();

    cout << "\nContents of array container:" << endl << endl;
    cout <<"SIZE ARRAY: " <<aCon.size() << endl;
    aCon.displayContents();*/

    /*srand(time(0));

    VectPyrotCont vCon;
    ContRandomPyrot(&vCon, rand() % 30);

    Iterator<PyrotechnicPtr>* iterator = vCon.GetIterator();
    TimeItDecorator timeDecorator(iterator, TimePyrotechnic::Minute);

    cout << "SIZE continer: " << vCon.size() << endl << endl<< endl;
    int i = 1;
    for (timeDecorator.First(); !timeDecorator.IsDone(); timeDecorator.Next(),i++)
    {
        PyrotechnicPtr cur = timeDecorator.GetCurrent();
        cout << "Device " << i << ":" << endl;
        cout << "Name: \t\t" << PyrotechnicName(cur->GetName()) << endl;
        cout << "Caliber: \t" << PyrotechnicCaliber(cur->GetCaliber()) << endl;
        cout << "Time: \t\t" << PyrotechnicTime(cur->GetTime()) << endl << endl;
    }*/

    srand(time(0));
    setlocale(LC_ALL, "Russian");
    SQLCont db;
    db.AddPyroDev();

    for(int i = 0 ; i < rand() % 100; i++)
    {
        db.AddPyroDev();
    }
    db.Kol_vo();
    db.countExpiredDevices();

    SQLContIt* it = db.GetIterator();

    cout << "ALL PYROTECHNIC DEVICES:" << endl << endl;
    int i = 1;
    while(true)
    {
        if(sqlite3_step(it->SQLStatement) != SQLITE_ROW)
        {
            break;
        }

        cout << "( " << i << " )"<< endl;
        i++;

        for(it->First(); !it->IsDone(); it->Next())
        {

            cout << it->GetCurrent() << endl;
        }
        cout<<endl<<endl;
	}
    return 0;
}

//Из main проверка выполнения заданий 1,2,3
    /*Fireworks a;
    Petard b;
    RomanCandles c;
    Flapper d;

    cout<<"Firework:"<<endl;
    a.ignite();
    cout<<"Calibr: "<<static_cast<int>(a.GetCaliber())<<endl;
    cout<<"TimeWork: "<<static_cast<int>(a.GetTime())<<endl;
    a.Vay();
    a.defective();
    cout<<endl;

    cout<<"Petard:"<<endl;
    b.ignite();
    cout<<"Calibr: "<<static_cast<int>(b.GetCaliber())<<endl;
    cout<<"TimeWork: "<<static_cast<int>(b.GetTime())<<endl;
    b.Vay();
    b.defective();
    cout<<endl;

    cout<<"RomanCandles:"<<endl;
    c.ignite();
    cout<<"Calibr: "<<static_cast<int>(c.GetCaliber())<<endl;
    cout<<"TimeWork: "<<static_cast<int>(c.GetTime())<<endl;
    c.Vay();
    c.defective();
    cout<<endl;

    cout<<"Flapper:"<<endl;
    d.ignite();
    cout<<"Calibr: "<<static_cast<int>(d.GetCaliber())<<endl;
    cout<<"TimeWork: "<<static_cast<int>(d.GetTime())<<endl;
    d.Vay();
    d.defective();
    cout<<endl;*/

//Из main проверка выполнения задания 4
 /*//Создание контейнеров


    VectPyrotCont vCon;
    ListPyrotCont lCon;
    ArrayPyrotCont aCon(100); //вместимость 100

    Fireworks fireworks;
    Petard petard;
    Flapper flapper;

    //Добавление объектов
    vCon.add(&fireworks);
    vCon.add(&petard);
    vCon.add(&flapper);

    lCon.add(&petard);
    lCon.add(&flapper);
    lCon.add(&fireworks);
    lCon.add(&fireworks);

    //aCon.add(&fireworks);
    aCon.add(&flapper);
    aCon.add(&petard);
    //aCon.add(&fireworks);
    aCon.add(&petard);

    cout << "Vector size: " << vCon.size() << endl;
    cout << "List size: " << lCon.size() << endl;
    cout << "Array size: " << aCon.size() << endl << endl;

    cout << "Vector contains petard: " << vCon.contains(&petard) << endl;
    cout << "List contains flapper: " << lCon.contains(&flapper) << endl;
    cout << "Array contains fireworks: " << aCon.contains(&fireworks) << endl << endl;

    cout << "Displaying vector contents:" << endl << endl;
    vCon.displayContents();
    cout << endl;
    cout << "Displaying list contents:" << endl << endl;
    lCon.displayContents();
    cout << endl;
    cout << "Displaying array contents:" << endl << endl;
    aCon.displayContents();
    cout << endl;

    //очистка
    vCon.clear();
    lCon.clear();
    aCon.clear();*/

//Из main проверка выполнения задания 6
    /*VectPyrotCont container;

    container.add(new RomanCandles());
    container.add(new Fireworks());
    container.add(new Petard());
    container.add(new Flapper());
    container.add(new RomanCandles());
    container.add(new Petard());
    container.add(new Flapper());
    container.add(new RomanCandles());
    container.add(new Flapper());
    container.add(new Fireworks());
    container.add(new Flapper());

    DateItDecorator dateDecorator(container.GetIterator());
    TimeItDecorator timeDecorator(container.GetIterator(), TimePyrotechnic::Minute);
    CaliberItDecorator caliberDecorator(container.GetIterator(), CaliberPyrotechnic::TwoK);
    NameItDecorator nameDecorator(container.GetIterator(), NamePyrotechnic::RomanCandles);

    cout << "Filtering by expiration date:" << endl;
    for (dateDecorator.First(); !dateDecorator.IsDone(); dateDecorator.Next())
    {
        cout << "Pyrotechnic Device: " << PyrotechnicName(dateDecorator.GetCurrent()->GetName()) << endl;
    }

    cout << "\nFiltering by time:" << endl;
    for (timeDecorator.First(); !timeDecorator.IsDone(); timeDecorator.Next())
    {
        cout << "Pyrotechnic Device: " << PyrotechnicName(timeDecorator.GetCurrent()->GetName()) << endl;
    }

    cout << "\nFiltering by caliber:" << endl;
    for (caliberDecorator.First(); !caliberDecorator.IsDone(); caliberDecorator.Next())
    {
        cout << "Pyrotechnic Device: " << PyrotechnicName(caliberDecorator.GetCurrent()->GetName()) << endl;
    }

    cout << "\nFiltering by name (Roman Candles):" << endl;
    for (nameDecorator.First(); !nameDecorator.IsDone(); nameDecorator.Next())
    {
        cout << "Pyrotechnic Device: " << PyrotechnicName(nameDecorator.GetCurrent()->GetName()) << endl;
    }*/

//Из main пробный 8
    /*    srand(time(0));

    VectPyrotCont container;
    ContRandomPyrot(&container, rand()%30);

    Iterator<PyrotechnicPtr>* iterator = container.GetIterator();

    CaliberItDecorator caliberDecorator(iterator, CaliberPyrotechnic::TwoK);
    TimeItDecorator timeDecorator(&caliberDecorator, TimePyrotechnic::Minute);

    cout << "SIZE continer: " << container.size() << endl << endl<< endl;
    cout << "All pyrotechnic devices:" << endl << endl;
    displayAllItemsWithVay(&container, iterator);

    container.clear();*/
