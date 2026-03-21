#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

int main() {
    std::string name1 = "name1.txt";   
    std::string name2 = "name2.txt";   

    std::ifstream infile(name1);     
    std::ofstream outfile(name2);      

    // Используем remove_copy с итераторами
    std::remove_copy(
        std::istream_iterator<int>(infile),           // начало потока чисел из файла
        std::istream_iterator<int>(),                 // конец потока 
        std::ostream_iterator<int>(outfile, "\n"),    // запись в файл с переводом строки
        0                                             // значение, которое нужно исключить
    );

    return 0;
}
