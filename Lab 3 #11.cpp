#include <iostream>

#define ALPHABET_SIZE 26
#define MAX_INPUT_SIZE 4096

// Отримуємо ввід від користувача
char* getInput(int size) {
    char* input = new char[size + 1];
    std::cin.getline(input, size + 1);
    return input;
}

char* purify(const char* letters, char* input) {
    // Статична строка із символів-роздільників
    static const char* delimiters = " .,?!;:";

    // Отримуємо довжину введеної строки
    const int inputSize = strlen(input);

    // Виділяємо нову строку, куди будемо копіювати деякі слова із введеної
    char* purified = new char[inputSize + 1];

    // Стежимо за позицією останнього елемента в строці purified
    int position = 0;

    for (int i = 0; i < inputSize; ++i) {
        /*
        * Запускаємо цикл виходу із забороненого слова: поки строка не закінчилась і символ
        * не є роздільником - збільшуємо ітератор; якщо дійшли до кінця, виходимо із зовнішнього циклу
        * 
        * В умові if перевіряється:
        * 1. Даний символ є забороненим
        * 2. Слово ПОЧИНАЄТЬСЯ з даного символу (тоді, коли i = 0 -> слово перше АБО попередній символ є роздільником)
        */
        if (strchr(letters, tolower(input[i])) && (i == 0 || strchr(delimiters, input[i - 1]))) {
            while (i < inputSize && !strchr(delimiters, input[i])) {
                i++;
            }
            if (i == inputSize) { 
                break; 
            }
        }

        // Записуємо дозволений символ в строку і збільшуємо позицію
        purified[position] = input[i];
        position++;
    }

    // Термінуємо строку і повертаємо її
    purified[position] = '\0';
    return purified;
}

int main() {
    /*
    * Наприклад:
    * 
    * tsap [заборонені символи - початки слів]
    * Hello, world! A; test: string, to, check, the! Correctness. Of: this; program? [строка]
    * Hello, world! ; : , , check, ! Correctness. Of: ; ? [очищена строка]
    */
    const char* letters = getInput(ALPHABET_SIZE);
    char* input = getInput(MAX_INPUT_SIZE);
    char* purified = purify(letters, input);

    std::cout << purified;

    delete[] letters;
    delete[] input;
    delete[] purified;
}
