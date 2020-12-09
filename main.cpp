#include <iostream>
#include "Manager.h"
#include <ctime>

int main() {
    Manager m;
    int choice;
    while (true) {
        m.showMenu();
        cout << "输入选择:" <<endl;
        cin >> choice;
        while(!cin.good()){
            cout << "无效选项" <<endl;
            cin.clear();
            cin.ignore();
            m.showMenu();
            cout << "输入选择:" <<endl;
            cin >> choice;
        }
        switch (choice) {
            case 1: // 开始比赛
                m.startMatch();
                break;
            case 2: // 查看
                m.showRecord();
                break;
            case 3: // 清空
                m.clearRecord();
                break;
            case 4: // 退出
                m.exitSystem();
                break;
            default: // 其他
//                system("clear");
                break;
        }
    }
}
