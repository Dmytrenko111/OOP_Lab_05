#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Controller {
    
public:
    int Order = 0;
    double Price = 0;
    string CarNumb;
    string Name;
    string Surname;
    int Age = 0;
    int Sum = 0;
    
    
    template <class type>
    void SetParent(type* cr) {
        this->CarNumb = cr->CarNumb;
        this->Name = cr->Name;
        this->Surname = cr->Surname;
        this->Age = cr->Age;
        cr->Sum += this->Order;
        this->Sum = cr->Sum;
    }
    virtual void PrintValues() {
        cout << "Car Number: " << CarNumb << endl << "Name: " << Name << endl << "Surname: " << Surname << endl << "Age: " << Age << endl << "Sum: " << Sum << endl << endl;
    }
    
    virtual void PrintFields() {
        cout << "Driver:\n";
        PrintValues();
        cout << "Order:\nCost of the order: " << Order << endl << "Price per km: " << Price <<"\n\n" << endl << endl;
    }
    
    virtual int get_order() { return Order; }
    
    virtual double get_price() { return Price; }
    
    Controller() {};
};


class CarTrans : public Controller {
    
public:
    
    
    void CopyCar(CarTrans * cr) {
        this->SetValues(cr->CarNumb, cr->Name, cr->Surname, cr->Age, cr->Sum);
    }
    
    void SetValues(string num, string name, string surname, int age, int sum) {
        this->CarNumb = num;
        this->Name = name;
        this->Surname = surname;
        this->Age = age;
        this->Sum = sum;
    }
    
    
    CarTrans(string num, string name, string surname, int age, int sum) {
        SetValues(num, name, surname, age, sum);
    }
    CarTrans() {}
    CarTrans(CarTrans* cr) {
        this->CopyCar(cr);
    }
};


class Taxi : public CarTrans {
    
public:
    void Copy(Taxi* tax) {
        SetValues(tax->Order, tax->Price);
        this->CarNumb = tax->CarNumb;
        this->Name = tax->Name;
        this->Surname = tax->Surname;
        this->Age = tax->Age;
        this->Sum = tax->Sum;
    }
    
    void SetValues(int order, double price) {
        this->Order = order;
        this->Price = price;
    }
    
    void PrintFields()
    {
        cout << "Driver:\n";
        PrintValues();
        cout << "Order:\nCost of the order: " << Order << endl << "Price per km: " << Price <<"\n\n"<< endl<<endl;
    }
    
    Taxi(int order, double price) : CarTrans() {
        SetValues(order, price);
    }
    
    Taxi(int order, double price, CarTrans* cr) : CarTrans() {
        SetValues(order, price);
        SetParent(cr);
    }
    
    Taxi() : CarTrans() {}
    Taxi(Taxi * tax) {
        Copy(tax);
    }
};


class Bus : public CarTrans {
private:
    int Count = 0;
    int MinCount = 4;
    int Length = 0;
public:
    
    void copy(Bus* tax) {
        SetValues(tax->Length, tax->Price,tax->Count);
        this->CarNumb = tax->CarNumb;
        this->Name = tax->Name;
        this->Surname = tax->Surname;
        this->Age = tax->Age;
        this->Sum = tax->Sum;
        this->Count = tax->Count;
        this->MinCount = tax->MinCount;
    }
    
    
    void SetValues(int length, double price,int count) {
        if (count < MinCount) throw;
        this->Count = count;
        this->Length = length;
        this->Price = price;
        this->Order = price * length * count;
    }
    
    Bus(int length, double price, int count) : CarTrans() {
        SetValues(length, price,count);
    }
    
    Bus(int length, double price,int count, CarTrans* cr) : CarTrans() {
        SetValues(length, price,count);
        SetParent(cr);
    }
    
    Bus() : CarTrans() {}
    Bus(Bus * tax) {
        copy(tax);
    }
};



void Swap1(Taxi* a1, Taxi* a2) {
    Taxi*  temp = new Taxi(a1);
    a1->Copy(a2);
    a2->Copy(temp);
}

