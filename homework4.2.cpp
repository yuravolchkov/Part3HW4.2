#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


class Address
{
private:
    std::string City, Street;
    int HouseNumber, FlatNumber;

public:
    Address() :City("UnknownCity"), Street("UnknownStreet"), HouseNumber(0), FlatNumber(0)
    {
    }

    void setCity(std::string InputCity)
    {
        this->City = InputCity;
    }

    void setStreet(std::string InputStreet)
    {
        this->Street = InputStreet;
    }

    void setHouseNumber(int InputHouseNumber)
    {
        this->HouseNumber = InputHouseNumber;
    }

    void setFlatNumber(int InputFlatNumber)
    {
        this->FlatNumber = InputFlatNumber;
    }

    std::string getCity()
    {
        return City;
    }

    std::string getStreet()
    {
        return Street;
    }

    int getHouseNumber()
    {
        return HouseNumber;
    }

    int getFlatNumber()
    {
        return FlatNumber;
    }

    std::string DataComporator()
    {
        return getCity() + ", " + getStreet() + ", " + std::to_string(getHouseNumber()) + ", " + std::to_string(getFlatNumber());
    }
};

//создание массива из классов
Address *CreateCatalog (int &Outputsize, std::string C_path)
{
int InputHouseNumber, InputFlatNumber, C_Size;
std::string InputCity, InputStreet;
std::ifstream C_fin(C_path);
C_fin >> C_Size;
Outputsize = C_Size;

Address* C_AddCatalog = new Address[C_Size+1];
// +1вый элемент массива будет использован как переменная для хранения промежуточных результатов.
//заполнение массива из файла
for (int i = 0; i < C_Size; i++)
    {
        C_fin >> InputCity;
        C_AddCatalog[i].setCity(InputCity);
        C_fin >> InputStreet;
        C_AddCatalog[i].setStreet(InputStreet);
        C_fin >> InputHouseNumber;
        C_AddCatalog[i].setHouseNumber(InputHouseNumber);
        C_fin >> InputFlatNumber;
        C_AddCatalog[i].setFlatNumber(InputFlatNumber);
    }
// Закрыть файл после чтения
C_fin.close();
return C_AddCatalog;
}

void sort_func(Address* sort_AddCatalog, int &size)
{
 for (bool i = 0; i != 1;)
    {
        i = 1;
        for (int j = 0; j < size - 1; j++)
        {
            //Сортировка городов по алфавиту
            if (sort_AddCatalog[j].getCity() > sort_AddCatalog[j + 1].getCity())
            {
                sort_AddCatalog[size].setCity(sort_AddCatalog[j].getCity());
                sort_AddCatalog[size].setStreet(sort_AddCatalog[j].getStreet());
                sort_AddCatalog[size].setHouseNumber(sort_AddCatalog[j].getHouseNumber());
                sort_AddCatalog[size].setFlatNumber(sort_AddCatalog[j].getFlatNumber());
                sort_AddCatalog[j].setCity(sort_AddCatalog[j+1].getCity());
                sort_AddCatalog[j].setStreet(sort_AddCatalog[j+1].getStreet());
                sort_AddCatalog[j].setHouseNumber(sort_AddCatalog[j+1].getHouseNumber());
                sort_AddCatalog[j].setFlatNumber(sort_AddCatalog[j+1].getFlatNumber());
                sort_AddCatalog[j+1].setCity(sort_AddCatalog[size].getCity());
                sort_AddCatalog[j+1].setStreet(sort_AddCatalog[size].getStreet());
                sort_AddCatalog[j+1].setHouseNumber(sort_AddCatalog[size].getHouseNumber());
                sort_AddCatalog[j+1].setFlatNumber(sort_AddCatalog[size].getFlatNumber());
                i = 0;
            }
            //Сортировка улиц по алфавиту
            else if ((sort_AddCatalog[j].getCity() == sort_AddCatalog[j + 1].getCity()) && (sort_AddCatalog[j].getStreet() > sort_AddCatalog[j + 1].getStreet()))
            {
                sort_AddCatalog[size].setStreet(sort_AddCatalog[j].getStreet());
                sort_AddCatalog[size].setHouseNumber(sort_AddCatalog[j].getHouseNumber());
                sort_AddCatalog[size].setFlatNumber(sort_AddCatalog[j].getFlatNumber());
                sort_AddCatalog[j].setStreet(sort_AddCatalog[j + 1].getStreet());
                sort_AddCatalog[j].setHouseNumber(sort_AddCatalog[j + 1].getHouseNumber());
                sort_AddCatalog[j].setFlatNumber(sort_AddCatalog[j + 1].getFlatNumber());
                sort_AddCatalog[j + 1].setStreet(sort_AddCatalog[size].getStreet());
                sort_AddCatalog[j + 1].setHouseNumber(sort_AddCatalog[size].getHouseNumber());
                sort_AddCatalog[j + 1].setFlatNumber(sort_AddCatalog[size].getFlatNumber());
                i = 0;
            }
        }
    }
}

void Output_Func(std::string Out_path, int &Out_Size, Address* Out_AddCatalog)
{
    std::ofstream fout(Out_path);
    fout << Out_Size << std::endl;
    for (int i = 0; i < Out_Size; i++)
    {
        fout << Out_AddCatalog[i].DataComporator() << std::endl;
    }
    // Закрыть файл после записи
    fout.close();
}


int main()
{
    setlocale(LC_ALL, "ru"); // задать русский текст
    std::system("chcp 1251"); // настроить кодировку консоли
    std::system("cls"); // очистить экран
    std::string TotalString, path_input = "in.txt", path_output = "out.txt";
    int CatalogIndex;
    Address* AddCatalog = CreateCatalog(CatalogIndex, path_input);
    // сортировка пузырьком
    sort_func(AddCatalog, CatalogIndex);
    //вывод массива в файл
    Output_Func(path_output, CatalogIndex, AddCatalog);
    // Очистить память после использования программы
    delete[] AddCatalog;
    return 1;
}