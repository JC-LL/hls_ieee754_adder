#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

#include "conversions.h"
#include "add.h"

#define max_float 0xffffffff

/*A signalling NaN (NANS) is represented by any bit pattern
between 7F800001 and 7FBFFFFF or between FF800001 and FFBFFFFF

A quiet NaN (NANQ) is represented by any bit pattern
between 7FC00000 and 7FFFFFFF or between FFC00000 and FFFFFFFF*/

int isNaN(uint32_t x){
  return
        ((0x7F800001 <= x) &&  (x<= 0x7FBFFFFF)) || ((0xFF800001 <=x) &&  (x<= 0xFFBFFFFF)) ||
        ((0x7FC00000 <= x) &&  (x<= 0x7FFFFFFF)) || ((0xFFC00000 <=x) &&  (x<= 0xFFFFFFFF));
}

int test_from_file(std::string filename){
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file." << std::endl;
    }

    int nb_tests   = 0;
    int num_passed = 0;
    int num_failed = 0;
    int total_failed = 0;
    uint32_t i;
    uint32_t a, b, c;

    std::string line;
    while (getline(file, line)) {
        std::istringstream    iss(line);
        //std::cout << line << std::endl;
        nb_tests++;
        iss >> std::dec >> i;
        iss >> std::hex >> a;
        iss >> std::hex >> b;
        iss >> std::hex >> c;
        iss.clear();
        if (fp32_add(a, b)==c) {
            num_passed++;
        }
        else {
            num_failed++;
        }
    }
    std::cout << "=============================================" << std::endl;
    std::cout << "Testing patterns from file " << filename << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "- From  " << nb_tests << " tests, "<< num_passed << " " << "PASSED " << num_failed << " FAILED." << std::endl;
    file.close();
    return num_failed;
}

int test_random(int nb_tests){
  std::cout << "=============================================" << std::endl;
  std::cout << "Testing random patterns " << std::endl;
  std::cout << "=============================================" << std::endl;

  int num_passed = 0;
  int num_failed = 0;
  for (int test_id = 0; test_id < nb_tests; test_id++) {
      // generate a pseudo-random pattern
      uint32_t number1 = rand() % max_float;
      uint32_t number2 = rand() % max_float;

      // perform the reference floating point addition
      float sum = *(float*) &number1 + *(float*) &number2;

      // cast to 32 bits binary representation
      uint32_t expected= *(uint32_t*)&sum;

      // compare resulting binary patterns
      uint32_t actual= fp32_add(number1, number2);

      if (expected == actual) {
            num_passed++;
      }
      else if (isNaN(expected) && isNaN(actual)){
            num_passed++;
      }
      else {
          std::cout << "ERROR for " << uint32_as_float(number1) << "[uint " << number1 << "] + " << uint32_as_float(number2) << "[uint " << number2 << "]" << std::endl;
          std::cout << "Expected: " << expected << " pattern but received " << actual << std::endl;
          num_failed++;
      }
  }
  std::cout << "- From  " << nb_tests << " tests, "<< num_passed << " " << "PASSED " << num_failed << " FAILED." << std::endl;
  return num_failed;
}

int main() {
    const int NB_TESTS = 1000000;
    int total_failed = 0;
    total_failed += test_from_file("add.dat");
    total_failed += test_random(NB_TESTS);
    return total_failed;
}
