#include <iostream>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

class Customer
{
private:
    std::string name;
    std::string surname;
    std::string phone;

public:
    Customer(std::string name = "Noname",
             std::string surname = "Noname",
             std::string phone = "0000000000000") : name(name), surname(surname), phone(phone) {}

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getPhone() const { return phone; }

    void setName(std::string name)
    {
        this->name = name;
    }
    void setSurname(std::string surname)
    {
        this->surname = surname;
    }
    void setPhone(std::string phone)
    {
        this->phone = phone;
    }

    ~Customer() {}
};

class Item
{
protected:
    std::string name;
    double price;

public:
    Item(std::string name = "Undefined", double price = 0.0) : name(name), price(price) {}
    std::string getName() const { return name; }

    void setName(std::string name)
    {
        this->name = name;
    }
    void setPrice(double price)
    {
        this->price = price;
    }

    virtual double getPrice() const { return price; }
    virtual ~Item() {}
};

class Count_Item : public Item
{
private:
    int amount;

public:
    Count_Item(std::string name, double price, int amount) : Item(name, price), amount(amount) {}

    int getAmount() const { return amount; }
    void setAmount(int amount)
    {
        this->amount = amount;
    }

    double getPrice() const override { return amount * price; }

    ~Count_Item() {}
};

class Uncount_Item : public Item
{
private:
    double amount;

public:
    Uncount_Item(std::string name, double price, double amount) : Item(name, price), amount(amount) {}

    double getAmount() const { return amount; }
    void setAmount(double amount)
    {
        this->amount = amount;
    }

    double getPrice() const override { return amount * price; }

    ~Uncount_Item() {}
};

class Reciept
{
private:
    int discount;
    double totalPrice;

public:
    Reciept(int discount = 0) : discount(discount) {}

    int getDiscount() const { return discount; }
    void setDiscount(int discount)
    {
        this->discount = discount;
    }

    void create(int orderNumber, const std::string &customerName, double totalPrice, const std::vector<Item *> &items)
    {
        this->totalPrice = totalPrice - (totalPrice * discount / 100.0);
        std::cout << std::setfill(' ');
        std::cout << "ЧЕК ЗАКАЗА № " << orderNumber << std::endl;
        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout.setf(std::ios::showpoint);
        std::cout.setf(std::ios::showpos);
        std::cout << std::fixed << std::setprecision(2);

        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << "|" << std::left << std::setw(45) << " Наименование товара "
                  << "|" << std::right << std::setw(22) << " Стоимость " << "|" << std::endl;

        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');

        for (Item *i : items)
        {
            std::cout << "|" << std::left << std::setw(45) << i->getName();
            std::cout << "|" << std::right << std::setw(22) << i->getPrice() << "|" << std::endl;
        }

        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << "Покупатель: " << customerName << std::endl;

        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout.unsetf(std::ios::showpos);
        std::cout << "ИТОГО: " << this->totalPrice << " руб. " << std::endl;
        std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;

        std::ofstream ofile("reciept_book.txt", std::ios::app);

        if (ofile.fail() || ofile.bad())
        {
            std::cout << "Ошибка: Не удалось открыть файл для записи!" << std::endl;
            ofile.clear();
            return;
        }

        if (ofile.good())
        {
            ofile << std::setfill(' ');
            ofile << "ЧЕК ЗАКАЗА №" << orderNumber << std::endl;
            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;
            ofile << std::setfill(' ');
            ofile.setf(std::ios::showpos);
            ofile.setf(std::ios::showpoint);
            ofile << std::fixed << std::setprecision(2);
            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;
            ofile << std::setfill(' ');

            ofile << "|" << std::left << std::setw(45) << "Наименование товара"
                  << "|" << std::right << std::setw(22) << "Стоимость" << "|" << std::endl;
            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;
            ofile << std::setfill(' ');

            for (Item *i : items)
            {
                ofile << "|" << std::left << std::setw(45) << i->getName();
                ofile << "|" << std::right << std::setw(22) << i->getPrice() << "|" << std::endl;
            }

            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;
            ofile << std::setfill(' ');
            ofile << "Покупатель: " << customerName << std::endl;

            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;
            ofile << std::setfill(' ');
            ofile.unsetf(std::ios::showpos);
            ofile << "ИТОГО: " << this->totalPrice << " руб. " << std::endl;
            ofile << std::setfill('=') << std::setw(70) << "" << std::endl;

            ofile.close();
        }
    }
    void showReciept(int orderNumber, const std::string &customerName, const std::vector<Item *> &items)
    {
        std::cout << std::setfill(' ');
        std::cout << "Чек заказа № " << orderNumber << std::endl;
        std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout.setf(std::ios::showpoint);
        std::cout << std::fixed << std::setprecision(2);

        std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << "|" << std::left << std::setw(45) << " Наименование товара "
                  << "|" << std::right << std::setw(22) << " Стоимость " << "|" << std::endl;

        std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');

        for (Item *i : items)
        {
            std::cout << "|" << std::left << std::setw(45) << i->getName();
            std::cout << "|" << std::right << std::setw(22) << i->getPrice() << "|" << std::endl;
        }

        std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << "Покупатель: " << customerName << std::endl;

        std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
        std::cout << std::setfill(' ');
    }

