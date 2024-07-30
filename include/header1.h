#include "header.h"

#ifndef HEADER1_H
#define HEADER1_H

Student::Student(): _name(""), _group(""), _marks({}){};
Student::Student(std::string name, std::string group, std::list<int> marks) {
    try {
        _name = name;
        _group = group;
        for (auto el: marks) {
            if (el > 5 || el < 2) {
                throw std::out_of_range("Введите оценку от 2 до 5");
                
            }
            _marks.push_back(el);
        }
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
        std::cout << std::endl;
    }
}

bool Student::checkDebt() {
    for (auto el: _marks) {
        if (el == 2) return true;
    }
    return false;
}

bool Student::checkFive() {
    for (auto el: _marks) {
        if (el != 5) {
            return false;
        }
    }
    return true;
}

int Student::sumMarks(int m) {
    int count = 1;
    int sum = 0;
    for (auto el: _marks) {
        if (count == m) {
            sum = el;
            break;
        }
        count ++;
    }
    return sum;
}

void Student::changeMarks(std::list<int>& marks) {
    this->_marks.clear();
    for (auto el: marks) {
        _marks.push_back(el);
    }
}

std::string Student::getGroup() {
    return _group;
}

std::string Student::getName() {
    return _name;
}

std::ostream& operator<<(std::ostream& out, Student& st) {
    out << "ФИО: " << st._name << std::endl;
    out << "Группа: " << st._group << std::endl;
    std::vector<std::string> sub = {"Математика:", "АЯ:", "Физика:"};
    int count = 0;
    for (auto el: st._marks) {
        out << sub[count] << " " << el << std::endl;
        count ++;
    }
    return out;
}

Group::Group(): _nameGroup(nullptr), _group({}) {};

Group::Group(std::string nameGroup, std::list<Student> group): _nameGroup(nameGroup) {
    std::copy(group.begin(), group.end(), std::back_inserter(_group));
}

std::list<Student> Group::operator+(const Student& st) {
    this->_group.push_back(st);
    return this->_group;
}

std::string Group::getGroup() {
    return this->_nameGroup;
}

std::list<Student> Group::getStudents() {
    return this->_group;
}

void Group::changeGroup(Student& st) {
    auto iter = std::find_if(_group.begin(), _group.end(), [&st](Student stud) {return st.getName() == stud.getName();});
    if (iter != _group.end()) {
        _group.erase(iter);
        _group.push_back(st);
    }
}

float Group::middleMarks(int number) {
    int count = 0;
    for (auto el: _group) {
        count += el.sumMarks(number);
    }
    return count / (1.0 * _group.size());
}

std::list<Student> Group::check(int m) {
    std::list<Student> st;
    for (auto el: _group) {
        if (m == 5) {
            if (el.checkFive()) {
                st.push_back(el);
            }
        }
        else {
            if (el.checkDebt()) {
                st.push_back(el);
            }
        }
        
    }
    return st;
}

std::ostream& operator<<(std::ostream& out, Group& gr) {
    if (gr._group.size() == 0) out << "В этой группе студентов нет" << std::endl;
    for (auto el: gr._group) {
        out << el;
        out << std::endl;
    }
    return out;
}
#endif
