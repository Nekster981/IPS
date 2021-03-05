//Сухарев Н., 24 вариант, метод Симпсона

#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <thread>
using namespace std::chrono;
using namespace std;

//Считаем заданную функцию
double funct (double x) {
    return 8 / (1 + x * x);
}

//Считаем интеграл методом Симпсона
void simpson_vector(int n) {
    double f = 0;
    double a = 0;
    double b = 1;
    double h = (b - a) / n;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (double i = a + h; i <= b; i += h)
    {
        f += (i - a) / 6 * (funct(a) + 4 * funct((i + a) / 2) + funct(i));
        a += h;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "n = " << n << endl;
    cout << "f = " << f << endl;
    duration<double> duration = (t2 - t1);
    cout << "Duration is: " << duration.count() << " seconds" << endl;
}

void simpson_no_vector(int n) {
    double f = 0;
    double a = 0;
    double b = 1;
    double h = (b - a) / n;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    #pragma loop(no_vector)
    for (double i = a + h; i <= b; i += h)
    {
        f += (i - a) / 6 * (funct(a) + 4 * funct((i + a) / 2) + funct(i));
        a += h;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "n = " << n << endl;
    cout << "f = " << f << endl;
    duration<double> duration = (t2 - t1);
    cout << "Duration is: " << duration.count() << " seconds" << endl;
}

void simpson_parallel(int n) {
    double f = 0;
    double a = 0;
    double b = 1;
    double h = (b - a) / n;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    #pragma loop(hint_parallel(8))
    for (double i = a + h; i <= b; i += h)
    {
        f += (i - a) / 6 * (funct(a) + 4 * funct((i + a) / 2) + funct(i));
        a += h;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "n = " << n << endl;
    cout << "f = " << f << endl;
    duration<double> duration = (t2 - t1);
    cout << "Duration is: " << duration.count() << " seconds" << endl;
}





int main()
{
    int n = 100;
    //Выполняем задание 1 с векторизацией
    cout << "1) Vectorization" << endl; 
    cout << "\n";
    for (int j = 1; j <= 5; j++)
    {
        simpson_vector(n);
        cout << "\n";
        n = n * 10;
    }
    
    n = 100;
    //Выполняем задание 1 без векторизации
    cout << "2) No vectorization" << endl;
    cout << "\n";
    for (int j = 1; j <= 5; j++)
    {
        simpson_no_vector(n);
        cout << "\n";
        n = n * 10;
    }

    
    n = 100;
    //Выполняем задание 1 с параллелизацией
    cout << "3) Parallel" << endl;
    cout << "\n";
    for (int j = 1; j <= 5; j++)
    {
        simpson_parallel(n);
        cout << "\n";
        n = n * 10;
    }

    //Выполняем задание 1 с многопоточностью
    cout << "4) Threads" << endl;
    cout << "\n";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    std::thread a(simpson_vector,100);
    std::thread b(simpson_vector, 1000);
    std::thread c(simpson_vector, 10000);
    std::thread d(simpson_vector, 100000);
    std::thread e(simpson_vector, 1000000);
    a.join();
    b.join();
    c.join();
    d.join();
    e.join();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> duration = (t2 - t1);
    cout << "Total duration for last task is: " << duration.count() << " seconds" << endl;
    return 0;
}