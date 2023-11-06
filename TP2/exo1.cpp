#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <thread>
#include <queue>

using namespace std;

int numTasks = 0;

double factorielle(int n) {
    double res = 1;

    for (int i = 1; i <= n; i++) {
        res = res * i;
    }
    return res;
}

double calcul(int i) {
    double res = 0;
    res = pow(-1, i) / factorielle(i);
    return res;
}

void autoAction(int i, double *res) {
    numTasks++;
    *res += calcul(i);
    numTasks--;
}

double threadPool(int n) {
    vector<int> tasks;
    double res = 0;

    for (int i = 0; i < n; i++) {
        tasks.push_back(i);
    }

    while (1) {
        if ((numTasks < n) && (tasks.size() > 0)) {
            thread t(autoAction, tasks.back(), &res);
            t.join();
            tasks.pop_back();
        } else if (numTasks <= 0) {
            break;
        }
    }
    return res;
}

string versMinuscule(string s, string *res) {
    *res = "";
    for (int i = 0; i < s.size(); i++) {
        *res += tolower(s[i]);
    }
    return *res;
}

string chiffreToText(string s, string *res) {
    *res = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            *res += "zero";
        } else if (s[i] == '1') {
            *res += "un";
        } else if (s[i] == '2') {
            *res += "deux";
        } else if (s[i] == '3') {
            *res += "trois";
        } else if (s[i] == '4') {
            *res += "quatre";
        } else if (s[i] == '5') {
            *res += "cinq";
        } else if (s[i] == '6') {
            *res += "six";
        } else if (s[i] == '7') {
            *res += "sept";
        } else if (s[i] == '8') {
            *res += "huit";
        } else if (s[i] == '9') {
            *res += "neuf";
        } else {
            *res += s[i];
        }
    }
    return *res;
}

string supprimerPonctuation(string s, string *res) {
    *res = "";
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '.') or (s[i] == ',') or (s[i] == ';') or (s[i] == ':') or (s[i] == '!') or (s[i] == '?')) {
            *res += "";
        } else {
            *res += s[i];
        }
    }
    return *res;
}

vector<string> tokeniser(string s, vector<string> *res) {
    string tmp = "";

    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == ' ') or (s[i] == '\'')) {
            res->push_back(tmp);
            tmp = "";
        } else {
            tmp += s[i];
        }
    }

    // ajoute le dernier mot
    res->push_back(tmp);

    return *res;
}

/*
void pipeline(queue<string> phrases) {
    queue<string> tache2;
    queue<vector<string>> tache3;
    string res = "";
    vector<string> res2;
    int counter = phrases.size();

    while(1) {
        thread t1(versMinuscule, phrases.front(), &res);
        cout << res << endl;
        t1.join();
        tache2.push(res);
        phrases.pop();

        thread t2(tokeniser, tache2.front(), &res2);
        t2.join();
        tache3.push(res2);
        tache2.pop();

        if (tache2.size()<=0) {
            break;
        }
    }
    */
void pipeline(queue<string> queueTache1) {
    queue<string> queueTache2;
    queue<string> queueTache3;
    queue<string> queueTache4;

    vector<vector<string>> resFinal;

    int counter = queueTache1.size();

    auto tache1 = [&queueTache1, &queueTache2]() {
        int counter = queueTache1.size();
        string resTache1 = "";
        for (int i = 0; i < counter; i++) {
            versMinuscule(queueTache1.front(), &resTache1);
            queueTache2.push(resTache1);
            queueTache1.pop();
        }
    };

    auto tache2 = [&queueTache2, &queueTache3]() {
        int counter = queueTache2.size();
        string resTache2 = "";
        for (int i = 0; i < counter; i++) {
            chiffreToText(queueTache2.front(), &resTache2);
            queueTache3.push(resTache2);
            queueTache2.pop();
        }
    };

    auto tache3 = [&queueTache3, &queueTache4] {
        int counter = queueTache3.size();
        string resTache3 = "";
        for (int i = 0; i < counter; i++) {
            supprimerPonctuation(queueTache3.front(), &resTache3);
            queueTache4.push(resTache3);
            queueTache3.pop();
        }
    };

    auto tache4 = [&queueTache4, &resFinal]() {
        int counter = queueTache4.size();
        for (int i = 0; i < counter; i++) {
            vector<string> res;
            tokeniser(queueTache4.front(), &res);
            queueTache4.pop();

            resFinal.push_back(res);
        }
    };

    // lance les threads
    for (int i = 0; i < counter; i++) {
        thread t1(tache1);
        thread t2(tache2);
        thread t3(tache3);
        thread t4(tache4);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

    // affiche le résultat
    for (int i = 0; i < resFinal.size(); i++) {
        for (int j = 0; j < resFinal[i].size(); j++) {
            cout << resFinal[i][j] << " / ";
        }
        cout << endl;
    }

}

/*void bruteForce() {

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string res = "";

    for (int i = 0; i < alphabet.size(); i++) {
        for (int j = 0; j < alphabet.size(); j++) {
            for (int k = 0; k < alphabet.size(); k++) {
                for (int l = 0; l < alphabet.size(); l++) {
                    for (int m = 0; m < alphabet.size(); m++) {
                        res = string() + alphabet[i] + alphabet[j] + alphabet[k] + alphabet[l] + alphabet[m];
                        if (md5(res) == "3ed7dceaf266cafef032b9d5db224717") {
                            cout << res << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
}*/


int main() {
    cout << factorielle(3) << endl;
    //cout << approxE1(2) << endl;
    cout << threadPool(5) << endl;

    
    queue<string> phrases;
    string s1 = "BONJOUR C'est la phrase 1.";
    string s2 = "c la phrase! 2";
    string s3 = "c la phrase 3";

    phrases.push(s1);
    phrases.push(s2);
    phrases.push(s3);

    pipeline(phrases);


    //cout << "md5 of 'grape': " << md5("secret") << endl;
   // bruteForce();
    return 0;
}