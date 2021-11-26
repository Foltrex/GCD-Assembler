
#include "pch.h"
#include <iostream>
#include <iomanip>

#include <chrono> // для функций из std::chrono

class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};


int findGCD_A(int x, int y) {
    int nod;
    _asm {
        mov eax, x;
        mov edx, y;
    cikl:
        cmp eax, edx; сравнение регистра eax с edx
            je the_end; если eax = edx, то "прыгаем" в the_end
            jl metka; если eax < edx, то "прыгаем" в metka
            sub eax, edx;
        jmp cikl;
    metka:
        sub edx, eax;
        jmp cikl;
    the_end:
        mov nod, eax;
    }
    return nod;
}

int findaGCD_C(int x, int y) {
    while (x != y) {
        if (x >= y) {
            x -= y;
        }
        else {
            y -= x;
        }
    }
    return x;
}

int main()
{
    using namespace std;

    int x{}, y{};

    cout << "Enter first and second number:\n";
    cin >> x >> y;

    Timer t;
    int amount_a = findGCD_A(x, y);
    auto time_a = t.elapsed();
    t.reset();

    int amount_c = findaGCD_C(x, y);
    auto time_c = t.elapsed();

    std::cout << fixed << setprecision(9) << "\nAnswer(assembler):  " << amount_a << '\n' <<
        "Anser(C++):  " << amount_c << "\n\n" <<
        "Time(assembler):  " << time_a << '\n' <<
        "Time(C++):  " << time_c;
    return 0;
}