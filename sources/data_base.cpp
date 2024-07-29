#include "header.h"
#include "header1.h"

std::mutex mut;

int main() {
    std::list<Group> groups;
    while(true) {
        int n = menu();
        if (n == 1) {
            std::string name = "";
            std::string group = "";
            std::list<int> marks;
            enterMarks(name, group, marks);
            Student st(name, group, marks);
            int flag = 0;
            for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
                if ((*iter).getGroup() == group) {
                    (*iter) + st;
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                std::list<Student> stud;
                stud.push_back(st);
                Group gr(group, stud);
                groups.push_back(gr);
                
            }
        }
        
        if (n == 2) {
            std::string name;
            std::string group;
            std::list<Student> student;
            std::list<int> marks;
            enterMarks(name, group, marks);
            Student st(name, group, marks);
            int flag = 0;
            for (auto el: groups) {
                if (el.getGroup() == group) {
                    for (auto el1: el.getStudents()) {
                        if (el1.getName() == name) {
                            el1.changeMarks(marks);
                            el.changeGroup(el1);
                            student = el.getStudents();
                            flag = 1;
                            std::cout << "Данные изменены" << std::endl;
                            break;
                        }
                    }
                }
            }
            changeGroups(flag, groups, student, group);
        }
        if (n == 3) {
            std::lock_guard <std::mutex> lock(mut);
            std::string name;
            std::string group;
            std::list<Student> student;
            std::cout << "Введите группу и ФИО студента" << std::endl;
            std::cin.ignore();
            std::cout << "ФИО: "; std::getline(std::cin, name);
            std::cout << "Группа: "; std::getline(std::cin, group);
            int flag = 0;
            for (auto el: groups) {
                if (el.getGroup() == group) {
                    flag = 1;
                    for (auto el1: el.getStudents()) {
                        if (el1.getName() != name) {
                            student.push_back(el1);
                        }
                    }
                }
            }
            changeGroups(flag, groups, student, group);
        }
        if (n == 4) {
            for (auto el: groups) {
                std::cout << el;
            }
        }
        if (n == 5) {
            std::string group;
            int m = menu1(group);
            int flag = 0;
            for (auto el: groups) {
                if (el.getGroup() == group) {
                    std::cout << "Средняя оценка: " << el.middleMarks(m) << std::endl;
                    flag = 1;
                }
            }
            if (!flag) std::cout << "Неправильные данные" << std::endl;
        }
        if (n == 6) {
            std::string group;
            std::cout << "Введите группу" << std::endl;
            std::cin.ignore();
            std::cout << "Группа: "; std::getline(std::cin, group);
            int flag = 0;
            int sum = 0;
            int size = 0;
            for (auto el: groups) {
                if (el.getGroup() == group) {
                    flag = 1;
                    size = el.getStudents().size();
                    for (auto el1: el.getStudents()) {
                        sum += el1.sumMarks(1) + el1.sumMarks(2) + el1.sumMarks(3);
                    }
                }
            }
            std::cout << "Средняя оценка: " << sum /  (size * 3.0) << std::endl;
            if (!flag) std::cout << "Неправильные данные" << std::endl;
        }
        if (n == 7) {
            int flag = 0;
            std::cout << "Отличники: " << std::endl;
            for (auto el: groups) {
                for (auto el1: el.check(5)) {
                    std::cout << el;
                }
            }
            if (!flag) std::cout << "Отличников нет" << std::endl;
        }
        if (n == 8) {
            int flag = 0;
            std::cout << "Должники: " << std::endl;
            for (auto el: groups) {
                for (auto el1: el.check(2)) {
                    std::cout << el;
                    flag = 1;
                }
            }
            if (!flag) std::cout << "Должников нет" << std::endl;
        }
        if (n == 9) {
            std::string group;
            std::list<Student> student;
            std::cout << "Введите группу" << std::endl;
            std::cin.ignore();
            std::cout << "Группа: "; std::getline(std::cin, group);
            int flag = 0;
            for (auto el: groups) {
                if (el.getGroup() == group) {
                    flag = 1;
                    student = el.getStudents();
                }
            }
            student.sort([=](auto st1, auto st2) {return st1.getName() < st2.getName();});
            changeGroups(flag, groups, student, group);
        }
        
        if (n == 10) {
            std::lock_guard <std::mutex> lock(mut);
            std::ofstream foutt("output.txt");
            for (auto el: groups) {
                foutt << el;
            }
        }
        
        if (n == 11) {
            std::lock_guard <std::mutex> lock(mut);
            int n;
            std::ifstream fint("input.txt");
            if (!fint) {
                std::cout << "Error" << std::endl;
            }
            fint >> n;
            for (int i = 0; i < n; ++i) {
                std::string name = "";
                fint.ignore();
                std::getline(fint, name);
                std::string group = "";
                fint.ignore();
                std::getline(fint, group);
                std::list<int> marks;
                for (int i = 0; i < 3; ++i) {
                    marks.push_back(checkF(fint));
                }
                Student st(name, group, marks);
                int flag = 0;
                for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
                    if ((*iter).getGroup() == group) {
                        (*iter) + st;
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    std::list<Student> stud;
                    stud.push_back(st);
                    Group gr(group, stud);
                    groups.push_back(gr);
                }
            }
        }
        
        if (n == 12) break;
    }
}

