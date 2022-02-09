#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const double EPS = 1e-7;
const int subjectCnt = 4;
const string subject[subjectCnt] = {"Chinese", "Mathematics", "English", "Programming"};

struct Student {
    string SID, name;
    int CID, score[subjectCnt];
    bool del;
    friend istream& operator>>(istream&, Student&);
    friend ostream& operator<<(ostream&, Student&);
    int count() {
        int ret = 0;
        FOR(i, 0, subjectCnt - 1) ret += score[i];
        return ret;
    }
    int passed() {
        int ret = 0;
        FOR(i, 0, subjectCnt - 1) ret += (score[i] >= 60);
        return ret;
    }
    Student() {del = 0;}
};

istream& operator>>(istream& in, Student& stu) {
    in >> stu.CID >> stu.name;
    FOR(i, 0, subjectCnt - 1) in >> stu.score[i];
    return in;
}

ostream& operator<<(ostream& out, Student& stu) {
    out << stu.SID << ' ' << stu.CID << ' ' << stu.name << ' ';
    FOR(i, 0, subjectCnt - 1) out << stu.score[i] << ' ';
    int tot = stu.count();
    out << tot << ' ' << tot / 4.0 + EPS;
    return out;
}

vector<Student> vec;

int mainMenu() {
    cout << "Welcome to Student Performance Management System (SPMS).\n\n";
    cout << "1 - Add\n";
    cout << "2 - Remove\n";
    cout << "3 - Query\n";
    cout << "4 - Show ranking\n";
    cout << "5 - Show Statistics\n";
    cout << "0 - Exit\n" << endl;
    int ret; cin >> ret;
    return ret;
}

void add() {
    Student now; string SID;
    while (true) {
        cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << endl;
        cin >> SID;
        if (SID == "0") break;
        cin >> now; now.SID = SID;
        bool isDulplicated = 0;
        for (Student &stu : vec) {
            if (!stu.del && stu.SID == now.SID) {
                cout << "Duplicated SID." << endl;
                isDulplicated = 1;
            }
        }
        if (!isDulplicated) vec.push_back(now);
    }
    return;
}

void remove() {
    while (true) {
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
        string str; cin >> str;
        if (str == "0") break;
        int cnt = 0;
        for (auto &stu : vec) {
            if (!stu.del && (stu.SID == str || stu.name == str)) {
                ++cnt;
                stu.del = 1;
                if (stu.SID == str) break;
            }
        }
        cout << cnt << " student(s) removed." << endl;
    }
}

int calcRank(Student &stu) {
    int ret = 0, now = stu.count();
    for (auto &x : vec) ret += (!x.del && x.count() > now);
    return ret + 1;
}

void query() {
    while (true) {
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
        string str; cin >> str;
        if (str == "0") break;
        for (auto &stu : vec) {
            if (!stu.del && (stu.SID == str || stu.name == str)) {
                int rnk = calcRank(stu);
                cout << rnk << ' ' << stu << endl;
                if (stu.SID == str) break;
            }
        }
    }
    return;
}

void statistics() {
    cout << "Please enter class ID, 0 for the whole statistics." << endl;
    int need; cin >> need;
    int passedCnt[subjectCnt + 1] = {0}, totScore[subjectCnt] = {0}, subPassed[subjectCnt] = {0}, tot = 0;
    for (auto &stu : vec) {
        if (stu.del) continue;
        if (!need || stu.CID == need) {
            ++tot;
            ++passedCnt[stu.passed()];
            FOR(i, 0, subjectCnt - 1) totScore[i] += stu.score[i], subPassed[i] += (stu.score[i] >= 60);
        }
    }
    FOR(i, 0, subjectCnt - 1) {
        cout << subject[i] << endl;
        cout << "Average Score: " << 1.0 * totScore[i] / tot + EPS << endl;
        cout << "Number of passed students: " << subPassed[i] << endl;
        cout << "Number of failed students: " << tot - subPassed[i] << endl;
        cout << endl;
    }
    cout << "Overall:" << endl;
    cout << "Number of students who passed all subjects: " << passedCnt[subjectCnt] << endl;
    DEC(i, subjectCnt - 1, 1) {
        passedCnt[i] += passedCnt[i + 1];
        cout << "Number of students who passed " << i << " or more subjects: " << passedCnt[i] << endl;
    }
    cout << "Number of students who failed all subjects: " << passedCnt[0] << endl;
    cout << endl;
    return;
}

int main() {
    int op; cout << fixed << setprecision(2);
    while (op = mainMenu()) {
        if (op == 1) add();
        else if (op == 2) remove();
        else if (op == 3) query();
        else if (op == 4) cout << "Showing the ranklist hurts students' self-esteem. Don't do that." << endl;
        else statistics();
    }
}