void Swap2(CarTrans* a1, CarTrans* a2) {
    CarTrans*  temp = new CarTrans(a1);
    a1->CopyCar(a2);
    a2->CopyCar(temp);
}

void PrintArray1(Taxi* arr, int size) {
    for (int i = 0; i < size; i++)arr[i].PrintFields();
}

void PrintArray2(CarTrans* arr, int size) {
    for (int i = 0; i < size; i++)arr[i].PrintValues();
}

void SortByIncrease(CarTrans* arr, int size) {
    int min = 0;
    for (int i = 0; i < size; i++)
    {
        min = i;
        for (int j = i + 1; j < size; j++)
            min = (arr[j].Sum > arr[min].Sum) ? j : min;
        
        if (i != min)
        {
            Swap2(arr + i, arr + min);
        }
    }
}

int WholeSum(CarTrans * arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)sum += (arr + i)->Sum;
    return sum;
}

int main()
{
    CarTrans* c = new CarTrans[3];
    
    c[0].SetValues("AM 5665 KM", "Ruslan", "Malinovsky", 25, 0);
    c[1].SetValues("AV 7921 KV", "Roman", "Yaremchuk", 23, 0);
    c[2].SetValues("VS 0001 NS", "Oleksandr", "Zinchenko", 22, 0);
    
    Taxi* tax = new Taxi[10];
    
    srand(time(0));
    // cout << "Orders: \n";
    for (int i = 0; i < 10; i++) {
        tax[i] = new Taxi(100 + rand()%1000, 3 + rand() % 5,c + rand() % 3);
        tax[i].PrintFields();
    }
    
    cout << "Buses:\n";
    Bus* bs = new Bus[5];
    for (int i = 0; i < 5; i++) {
        bs[i] = new Bus(30 + rand() % 60,3 + rand()%7, 5 + rand() % 10, c + rand() % 3);
        bs[i].PrintFields();
    }
    
    SortByIncrease(c, 3);
    cout << "\n\nArray after sorting:\n\n";
    PrintArray2(c, 3);
    
    cout << "\n\nThe whole sum is " << WholeSum(c, 3) <<
    "\nThe most successful driver is " << c[0].Name << " " << c[0].Surname << " With total value of " << c[0].Sum<<"\n\n"<<endl;
    
    return 42;
}

