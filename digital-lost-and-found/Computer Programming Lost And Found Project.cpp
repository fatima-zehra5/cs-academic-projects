#include <iostream>
#include <fstream>

using namespace std;

const int MAX_ITEMS = 100;

struct Item {
    char name[50];
    char description[100];
    char location[50];
};

void inputLine(char* arr, int size) {
    char ch;
    int i = 0;
    while (true) {
        ch = cin.get();
        if (ch == '\n' || i >= size - 1)
            break;
        arr[i++] = ch;
    }
    arr[i] = '\0';
}

void reportLostItem() {
    ofstream file("lost_items.txt", ios::app);
    if (!file) return;

    Item item;
    cout << "Enter item name: ";
    cin.get();
    inputLine(item.name, 50);
    cout << "Enter description: ";
    inputLine(item.description, 100);
    cout << "Enter location: ";
    inputLine(item.location, 50);

    file << item.name << "\n" << item.description << "\n" << item.location << "\n";
    file.close();
    cout << "Lost item reported!\n";
}

void reportFoundItem() {
    ofstream file("found_items.txt", ios::app);
    if (!file) return;

    Item item;
    cout << "Enter item name: ";
    cin.get();
    inputLine(item.name, 50);
    cout << "Enter description: ";
    inputLine(item.description, 100);
    cout << "Enter location: ";
    inputLine(item.location, 50);

    file << item.name << "\n" << item.description << "\n" << item.location << "\n";
    file.close();
    cout << "Found item reported!\n";
}

void viewLostItems() {
    ifstream file("lost_items.txt");
    if (!file) {
        cout << "No lost items file.\n";
        return;
    }

    Item item;
    cout << "\n--- Lost Items ---\n";
    while (file.getline(item.name, 50)) {
        file.getline(item.description, 100);
        file.getline(item.location, 50);
        cout << "Name: " << item.name << "\n";
        cout << "Description: " << item.description << "\n";
        cout << "Location: " << item.location << "\n\n";
    }

    file.close();
}

void viewFoundItems() {
    ifstream file("found_items.txt");
    if (!file) {
        cout << "No found items file.\n";
        return;
    }

    Item item;
    cout << "\n--- Found Items ---\n";
    while (file.getline(item.name, 50)) {
        file.getline(item.description, 100);
        file.getline(item.location, 50);
        cout << "Name: " << item.name << "\n";
        cout << "Description: " << item.description << "\n";
        cout << "Location: " << item.location << "\n\n";
    }

    file.close();
}

bool isMatch(Item lost, Item found) {
    int matchCount = 0;
    for (int i = 0; lost.name[i] != '\0' && found.name[i] != '\0'; i++) {
        if (lost.name[i] == found.name[i]) matchCount++;
    }

    int locationMatch = 0;
    for (int i = 0; lost.location[i] != '\0' && found.location[i] != '\0'; i++) {
        if (lost.location[i] == found.location[i]) locationMatch++;
    }

    return matchCount >= 3 && locationMatch >= 3;
}

void matchItems() {
    ifstream lostFile("lost_items.txt");
    ifstream foundFile("found_items.txt");

    if (!lostFile || !foundFile) {
        cout << "Files not found.\n";
        return;
    }

    Item lostList[MAX_ITEMS], foundList[MAX_ITEMS];
    int lostCount = 0, foundCount = 0;

    while (lostFile.getline(lostList[lostCount].name, 50)) {
        lostFile.getline(lostList[lostCount].description, 100);
        lostFile.getline(lostList[lostCount].location, 50);
        lostCount++;
    }
    lostFile.close();

    while (foundFile.getline(foundList[foundCount].name, 50)) {
        foundFile.getline(foundList[foundCount].description, 100);
        foundFile.getline(foundList[foundCount].location, 50);
        foundCount++;
    }
    foundFile.close();

    bool matched = false;
    bool isMatched[MAX_ITEMS] = {false};

    cout << "\n--- Matched Items ---\n";
    for (int i = 0; i < lostCount; i++) {
        for (int j = 0; j < foundCount; j++) {
            if (isMatch(lostList[i], foundList[j])) {
                matched = true;
                isMatched[i] = true;
                cout << "Item: " << lostList[i].name << "\n";
                cout << "Lost Desc: " << lostList[i].description << "\n";
                cout << "Found Desc: " << foundList[j].description << "\n";
                cout << "Lost Loc: " << lostList[i].location << " | Found Loc: " << foundList[j].location << "\n\n";
            }
        }
    }

    if (!matched) {
        cout << "No matches found.\n";
    } else {
        ofstream lostOut("lost_items.txt");
        for (int i = 0; i < lostCount; i++) {
            if (!isMatched[i]) {
                lostOut << lostList[i].name << "\n"
                        << lostList[i].description << "\n"
                        << lostList[i].location << "\n";
            }
        }
        lostOut.close();
        cout << "Matched lost items removed from lost_items.txt\n";
    }
}

void clearFiles() {
    ofstream lost("lost_items.txt");
    ofstream found("found_items.txt");
    lost.close();
    found.close();
    cout << "All records cleared!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- University Lost & Found System ---\n";
        cout << "1. Report Lost Item\n";
        cout << "2. Report Found Item\n";
        cout << "3. View Lost Items\n";
        cout << "4. View Found Items\n";
        cout << "5. Match Lost & Found Items\n";
        cout << "6. Clear All Data\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: reportLostItem(); break;
            case 2: reportFoundItem(); break;
            case 3: viewLostItems(); break;
            case 4: viewFoundItems(); break;
            case 5: matchItems(); break;
            case 6: clearFiles(); break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}

