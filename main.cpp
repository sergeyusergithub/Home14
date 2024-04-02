// main.cpp

#include "employee.hpp"

#include <random>
#include <vector>
#include <algorithm>

#include <string>
#include <sstream>
#include <iostream>
#include <set>






int main(){

    // для заполнения некоторых полей класса рабочий, создадим генерацию случайных чисел
    std::random_device rd;
    std::mt19937 distr(rd());
    std::uniform_int_distribution<int> prov_shift(0,1); // для генерации смены Ночь = 0, день = 1
    std::uniform_real_distribution<double> prov_real(50000,150000); // для генерации случайной зарплаты

    // создадим коллекцию, которая будет содержать рабочих
    std::vector<Employee> fabric;

    // размер коллекции рабочих
    const int size = 25;  

    // резервируем место для нашей коллекции
    fabric.reserve(size);

    // заполняем коллекцию рабочими
    for(int i = 0; i < size; i++){
        fabric.emplace_back(100 + i,"Worker "+ std::to_string(i + 1),prov_shift(distr),prov_real(distr));
    }

    // выводим содержимое полученной коллекции
    for(auto& i:fabric){
        std::cout << i; 
    }

    // определяем дневных рабочих
    std::cout << "\n=================== Day Worker ======================\n";

    // определим итератор на начало коллекции
    auto it = fabric.begin();

    // цикл для определения дневных рабочих
    while(it != fabric.end()){
        // используем алгоритм поиска с условием для определения дневных рабочих
        it = std::find_if(it,fabric.end(),[](Employee &input)->bool{ 
                                  return input.Shift();});
        // выводим полученное содержимое
        if (it != fabric.end()){
            it->print();
            it++;
        }
    }

    // определяем ночных рабочих
    std::cout << "\n================== Nigth Worker =====================\n";
    it = fabric.begin();

    while(it != fabric.end()){
        // алгоритм поиска ночных рабочих
        it = std::find_if_not(it,fabric.end(),[](Employee &input)->bool{ 
                                  return input.Shift();});
        // выводим ночных рабочих
        if (it != fabric.end()){
            it->print();
            it++;
        }
    }
       
    // для того, чтобы определить максимальную и минимальную оплату дневных и ночных рабочих
    // сорируем массив по зарплате
    std::sort(fabric.begin(),fabric.end(),[](Employee& a, Employee& b)->bool{
                                        return a.Fee() > b.Fee();});


    // определяем файл в который будет записываться и считываться информация о рабочих
    const char* file = "../notice.txt";

    std::fstream in_out;
    
    // открываем файл для записи, если файла не существует, то он будет создан,
    // данные из файла будут удалены
    in_out.open(file,std::ios::out);

    // проверяем получилось ли открыть файл
    if (in_out.is_open()){
        // выводим разделительные строки в консоль и в файл
        std::cout << "\n================ Max Fee Day Worker =================\n";
        in_out << "================ Max Fee Day Worker ==================\n";

        it = fabric.begin();

        // счетчик количества необходимого количества рабочих, которых необходимо вывести
        int count{};

        // так как коллекция является отсортированная, то выводим последовательно из
        // коллекции дневных рабочих, это и будет три дневных рабочих с максимальной зарплатой
        while(it != fabric.end() && count < 3){
            it = std::find_if(it,fabric.end(),[](Employee &input)->bool{ 
                                    return input.Shift();});
            
            // выводим содержимео в консоль и  в файл
            if (it != fabric.end()){
                std::cout << *it;
                in_out << *it;
                it++;
            }
            count++;
        }

        // закрываем файл
        in_out.close();

        //=======================================
        // открываем файл для дозаписи
        in_out.open(file,std::ios::app);

        // проверяем, удалось ли открыть файл
        if(in_out.is_open()) {
            // строковые разделители для консоли и файла
            std::cout << "\n=============== Max Fee Nigth Worker ================\n";
            in_out << "=============== Max Fee Nigth Worker =================\n";
    
            it = fabric.begin();
            count = 0;

            // цикл который выводит трех ночных рабочих с максимальной зарплатой
            while(it != fabric.end() && count < 3){
                it = std::find_if_not(it,fabric.end(),[](Employee &input)->bool{ 
                                        return input.Shift();});
                
                // выводим содержимое в консоль и в файл
                if (it != fabric.end()){
                    it->print();
                    in_out << *it;
                    it++;
                }
                count++;
            }

            // строковые разделители для трех рабочих с максимальной зарплатой
            std::cout << "\n================= Max Fee ===========================\n";
            in_out << "====================== Max Fee =======================\n";
            
            // в цикле выводятся последние элементы коллекция, там находятся рабочие с макцимальной зарплатой
            for(int i = size - 1; i > size - 4; --i){
                std::cout << fabric.at(i);
                in_out << fabric.at(i);
            }

            // снова сортируем коллекцию, только по убыванию, хотя можно было использовать
            // коллекцию с предыдущей сортировкой
            std::sort(fabric.begin(),fabric.end(),[](Employee& a, Employee& b)->bool{
                                                return a.Fee() < b.Fee();});


            // определение и вывод рабочих с минимальной зарплатой делается аналогично 
            // выводу с максимальной зарплатой
            std::cout << "\n=============== Min Fee Day Worker ==================\n";
            in_out << "================ Min Fee Day Worker ==================\n";

            it = fabric.begin();

            count = 0;

            while(it != fabric.end() && count < 3){
                it = std::find_if(it,fabric.end(),[](Employee &input)->bool{ 
                                        return input.Shift();});
                
                if (it != fabric.end()){
                    it->print();
                    in_out << *it;
                    it++;
                }
                count++;
            }

            std::cout << "\n=============== Min Fee Nigth Worker ================\n";
            in_out << "================ Min Fee Nigth Worker ================\n";
            it = fabric.begin();
            count = 0;
            while(it != fabric.end() && count < 3){
                it = std::find_if_not(it,fabric.end(),[](Employee &input)->bool{ 
                                        return input.Shift();});
                
                if (it != fabric.end()){
                    it->print();
                    in_out << *it;
                    it++;
                }
                count++;
            }
            std::cout << "\n================= Min Fee ===========================\n";
            in_out << "================== Min Fee ===========================\n";
        
            
            for(int i = 0; i < 3; ++i){
                fabric.at(i).print();
                in_out << fabric.at(i);
            }
            in_out.close();
        } else {
            std::cout << "File is not open!\n";
        }
    } else {
        std::cout << "File is not open!\n";
    }

    // теперь, для чтения файла, открываем его, в режиме чтения
    in_out.open(file,std::ios::in);

    // вспомогательная переменная, куда будут построчно считываться данные из файла
    std::string str;

    // определим вспомогательную коллекцию, которая будет содержать уникальные элементы коллекции
    std::set<Employee> set_array;

    // определим коллекцию, куда будут помещаться оставшиеся в файле раточие
    std::vector<Employee> new_vect;

    // переменная для хранения уникального номера рабочего
    int id;
    // переменная для хранения имени рабочего, номера из имени рабочего, смену рабочего
    std::string worker, num, shift;

    // переменная для хранения зарплаты рабочего
    double fee;

    // переменная хранящая записи о количестве элементов уникальной коллекции
    int length{};

    // проверяем получилось ли открыть файл    
    if(in_out.is_open()){
        
        // цикл считывания строк из файла и запись полученных строк в новые коллекции
        while(std::getline(in_out,str)){
            // если строка не содержит в начале символ =, то такую строку можно добавлять в коллекцию
            if(str[0] != '='){
                // определим переменную, которая будет нашу строку из файла
                // в ставлять в поток ввода, из которого мы и получим необходимые данные о рабочих
                std::istringstream ss(str);
                // из потока ввода запишим данные строки в соответствующие переменные
                ss >> id >> worker >> num >> shift >> fee;
               
                // поместим строку в коллекцию с уникальными рабочими, при этом сделав преобразование
                // строковых значений смены День/Ночь в bool
                set_array.emplace(id,worker+" "+num,((shift == "Day")? true:false),fee);
                // проверяем, если размер коллекции увеличился, то запись произошла, полученная
                // строка была уникальной, иначе, полученная строка не уникальная и ее
                // запишем в другую коллекцию
                if (set_array.size() == length + 1){
                    length += 1;
                } else {
                    new_vect.emplace_back(id,worker+" "+num,((shift == "Day")? true:false),fee);
                }
            }
        }


    // по завершению заполнения коллекций закроем файл
    in_out.close();

    // выводим содержимое коллекции с уникальными рабочими из файла
    std::cout << "\n\n=============== Uniq string from file ===========\n";
    for(auto &i:set_array){
        std::cout << i;
    }

    // выводим содержимое коллекции с остальными рабочими из файла
    std::cout << "\n================= Other string from file ============\n";
    for(auto &i:new_vect){
        std::cout << i;
    }

    } else {
        std::cout << "File is not open\n";
    }
    
    return 0;
}