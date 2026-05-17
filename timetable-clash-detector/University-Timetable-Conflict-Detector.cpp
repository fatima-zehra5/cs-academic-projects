#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool clash(int s1, int e1, int s2, int e2) {
    if (e1 <= s2 || e2 <= s1) return false;
    return true;
}

int main() {
    int n;
    cout << "===== University Timetable Conflict Detection =====\n\n";

    cout << "Enter number of courses: ";
    cin >> n;

    if (n <= 0) {
        cout << "No courses entered. Exiting.\n";
        return 0;
    }

    vector<string> name(n);
    vector<int> start(n), endt(n);

    cout << "\nPlease enter each course as:\n";
    cout << "CourseName StartHour EndHour  (24-hour format, e.g. MTH101 9 11)\n";
    cout << "Note: 0 <= StartHour < 24, 0 <= EndHour < 24 and EndHour > StartHour.\n\n";

    for (int i = 0; i < n; i++) {
        while (true) {
            cout << "Course " << i + 1 << ": ";
            cin >> name[i] >> start[i] >> endt[i];

            bool ok = true;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "  Invalid input type. Please enter again (e.g. MTH101 9 11).\n";
                ok = false;
            }

            if (ok && (start[i] < 0 || start[i] > 23 || endt[i] < 0 || endt[i] > 23)) {
                cout << "  Invalid time. Hours must be between 0 and 23.\n";
                ok = false;
            }

            if (ok && endt[i] <= start[i]) {
                cout << "  Invalid time range. EndHour must be strictly greater than StartHour.\n";
                ok = false;
            }

            if (ok) break;
        }
    }

    vector<vector<int>> R(n, vector<int>(n, 0));
    bool anyClash = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (clash(start[i], endt[i], start[j], endt[j])) {
                R[i][j] = 1;
                anyClash = true;
            }
        }
    }

    cout << "\n==============================================\n";

    if (anyClash) {
        cout << "Result: CLASHES DETECTED in the timetable.\n";
    } else {
        cout << "Result: NO CLASHES found between the courses.\n";
    }

    cout << "\nRelation R (clash matrix):\n\n";

    cout.width(12);
    cout << left << "";
    for (int j = 0; j < n; j++) {
        cout.width(12);
        cout << left << name[j];
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout.width(12);
        cout << left << name[i];
        for (int j = 0; j < n; j++) {
            cout.width(12);
            cout << left << R[i][j];
        }
        cout << "\n";
    }

    cout << "\nList of pairwise clashes (easy to read):\n";
    bool anyPairPrint = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (R[i][j] == 1) {
                anyPairPrint = true;
                cout << "  " << name[i] << " and " << name[j]
                     << " are clashing (overlapping time slots).\n";
            }
        }
    }
    if (!anyPairPrint) {
        cout << "  No pair of courses is clashing.\n";
    }

    bool symmetric = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (R[i][j] != R[j][i]) {
                symmetric = false;
            }
        }
    }

    cout << "\n----------------------------------------------\n";
    if (symmetric)
        cout << "Symmetry check: Relation R IS symmetric.\n";
    else
        cout << "Symmetry check: Relation R is NOT symmetric.\n";

    cout << "\n3-way clashes (sets of 3 courses that all clash with each other):\n";
    bool any3 = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (R[i][j] && R[j][k] && R[i][k]) {
                    any3 = true;
                    cout << "  { " << name[i] << ", " << name[j]
                         << ", " << name[k] << " }\n";
                }
            }
        }
    }
    if (!any3) {
        cout << "  No 3-way clashes found.\n";
    }

    cout << "\n----------------------------------------------\n";
    cout << "Simple conflict-free suggestion (sorted by start time):\n";

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (start[idx[j]] < start[idx[i]]) {
                swap(idx[i], idx[j]);
            }
        }
    }

    for (int t = 0; t < n; t++) {
        int i = idx[t];
        cout << "  " << name[i] << " : "
             << start[i] << ":00 - " << endt[i] << ":00\n";
    }

    cout << "\n===== End of analysis =====\n";
    return 0;
}

