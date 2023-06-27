#include <iostream>
#include <iomanip>
#include "scene/scene.hpp"

//use cpdf reciprocal
double GetValueWithMyPDF(double x) {
    return 2 * x;
}

double MyPDF(double x) {
    return 0.5;
}

double SquareFunction(double x) {
    return x * x;
}

void TestPDF() {
    constexpr int SqrtN = 100;
    double Sum = 0.0;
    for (int i = 0; i < SqrtN; i++) {
        auto x = GetValueWithMyPDF(mortal::KRandom());
        Sum += SquareFunction(x) / MyPDF(x);
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << Sum / SqrtN << "\n";


    //2.666789837968 3.035327570103
    //2.666846585129 2.773139913800
}

int main(){
    mortal::Scene scene;
    scene.Play();
}
