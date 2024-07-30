#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <ranges>
#include <mutex>
#include <thread>
#include <fstream>
#include <vector>

#ifndef HEADER_H
#define HEADER_H

class Student {
private:
    std::string _name;
    std::string _group;
    std::list<int> _marks;
    
public:
    Student();
    Student(std::string name, std::string group, std::list<int> marks);
    ~Student()=default;
    bool checkDebt();
    bool checkFive();
    int sumMarks(int m);
    void changeMarks(std::list<int>& marks);
    std::string getGroup();
    std::string getName();
    friend std::ostream& operator<<(std::ostream& out, Student& st);
};

class Group {
    std::string _nameGroup;
    std::list<Student> _group;
public:
    Group();
    Group(std::string nameGroup, std::list<Student> group);
    ~Group()=default;
    std::list<Student> operator+(const Student& st);
    std::string getGroup();
    std::list<Student> getStudents();
    void changeGroup(Student& st);
    float middleMarks(int number);
    std::list<Student> check(int m);
    friend std::ostream& operator<<(std::ostream& out, Group& gr);
};

void enterMarks(std::string& name, std::string& group, std::list<int>& marks) {
    try {
        char m, m1, m2;
        std::cout << "Введите ФИО студента, группу и оценки" << std::endl;
        std::cin.ignore();
        std::cout<< "ФИО: "; getline(std::cin, name);
        std::cout << "Группа: "; getline(std::cin, group);
        std::cout << "Математика: "; std::cin >> m;
        if (!std::isdigit(m)) {
            throw std::runtime_error("Введите число");
        }
        marks.push_back(static_cast<int>(m - '0'));
        std::cout << "АЯ: "; std::cin >> m1;
        if (!std::isdigit(m1)) {
            throw std::runtime_error("Введите число");
        }
        marks.push_back(static_cast<int>(m1 - '0'));
        std::cout << "Физика: "; std::cin >> m2;
        if (!std::isdigit(m2)) {
            throw std::runtime_error("Введите число");
        }
        marks.push_back(static_cast<int>(m2 - '0'));
        std::cout << std::endl;
    }
    catch(const std::runtime_error& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    
}

void changeGroups(int flag, std::list<Group>& groups, std::list<Student>& student, std::string& group) {
    if (flag) {
        for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
            if ((*iter).getGroup() == group) {
                groups.erase(iter);
                Group newGr(group, student);
                groups.push_back(newGr);
                break;
            }
        }
    }
    if (!flag) std::cout << "Неправильные данные" << std::endl;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int checkF(std::ifstream& in) {
    std::string n;
    try {
        in >> n;
        if (!is_number(n)) {
            throw std::runtime_error("Введите число");
        }
        if (atoi(n.c_str()) > 13 || atoi(n.c_str()) < 1) {
            throw std::out_of_range("Введите цифру от 2 до 5");
        }
    }
    catch(const std::runtime_error& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    return atoi(n.c_str());
}

int menu() {
    std::cout << "1. Добавить студента" << std::endl;
    std::cout << "2. Редактировать оценки студента" << std::endl;
    std::cout << "3. Удалить студента из группы" << std::endl;
    std::cout << "4. Просмотр групп" << std::endl;
    std::cout << "5. Средний балл по одной дисциплины для группы" << std::endl;
    std::cout << "6. Средний балл по всем дисциплинам для группы" << std::endl;
    std::cout << "7. Отличники" << std::endl;
    std::cout << "8. Должники" << std::endl;
    std::cout << "9. Сортировка по ФИО в группе" << std::endl;
    std::cout << "10. Запись значений в файл" << std::endl;
    std::cout << "11. Чтение значений из файла" << std::endl;
    std::cout << "12. Выход из программы" << std::endl;
    std::cout << "Введите цифру:" << std::endl;
    std::string n;
    try {
        std::cin >> n;
        if (!is_number(n)) {
            throw std::runtime_error("Введите число");
        }
        if (atoi(n.c_str()) > 13 || atoi(n.c_str()) < 1) {
            throw std::out_of_range("Введите цифру от 1 до 10");
        }
    }
    catch(const std::runtime_error& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    return atoi(n.c_str());
}

int menu1(std::string& group) {
    std::cout << "Введите группу" << std::endl;
    std::cin.ignore();
    std::cout << "Группа: "; std::getline(std::cin, group);
    std::cout << "Введите номер дисциплины: " << std::endl;
    std::cout << "1. Математика" << std::endl;
    std::cout << "2. АЯ" << std::endl;
    std::cout << "3. Физика" << std::endl;
    std::cout << "Предмет: ";
    std::string n;
    try {
        std::cin >> n;
        if (!is_number(n)) {
            throw std::runtime_error("Введите число");
        }
        if (atoi(n.c_str()) > 13 || atoi(n.c_str()) < 1) {
            throw std::out_of_range("Введите цифру от 1 до 10");
        }
    }
    catch(const std::runtime_error& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    return atoi(n.c_str());
}
#endif

