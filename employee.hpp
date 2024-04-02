// employee.hpp

// в данном файле создается класс
// работника, вместо структуры работника

#pragma once


#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_
#include <iostream>
#include <fstream>

// класс работник
class Employee{
public:
    // конструктор по умолчанию
    Employee():id_{},name_{},shift_{},fee_{}{}

    // конструктор с параметрами
    Employee(int id, std::string name, bool shift, double fee):
    id_(id),name_(name),shift_(shift),fee_(fee){}

    // конструктор копирования
    Employee(const Employee& other):id_(other.id_),name_(other.name_),
                shift_(other.shift_),fee_(other.fee_){ }

    // оператор присваивание копированием
    Employee& operator=(const Employee& other){
            id_ = other.id_;
            name_ = other.name_;
            shift_ = other.shift_;
            fee_ = other.fee_;
        return *this;
    }

    // оператор потокового вывода в файл
    friend std::ofstream& operator<<(std::ofstream &outfile, const Employee &obj) {
        outfile << obj.id_ << "\t" << obj.name_ << "\t" << \
        ((obj.shift_)? "Day  ":"Night") << "\t" << \
        obj.fee_ << '\n';
        return outfile;
    }

    // оператор потокового вывода в консоль
    friend std::ostream& operator<<(std::ostream& coutput, const Employee& obj){
        coutput << obj.id_ << "\t" << obj.name_ << "\t" << ((obj.shift_)?"Day  ":"Nigth") \
         << '\t' << obj.fee_ << '\n';
        return coutput;
    }

    // оператор потокового ввода из файла
    friend std::ifstream& operator>>(std::ifstream& infile,Employee& obj){
        infile >> obj.id_;
        return infile;
    }

    // оператор < для работы контейнера set, сравнивать
    // будем только по id рабочего
    bool operator<(const Employee& other)const{
        return (id_ < other.id_);
    }  

    // метод вывода информации на экран
    void print(){
        std::cout << id_ << "\t" << name_ << "\t" << ((shift_)?"Day  \t":"Nigth\t");
        std::cout << fee_ << '\n';
    }

    // геттеры и сеттеры
    int Id(){
        return id_;
    }
    void Id(int id){
        id_ = id;
    }
    //==========================
    std::string Name()const{
        return name_;
    }

    void Name(std::string name){
        name_ = name;
    }

    //==========================
    bool Shift()const{
        return shift_;
    }

    void Shift(bool shift){
        shift_ = shift;
    }

    //===========================
    double Fee() const {
        return fee_;
    }

    void Fee(double fee){
        fee_ = fee;
    }


private:
    int id_;   // индивидуальный номер работника
    std::string name_; // имя работника
    bool shift_; // true - дневная смена работника
                 // false - ночная смена работника
    double fee_; // зарплата работника

};




#endif  // _EMPLOYEE_HPP_