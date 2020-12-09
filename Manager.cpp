//
// Created by Knight on 2020/12/9.
//
#include "Manager.h"
#include "Player.h"
#include <algorithm>

Manager::Manager() {
    this->Initilize();
    this->createPlayer();
    this->loadRecord();
}

Manager::~Manager() {

}

void Manager::showMenu() {
    int wid = 30;
    string menulst[] = {"欢迎参加比赛", "开始比赛", "查看往届记录", "清空比赛记录", "退出程序"};
    vector<string> v;
    string ud = string(wid, '*');
    v.push_back(ud);
    int len = sizeof(menulst) / sizeof(menulst[0]);
    for (int i = 0; i < len; i++) {
        string str;
        if (i > 0) {
            int slen = (wid - menulst[i].length() * 2 / 3 - 1) / 2;
            string sd = string(slen, '*');
            str = sd + " " + to_string(i) + "." + menulst[i] + " " + sd;
        } else {
            int slen = (wid - menulst[i].length() * 2 / 3) / 2;
            string sd = string(slen, '*');
            str = sd + " " + menulst[i] + " " + sd;
        }
        v.push_back(str);
    }
    v.push_back(ud);

    for (vector<string>::iterator it = v.begin(); it != v.end(); it++) {
        cout << (*it) << endl;
    }
}

void Manager::exitSystem() {
    cout << "欢迎下次试用" << endl;
    exit(0);
}

void Manager::Initilize() {
    this->v1.clear();
    this->v2.clear();
    this->victory.clear();
    this->m_Player.clear();
    this->m_Record.clear();
    this->m_Index = 1;

}

void Manager::createPlayer() {
    string nameSeed = "ABCDEFGHIJKLMNOPQ";
    string name = "选手";
    for (int i = 0; i < nameSeed.size(); i++) {
        Player p;
        p.m_Name = name + nameSeed[i];
        for (int j = 0; j < 2; j++) {
            p.m_Score[j] = 0;
        }
        this->v1.push_back(i + 10001);
        this->m_Player.insert(make_pair(i + 10001, p));
    }
}

void Manager::drawMatch() {
    cout << "第 <<" << this->m_Index << ">> 轮选手正在抽签" << endl;
    cout << "------------------------------------------" << endl;
    cout << "抽签结果如下:" << endl;
    if (this->m_Index == 1) {
        random_shuffle(v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
            cout << (*it) << " ";
        }
        cout << endl;
    } else {
        random_shuffle(v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
            cout << (*it) << " ";
        }
        cout << endl;
    }
}

void Manager::conTest() {
    srand((unsigned int)time(NULL));
    cout << ">>>>>>>>>>>>第" << this->m_Index << "轮比赛正式开始" << endl;
    multimap<double, int, greater<double>> groupScore;
    int num = 0; //记录人员个数 6人一组
    vector<int> v_Src;
    if (m_Index == 1) {
        v_Src = this->v1;
    } else {
        v_Src = this->v2;
    }

    for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
        //评委打分
        deque<double> d;
        for (int i = 0; i < 10; i++) {
            double score = (rand() % 401 + 600) / 10;
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front();
        d.pop_back();
        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double) d.size();
        this->m_Player[*it].m_Score[this->m_Index - 1] = avg;
        groupScore.insert(make_pair(avg, (*it)));
        num++;
        if (num % 6 == 0) {
            cout << "第" << num / 6 << "组比赛名次:" << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
                 it != groupScore.end(); it++) {
                cout << "编号:" << (*it).second << " "
                     << "姓名:" << this->m_Player[(*it).second].m_Name << " "
                     << "分数:" << (*it).first << endl;
            }

            //取前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); count < 3; it++, count++) {
                if (this->m_Index == 1) {
                    this->v2.push_back((*it).second);
                } else {
                    this->victory.push_back((*it).second);
                }

            }
            groupScore.clear();
        }
    }
    cout << "第" << this->m_Index << "轮比赛正式结束" << endl;
}

void Manager::showScore() {
    cout << "------------第" << this->m_Index << "轮晋级选手如下:" << endl;
    vector<int> v;
    if (this->m_Index == 1) {
        v = this->v2;
    } else {
        v = this->victory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "编号:" << (*it) << " "
             << "姓名:" << this->m_Player[(*it)].m_Name << " "
             << "分数" << this->m_Player[(*it)].m_Score[this->m_Index - 1] << endl;
    }

}

void Manager::saveRecord() {
    ofstream ofs;
    ofs.open("match.csv", ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "文件保存失败" << endl;
        exit(9);
    } else {
        for (vector<int>::iterator it = this->victory.begin(); it != this->victory.end(); it++) {
            ofs << *it << ","
                << this->m_Player[*it].m_Name << ","
                << this->m_Player[*it].m_Score[1] << ",";
        }
        ofs << endl;
    }
    ofs.close();
    cout << "记录已经保存" << endl;
    this->Initilize();
    this->createPlayer();
    this->loadRecord();
}

void Manager::loadRecord() {
    ifstream ifs;
    ifs.open("match.csv", ios::in);
    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;
    ifs.putback(ch);
    int index=0;
    string data;
    while (ifs >> data) {
        int pos = -1;
        int start = 0;
        vector<string> vdata;
        while (true) {
            pos = data.find(',', start);
            if (pos != -1) {
                string tmp = data.substr(start, pos - start);
                vdata.push_back(tmp);
                start = pos + 1;
            } else {
                break;
            }
        }
//        for(vector<string>::iterator it=vdata.begin();it!=vdata.end();it++){
//            cout << (*it) <<" ";
//        }
//        cout <<endl;
        this->m_Record.insert(make_pair(index,vdata));
        index++;
    }
    ifs.close();
}

void Manager::showRecord(){
    for(int i=0;i<this->m_Record.size();i++){
        cout << "第" << i + 1 << "届比赛: "
             << "冠军编号:" << this->m_Record[i][0] << " "
             << "姓名:" << this->m_Record[i][1] << " "
             << "得分:" << this->m_Record[i][2] << endl;
    }
}

void Manager::clearRecord(){
    ofstream ofs;
    ofs.open("match.csv",ios::trunc);
    ofs.close();
    this->Initilize();
    this->createPlayer();
    this->loadRecord();
    cout << "清空成功" <<endl;
}

void Manager::startMatch() {
    //第一轮
    //抽签
    this->drawMatch();
    //比赛
    this->conTest();
    //显示结果
    this->showScore();
    //第二轮
    this->m_Index++;
    //抽签
    this->drawMatch();
    //比赛
    this->conTest();
    //最终结果
    this->showScore();
    //保存到文件
    this->saveRecord();
    cout << "本届比赛结束" << endl;
}