#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Destination {
    string place;
    string food;
    int cost;
};

class TravelPlanner {
private:
    vector<Destination> places;

public:

    // Load CSV File
    void loadCSV(string filename) {

        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error opening file.\n";
            return;
        }

        string line;

        // Skip header
        getline(file, line);

        while (getline(file, line)) {

            stringstream ss(line);

            string place, food, costStr;

            getline(ss, place, ',');
            getline(ss, food, ',');
            getline(ss, costStr, ',');

            Destination d;

            d.place = place;
            d.food = food;
            d.cost = stoi(costStr);

            places.push_back(d);
        }

        file.close();
    }

    // Recommend trips under budget
    void recommendTrips(int budget) {

        cout << "\n===== Recommended Trips =====\n";

        bool found = false;

        for (int i = 0; i < places.size(); i++) {

            if (places[i].cost <= budget) {

                found = true;

                cout << "\nPlace : "
                     << places[i].place << endl;

                cout << "Food  : "
                     << places[i].food << endl;

                cout << "Cost  : Rs."
                     << places[i].cost << endl;
            }
        }

        if (!found) {
            cout << "\nNo trips found within budget.\n";
        }
    }
};

int main() {

    TravelPlanner planner;

    planner.loadCSV("travel.csv");

    int budget;

    cout << "===== AI Travel Planner =====\n";

    cout << "\nEnter your budget: ";
    cin >> budget;

    planner.recommendTrips(budget);

    return 0;
}
