#include <string>
#include <ctime>
#include <cstdlib>
#include "Motor.h"
#include "Car.h"
#include "DataGenerator.h"
using namespace std;

void saveToFile(const string& cccd, const string& filename) {
    ofstream out(filename, ios::app);
    if (!out.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }
    out << cccd << endl;
    out.close();
}
int main(){
     // Khởi tạo hệ thống
    
    
    for (int i = 0; i < 555555 ; i++){
        string bienSo = DataGenerator::generateBienSo();
        int j = rand () % 3;
        for (int k = 0; k < j; k++){
            string loi = DataGenerator::generateLoi();
            string ngay = DataGenerator::generateNgay();
            bienSo = bienSo + " " + loi + " " + ngay;
        }
        saveToFile(bienSo,"bienso.txt");
    }
}