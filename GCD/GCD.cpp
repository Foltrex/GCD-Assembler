
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <chrono>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now()) { }

    void reset() {
        m_beg = clock_t::now();
    }

    double elapsed() const {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};


uint32_t findGCD_A(uint32_t x, uint32_t y) {
    _asm {
        mov eax, x
        mov edx, 0
        cikl:
        cmp y, 0
            je the_end
            idiv y
            mov eax, y
            mov y, edx
            mov edx, 0
        jmp cikl
        
       the_end:
            mov y, eax
    }
    return y;
}


// tail recursion, which is executed as a loop
uint32_t findGCDWithTailRecursion(uint32_t x, uint32_t y) {
    return y ? findGCDWithTailRecursion(y, x % y) : x;
}

uint32_t findGCDWithLoop(uint32_t x, uint32_t y) {
    while (y) {
        std::swap(x %= y, y);
    }

    return x;
}

int main()
{
    uint32_t x{}, y{};

    std::cout << "Enter first and second number:\n";
    while( !(std::cin >> x >> y) ) {
        std::cout << "Enter two positive numbers again:\n";
    }

    Timer time;

    uint32_t amountAssembler = findGCD_A(x, y);
    auto timeWithAssembler= time.elapsed();
    time.reset();

    uint32_t amountWithTailRecursion = findGCDWithTailRecursion(x, y);
    auto timeWithTailRecursion = time.elapsed();
    time.reset();

    uint32_t amountWithLoop = findGCDWithLoop(x, y);
    auto timeWithLoop = time.elapsed();


    std::cout.precision(9);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);

    std::cout << '\n';
    std::cout << "Answer(assembler):\t\t"           << amountAssembler          << '\n';
    std::cout << "Anser(tail recursion, C++):\t"    << amountWithTailRecursion  << '\n';
    std::cout << "Anser(loop, C++):\t\t"            << amountWithLoop           << "\n\n";

    std::cout << "Time(assembler):\t\t"             << timeWithAssembler        << '\n';
    std::cout << "Time(tail recursion, C++):\t"     << timeWithTailRecursion    << '\n';
    std::cout << "Time(loop, C++):\t\t"             << timeWithLoop             << '\n';

    return 0;
}