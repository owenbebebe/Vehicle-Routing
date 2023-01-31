#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>

using namespace std;

class Location {
public:
    map<int, double> distance_list;
    double x, y;
    int cap, id;
    bool visited;
    //constructor
    Location(int i, int capp, double x1, double x2) {
        id = i; 
        cap = capp;
        x = x1;
        y = x2;
        visited = false;
    }
    double calcDist(Location* lc) {
        double distance = sqrt(pow((lc->x - x), 2) + pow((lc->y - y), 2));
        distance_list[lc->id] = distance;
        return distance;
    }
};


int main()
{
    cout << "*****Vehicle Routing******" << endl;
    /*string filenames = "filenames";
    ifstream iinfile;
    iinfile.open(filenames);
    string s;
    iinfile >> s; 
    iinfile.close();
    int ssize = s.size();
    while (s.size() != 0) {
        int init = s.find(",");
        string filename = "vrp_" + s.substr(0, init);
        ifstream infile;*/
    string filename;
    cin >> filename;
    ifstream infile; 
        infile.open("input/"+ filename);
        if (!infile.is_open()) {
            cout << "Can't open this file!" << endl << endl;
        }
        int number_vehicle, number_customer, vehicle_cap;
        int i;
        infile >> i;
        number_customer = i;
        infile >> i;
        number_vehicle = i;
        infile >> i;
        vehicle_cap = i;
        double i1, i2;
        vector<Location*> location_list;
        int id = 0;
        while (infile >> i) {
            infile >> i1;
            infile >> i2;
            Location* Loc = new Location(id, i, i1, i2);
            id++;
            location_list.push_back(Loc);
        }
        infile.close();
        //at this point have successfully read the file
        //get the first line of the text file
        //Greedy Approach
        /*
            1. start with the first vehicle at the warehouse
            2. with in the vehicle capacity travel to the nearest location
            3. send the second vehicle until every demand is reached
        */
        vector<vector<int>> ans;
        int visited_count = 1;
        int vehicle_id = 0;
        double ans_cost = 0;
        vector<bool> visited(number_customer);
        //while not every location is visited
        while (visited_count < number_customer) {
            if (vehicle_id < number_vehicle) {
                int v_cap = vehicle_cap;
                vector<int> v_travel;
                v_travel.push_back(0);
                int cur_loc = 0;
                visited[cur_loc] = true;
                while (v_cap > 0) {
                    //for each facility calc the distance to other location
                    double min = DBL_MAX;
                    double cur_distance;
                    int min_i = -1;
                    for (int i = 0; i < number_customer; i++) {
                        if (!visited[i]) {
                            cur_distance = location_list[cur_loc]->calcDist(location_list[i]);
                            //check if the distance is the most min
                            if (cur_distance < min) {
                                //check if its in the capacity
                                if ((v_cap - location_list[i]->cap) >= 0) {
                                    min = cur_distance;
                                    min_i = i;
                                }
                            }
                        }
                    }
                    //if we couldnt not find min move to the next vihicle
                    if (min_i == -1) {
                        vehicle_id++;
                        v_travel.push_back(0);
                        ans_cost += location_list[cur_loc]->calcDist(location_list[0]);
                        ans.push_back(v_travel);
                        cout << "v_id = " << vehicle_id << "v_cap = " << v_cap << endl;
                        v_cap = -1;
                    }
                    //else add the location to the cur vehicle
                    else {
                        cur_loc = min_i;
                        visited[cur_loc] = true;
                        ans_cost += min;
                        v_cap -= location_list[cur_loc]->cap;
                        v_travel.push_back(cur_loc);
                        if (v_cap == 0) {
                            v_travel.push_back(0);
                            ans_cost += min;
                            //calculate the last loc to warehouse
                            ans_cost += location_list[cur_loc]->calcDist(location_list[0]);
                            ans.push_back(v_travel);
                            vehicle_id++;
                            cout << "v_id = " << vehicle_id << "v_cap = " << v_cap << endl;
                        }
                        visited_count++;
                    }
                }
            }
            else {
                for (int t = 0; t < number_customer; t++) {
                    if (visited[t] == false) visited_count++;
                }
            }
        }
        
        while (vehicle_id < number_vehicle) {
            vector<int> temp;
            temp.push_back(0);
            ans.push_back(temp);
            vehicle_id++;
        }
        //export the file
        ofstream output(filename + "_output");
        output << ans_cost << endl;
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[i].size(); j++) {
                output << ans[i][j] << " ";
            }
            output << endl;
        }
        output.close();
        /*s = s.substr(init + 1, s.size() - init);
    }
    return 0;*/
}

