//
// Created by Knight on 2020/12/9.
//

#ifndef COMPETITION_MANAGER_H
#define COMPETITION_MANAGER_H

#endif //COMPETITION_MANAGER_H
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "Player.h"
#include <numeric>
#include <functional>
#include <fstream>
using namespace std;

class Manager{
public:
    vector<int> v1; //第一轮比赛选手编号
    vector<int> v2; //第二轮比赛选手编号（第一轮晋级）
    vector<int> victory; //胜出选手编号
    map<int,Player> m_Player;
    bool fileIsEmpty;
    int m_Index;
    map<int,vector<string>> m_Record;
    Manager();
    ~Manager();
    void showMenu();
    void exitSystem();
    void Initilize();
    void createPlayer();
    void startMatch();
    void drawMatch();
    void conTest();
    void showScore();
    void saveRecord();
    void loadRecord();
    void showRecord();
    void clearRecord();
};