    ~Reciept() {}
};

class Order
{
private:
    int number;
    static int count;
    std::vector<Item *> items;
    Customer *customer;
    Reciept reciept;
    
public:
    Order(Customer *customer) : customer(customer)
    {
        count++;
        number = count;
    }

    void addItem(Item *item)
    {
        items.push_back(item);
    }

    double getTotalPrice() const
    {
        double total = 0;
        for (Item *n : items)
        {
            total += n->getPrice();
        }
        return total;
    }

    void setDiscount(int discount)
    {
        reciept.setDiscount(discount);
    }
    void showcheck()
    {
        if (items.empty())
        {
            std::cout << "Ваш заказ пока пуст." << std::endl;
            return;
        }

        reciept.showReciept(number, customer->getName() + " " + customer->getSurname(), items);
    }

    void checkout()
    {
        if (items.empty())
        {
            std::cout << "Ваш заказ пока пуст." << std::endl;
            return;
        }

        reciept.create(number, customer->getName() + " " + customer->getSurname(), getTotalPrice(), items);
    }

    int getOrderAmount() const { return items.size(); }

    void sortByPrice()
    {
        for (int i = 0; i < getOrderAmount(); i++)
        {
            for (int j = 0; j < getOrderAmount() - 1; j++)
            {
                if (items[j]->getPrice() < items[j + 1]->getPrice())
                {
                    std::swap(items[j], items[j + 1]);
                }
            }
        }
    }
    int findItem(const std::string &findItemName) const
    {
        for (int i = 0; i < items.size(); i++)
        {
            if ((items[i]->getName()) == findItemName)
                return i + 1;
        }
        return -1;
    }
    void deleteItemByName(const std::string &nameItem)
    {

        for (int i = 0; i < items.size(); i++)
        {
            if (items[i]->getName() == nameItem)
            {
                delete items[i];
                items.erase(items.begin() + i);
                i--;
            }
        }
    }

    ~Order()
    {
        for (Item *item : items)
        {
            delete item;
        }
    }
};

