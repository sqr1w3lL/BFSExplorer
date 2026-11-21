#include <iostream>
#include <algorithm>
#include <climits>
#include <windows.h>
#include <locale>

using namespace std;

struct Task {
    int id;
    int earliestStart;
    int latestFinish;
    int duration;
    int startTime;
};

bool compareTasks(Task a, Task b) {
    return a.latestFinish < b.latestFinish;
}

bool scheduleTasks(int robots, Task* tasks, int n) {
    sort(tasks, tasks + n, compareTasks);

    int* robotAvailable = new int[robots];
    for (int i = 0; i < robots; i++)
        robotAvailable[i] = 0;

    for (int i = 0; i < n; i++) {
        Task& t = tasks[i];
        int earliestStart = t.earliestStart;

        int selectedRobot = -1;
        int minAvailableTime = INT_MAX;

        for (int r = 0; r < robots; r++) {
            if (robotAvailable[r] <= t.latestFinish - t.duration &&
                max(robotAvailable[r], earliestStart) < minAvailableTime) {
                minAvailableTime = max(robotAvailable[r], earliestStart);
                selectedRobot = r;
            }
        }

        if (selectedRobot == -1) {
            delete[] robotAvailable;
            return false;
        }

        t.startTime = minAvailableTime;
        robotAvailable[selectedRobot] = t.startTime + t.duration;
    }

    delete[] robotAvailable;
    return true;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ukr");

    int robots, n;
    cout << "Введіть кількість роботів: ";
    cin >> robots;
    cout << "Введіть кількість завдань: ";
    cin >> n;

    Task* tasks = new Task[n];

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        cout << "Завдання " << i + 1 << " (earliest start, latest finish, duration): ";
        cin >> tasks[i].earliestStart >> tasks[i].latestFinish >> tasks[i].duration;
    }

    if (scheduleTasks(robots, tasks, n)) {
        cout << "Завдання можна виконати за заданих умов.\n";
        cout << "Порядок виконання та час початку:\n";
        for (int i = 0; i < n; i++) {
            cout << "Завдання " << tasks[i].id << ": початок о " << tasks[i].startTime
                << ", тривалість " << tasks[i].duration << endl;
        }
    }
    else {
        cout << "Неможливо виконати всі завдання за заданих умов.\n";
    }

    delete[] tasks;
    return 0;
}
