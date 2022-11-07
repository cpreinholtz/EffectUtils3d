#include <cstdint>
typedef uint8_t byte;
#include <iostream>
using namespace std;


#include <mock_arduino.h>




int run_tests() {
    int error_code =0;
    initialize_mock_arduino();

    //do tests here


    cout << "press enter to continue\n";
    while (cin.get() != '\n');
    return error_code;
}



int main(int argc, char **argv){
    cout << "Beggining test sequence\n";
    return run_tests();
}