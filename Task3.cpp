#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>   
#include <algorithm> 

int main() {
    // Исходный вектор V 
    // Слова набраны заглавными буквами
    std::vector<std::string> V = {
        "HELLO", "CPP", "CODE", "JAVA", "RUST", "GO"
    };

    // Вспомогательное отображение M
    // Ключ: последняя буква 
    // Значение: вектор слов, оканчивающихся на эту букву
    std::map<char, std::vector<std::string>> M;

    // Используем std::for_each вместо цикла for
    std::for_each(V.begin(), V.end(), [&M](const std::string& word) {
        if (!word.empty()) {
            char lastChar = word.back();
            M[lastChar].push_back(word);
        }
    });

    // std::map автоматически отсортирован по буквам
    std::for_each(M.begin(), M.end(), [](const auto& entry) {
        char letter = entry.first;
        const std::vector<std::string>& group = entry.second;

        std::string resultString;

        // Сумма всех слов, кроме последнего
        if (group.size() > 1) {
            // Используем std::accumulate
            // Диапазон: от begin() до (end() - 1), чтобы исключить последнее слово
            resultString = std::accumulate(
                group.begin(), 
                group.end() - 1, 
                std::string(""), // Начальное значение 
                [](std::string acc, const std::string& word) {
                    // Функция сложения: добавляем слово и пробел
                    return acc + word + " ";
                }
            );
        } 
        // Если группа состоит из одного элемента, resultString остается пустой ("")

        // Вывод пары: буква и найденная строка
        std::cout << letter << ": \"" << resultString << "\"" << std::endl;
    });

    return 0;
}