/*
 #include <iostream>
 #include <string>
 #include <ctime>
 using namespace std;
 
 
 class controller {
 
 public:
 int order = 0;
 double price = 0;
 string num = "";
 string name = "";
 string surname = "";
 int age = 0;
 int sum = 0;
 
 
 template <class type>
 void set_parent(type* cr) {
 this->num = cr->num;
 this->name = cr->name;
 this->surname = cr->surname;
 this->age = cr->age;
 cr->sum += this->order;
 this->sum = cr->sum;
 }
 virtual void print_values() {
 cout << "NUMBER: " << num << endl << "NAME: " << name << endl << "SURNAME: " << surname << endl << "AGE: " << age << endl << "SUM: " << sum << endl << endl;
 }
 
 virtual void print_fields() {
 cout << "Driver:\n";
 print_values();
 cout << "Order:\nPrice: " << order << endl << "Price per km: " << price << endl << endl;
 }
 
 virtual int get_order() { return order; }
 
 virtual double get_price() { return price; }
 
 controller() {};
 };
 
 
 class car : public controller {
 
 public:
 
 void copy_car(car * cr) {
 this->set_values(cr->num, cr->name, cr->surname, cr->age, cr->sum);
 }
 
 void set_values(string num, string name, string surname, int age, int sum) {
 this->num = num;
 this->name = name;
 this->surname = surname;
 this->age = age;
 this->sum = sum;
 }
 
 
 car(string num, string name, string surname, int age, int sum) {
 set_values(num, name, surname, age, sum);
 }
 car() {}
 car(car* cr) {
 this->copy_car(cr);
 }
 };
 
 
 class taxi : public car {
 
 public:
 void copy(taxi* tax) {
 set_values(tax->order, tax->price);
 this->num = tax->num;
 this->name = tax->name;
 this->surname = tax->surname;
 this->age = tax->age;
 this->sum = tax->sum;
 }
 
 void set_values(int order, double price) {
 this->order = order;
 this->price = price;
 }
 
 taxi(int order, double price) : car() {
 set_values(order, price);
 }
 
 taxi(int order, double price, car* cr) : car() {
 set_values(order, price);
 set_parent(cr);
 }
 
 taxi() : car() {}
 taxi(taxi * tax) {
 copy(tax);
 }
 };
 
 
 class bus : public car {
 private:
 int count = 0;
 int min_count = 4;
 int length = 0;
 public:
 
 void copy(bus* tax) {
 set_values(tax->length, tax->price,tax->count);
 this->num = tax->num;
 this->name = tax->name;
 this->surname = tax->surname;
 this->age = tax->age;
 this->sum = tax->sum;
 this->count = tax->count;
 this->min_count = tax->min_count;
 }
 
 
 void set_values(int length, double price,int count) {
 if (count < min_count) throw;
 this->count = count;
 this->length = length;
 this->price = price;
 this->order = price * length * count;
 }
 
 bus(int length, double price, int count) : car() {
 set_values(length, price,count);
 }
 
 bus(int length, double price,int count, car* cr) : car() {
 set_values(length, price,count);
 set_parent(cr);
 }
 
 bus() : car() {}
 bus(bus * tax) {
 copy(tax);
 }
 };
 
 
 
 void swap(taxi* a1, taxi* a2) {
 taxi*  temp = new taxi(a1);
 a1->copy(a2);
 a2->copy(temp);
 }
 
 void swap(car* a1, car* a2) {
 car*  temp = new car(a1);
 a1->copy_car(a2);
 a2->copy_car(temp);
 }
 
 void print_array(taxi* arr, int size) {
 for (int i = 0; i < size; i++)arr[i].print_fields();
 }
 
 void print_array(car* arr, int size) {
 for (int i = 0; i < size; i++)arr[i].print_values();
 }
 
 void sort_by_increase(car* arr, int size) {
 int min = 0;
 int buf = 0;
 for (int i = 0; i < size; i++)
 {
 min = i;
 for (int j = i + 1; j < size; j++)
 min = (arr[j].sum > arr[min].sum) ? j : min;
 
 if (i != min)
 {
 swap(arr + i, arr + min);
 }
 }
 }
 
 int calculate_whole_sum(car * arr, int size) {
 int sum = 0;
 for (int i = 0; i < size; i++)sum += (arr + i)->sum;
 return sum;
 }
 
 int main()
 {
 system("color f0");
 
 car* c = new car[3];
 
 c[0].set_values("1", "JOHN", "SNOW", 42, 0);
c[1].set_values("2", "GENDALF", "GREY", 102, 0);
c[2].set_values("3", "LUKE", "SKYWALKER", 28, 0);

taxi* tax = new taxi[10];

srand(time(0));
cout << "Orders:\n";
for (int i = 0; i < 10; i++) {
    tax[i] = new taxi(100 + rand() % 1000, 3 + rand() % 5, c + rand() % 3);
    tax[i].print_fields();
}
cout << "Buses:\n";
bus* bs = new bus[5];
for (int i = 0; i < 5; i++) {
    bs[i] = new bus(30 + rand() % 60,3 + rand()%7, 5 + rand() % 10, c + rand() % 3);
    bs[i].print_fields();
}
sort_by_increase(c, 3);
cout << "\n\nArray after sorting:\n\n";
print_array(c, 3);

cout << "\n\nThe whole sum is " << calculate_whole_sum(c, 3) <<
"\nThe most successful driver is " << c[0].name << " " << c[0].surname << " With total value of " <<c[0].sum << endl;

return 42;
}
*/