int Order::count = 0;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n = 1;
    while (n != 0)
    {
        std::cout << "Здравствуйте! Желаете сделать новый заказ?" << std::endl;
        std::cout << "[1] - Да" << std::endl;
        std::cout << "[0] - ВЫХОД" << std::endl;

        std::cin >> n;
        switch (n)
        {
        case 1:
        {

            std::string inputName, inputSurname, inputPhone;
            std::cout << std::setfill(' ');
            std::cout << "ДАННЫЕ КЛИЕНТА" << std::endl;
            std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
            std::cout << "Введите имя: ";
            std::cin >> inputName;

            std::cout << "Введите фамилию: ";
            std::cin >> inputSurname;

            std::cout << "Введите номер телефона (+375XXXXXXXXX): ";
            std::cin >> inputPhone;
            std::cout << std::endl;
            Customer cust1(inputName, inputSurname, inputPhone);
            Order myOrder(&cust1);

            int choice = -1;

            while (choice != 0)
            {
                std::cout << std::setfill(' ');
                std::cout << "КАТАЛОГ ТОВАРОВ" << std::endl;
                std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
                std::cout << std::setfill(' ');

                std::cout << "[1] Доска (дуб, 12.75 руб/шт)" << std::endl;
                std::cout << "[2] Доска (ясень, 11.15 руб/шт)" << std::endl;
                std::cout << "[3] Песок (весовой, 15.0 руб/куб)" << std::endl;
                std::cout << "[4] Цемент (весовой, 20.20 руб/куб)" << std::endl;
                std::cout << "[5] Гвоздь (обычный, 15.0 руб/100 шт.)" << std::endl;

                std::cout << "ДЕЙСТВИЯ С ЗАКАЗОМ" << std::endl;
                std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << "[6] Просмотреть текущий заказ" << std::endl;
                std::cout << "[7] Удалить товар из заказа" << std::endl;
                std::cout << "[8] Отсортировать заказ по стоимости(по убыванию)" << std::endl;
                std::cout << "[9] Поиск по названию товара в заказе" << std::endl;
                std::cout << "[10] Применить скидку" << std::endl;
                std::cout << "[0] Оформить заказ и получить чек" << std::endl;
                std::cout << "Выберите номер товара (действия): ";

                std::cin >> choice;
                std::cin.ignore(1000, '\n');
                switch (choice)
                {
                case 1:
                {
                    int amount;
                    std::cout << "Введите количество досок из дуба (шт): ";
                    std::cin >> amount;
                    std::cin.ignore(1000, '\n');
                    myOrder.addItem(new Count_Item("Доска (дуб)", 12.75, amount));
                    std::cout << "Доска (дуб) добавлена в заказ!" << std::endl;
                    break;
                }
                case 2:
                {
                    int amount;
                    std::cout << "Введите количество досок из ясеня (шт): ";
                    std::cin >> amount;
                    std::cin.ignore(1000, '\n');
                    myOrder.addItem(new Count_Item("Доска (ясень)", 11.15, amount));
                    std::cout << "Доска (ясень) добавлена в заказ!" << std::endl;
                    break;
                }
                case 3:
                {
                    double amount;
                    std::cout << "Введите объем песка (куб.м): ";
                    std::cin >> amount;
                    std::cin.ignore(1000, '\n');
                    myOrder.addItem(new Uncount_Item("Песок (куб)", 15.0, amount));
                    std::cout << "Песок добавлен в заказ!" << std::endl;
                    break;
                }
                case 4:
                {
                    double amount;
                    std::cout << "Введите объем цемента (куб.м): ";
                    std::cin >> amount;
                    std::cin.ignore(1000, '\n');
                    myOrder.addItem(new Uncount_Item("Цемент (куб)", 20.20, amount));
                    std::cout << "Цемент добавлен в заказ!" << std::endl;
                    break;
                }
                case 5:
                {
                    int amount;
                    std::cout << "Введите количество порций гвоздей (по 100 шт): ";
                    std::cin >> amount;
                    std::cin.ignore(1000, '\n');
                    myOrder.addItem(new Count_Item("Гвозди (100шт)", 15.0, amount));
                    std::cout << "Гвозди добавлены в заказ!" << std::endl;
                    break;
                }
                case 6:
                {
                    myOrder.showcheck();
                    break;
                }
                case 7:
                {
                    std::cout << "Введите полное название товара" << std::endl;
                    std::string nameItem;

                    std::getline(std::cin, nameItem);
                    if (myOrder.findItem(nameItem) == -1)
                    {
                        std::cout << "Товар не найден." << std::endl;
                        break;
                    }
                    else
                    {
                        myOrder.deleteItemByName(nameItem);
                        std::cout << "Товар удален." << std::endl;
                        break;
                    }
                    break;
                }

                case 8:
                {
                    myOrder.sortByPrice();
                    std::cout << "Заказ отсортирован по убыванию стоимости!" << std::endl;
                    break;
                }

                case 9:
                {
                    std::cout << "Введите полное название товара" << std::endl;
                    std::string nameItem;

                    std::getline(std::cin, nameItem);
                    if (myOrder.findItem(nameItem) == -1)
                    {
                        std::cout << "Товар не найден." << std::endl;
                    }
                    else
                    {
                        std::cout << "Товар в заказе / под номером: " << myOrder.findItem(nameItem) << std::endl;
                    }
                    break;
                }
                case 10:
                {
                    std::cout << "Введите % скидки" << std::endl;
                    int discount;
                    while (true)
                    {
                        std::cin >> discount;
                        if (discount < 100 && discount > 0)
                            break;
                    }
                    myOrder.setDiscount(discount);
                    std::cout << "Cкидка успешно применена!" << std::endl;
                    break;
                }
                case 0:
                {
                    std::cout << "Переход к оформлению заказа..." << std::endl;
                    break;
                }

                default:
                    std::cout << "Неверный выбор. Пожалуйста, введите число от 0 до 10." << std::endl;
                    break;
                }
            }

            std::cout << std::left << std::setw(70) << "ОФОРМЛЕНИЕ ЗАКАЗА" << std::endl;
            std::cout << std::right << std::setfill('=') << std::setw(70) << "" << std::endl;
            std::cout << std::setfill(' ');
            myOrder.checkout();

            break;
        }

        case 2:
        {

            break;
        }

        case 0:
        {
            std::cout << "До свидания!";
            return 0;
        }
        }
    }
}
