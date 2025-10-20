#include <iostream>
#include <string>
using namespace std;

void displayHomeMenu() {
    int choice;
    do {
        system("cls"); 
        cout << "=== MENU HOME ===\n";
        cout << "1. Cong an\n";
        cout << "2. Ngu dan\n";
        cout << "3. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCongAnMenu();
                break;
            case 2:
                displayNguDanMenu();
                break;
            case 3:
                cout << "Tam biet!\n";
                return;
            default:
                cout << "Lua chon khong hop le! Vui long thu lai.\n";
                system("pause");
        }
    } while (true);
}

// Hàm hiển thị menu Công an và xử lý lựa chọn
void displayCongAnMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== MENU CONG AN ===\n";
        cout << "1. Xem thong tin\n";
        cout << "2. Them thong tin\n";
        cout << "3. Xoa thong tin\n";
        cout << "4. Quay lai\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Hien thi thong tin...\n";
                system("pause");
                break;
            case 2:
                cout << "Them thong tin...\n";
                system("pause");
                break;
            case 3:
                cout << "Xoa thong tin...\n";
                system("pause");
                break;
            case 4:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long thu lai.\n";
                system("pause");
        }
    } while (true);
}

// Hàm hiển thị menu Ngư dân và xử lý lựa chọn
void displayNguDanMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== MENU NGU DAN ===\n";
        cout << "1. Xem thong tin\n";
        cout << "2. Them thong tin\n";
        cout << "3. Theo CCCC\n";
        cout << "4. Theo bien so xe\n";
        cout << "5. Quay lai\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Hien thi thong tin...\n";
                system("pause");
                break;
            case 2:
                cout << "Them thong tin...\n";
                system("pause");
                break;
            case 3:
                cout << "Theo CCCC...\n";
                system("pause");
                break;
            case 4:
                cout << "Theo bien so xe...\n";
                system("pause");
                break;
            case 5:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long thu lai.\n";
                system("pause");
        }
    } while (true);
}

// Hàm chính
int main() {
    cout << "=== BAT DAU ===\n";
    system("pause");
    displayHomeMenu();
    return 0;
}