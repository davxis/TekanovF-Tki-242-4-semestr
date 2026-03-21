#include <iostream>
#include <list>
#include <iterator>

// Функция для обмена первой половины L1 и второй половины L2
void swapHalves(std::list<int>& L1, std::list<int>& L2) {
    auto mid1 = L1.size() / 2;
    auto mid2 = L2.size() / 2;
    
    // Итераторы к серединам списков
    auto it1 = std::next(L1.begin(), mid1);
    auto it2 = std::next(L2.begin(), mid2);
    
    // Временный список для хранения второй половины L2
    std::list<int> temp;
    
    // Перемещаем вторую половину L2 во временный список
    temp.splice(temp.begin(), L2, it2, L2.end());
    
    // Перемещаем первую половину L1 в конец L2
    L2.splice(L2.end(), L1, L1.begin(), it1);
    
    // Перемещаем сохранённую вторую половину L2 в начало L1
    L1.splice(L1.begin(), temp);
}

// Функция для вывода списка
void printList(const std::string& name, const std::list<int>& lst) {
    std::cout << name << ": ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Инициализация списков с чётным количеством элементов
    std::list<int> L1 = {1, 2, 3, 4, 5, 6};
    std::list<int> L2 = {10, 20, 30, 40, 50, 60};
    
    std::cout << "Исходные списки:" << std::endl;
    printList("L1", L1);
    printList("L2", L2);
    
    // Обмен половинами
    swapHalves(L1, L2);
    
    std::cout << "\nПосле обмена:" << std::endl;
    printList("L1", L1);
    printList("L2", L2);
    
    return 0;
}
