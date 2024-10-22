#include "functions.h"

int main() {
    std::vector<int> arr;
    RANDOM_FILL(arr, 10);
    PRINT_VECTOR(arr);

    int minPos = 0;
    FIND_MIN_ABS_POSITION(arr, minPos);
    std::cout << "Position of minimal element by absolute value: " << minPos << "\n";

    int sum = 0;
    SUM_ABS_BEYOND_FIRST_NEGATIVE(arr, sum);
    std::cout << "Sum by abs() of elements which are located beyond first negative one: " << sum << "\n";


    COMPRESS_ARRAY(arr, 10, 40);
    PRINT_VECTOR(arr);
}
