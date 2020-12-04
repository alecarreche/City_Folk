#include "graph.h"

string Graph::getStationName(int id) {
    return stationID[id].name;
}

void Graph::importStations(string fileName) {
    ifstream stations;
    stations.open(fileName);

    string curRow;

    // skip header row
    getline(stations, curRow);

    while(getline(stations, curRow)) {

        Station curStation;
        string cell;
        stringstream row(curRow);

        // skip index col
        getline(row, cell, ',');

        // Stop ID
        getline(row, cell, ',');
        int ID = stoi(cell);

        // Stop Name
        getline(row, cell, ',');
        curStation.name = cell;

        // Lat
        getline(row, cell, ',');
        curStation.latitude = stod(cell);

        // Long
        getline(row, cell, ',');
        curStation.longitude = stod(cell);

        stationID.emplace(ID, curStation);
    }
}

void Graph::importEdges(string fileName) {
    ifstream edges;
    edges.open(fileName);

    string curRow;

    // skip header row
    getline(edges, curRow);

    while(getline(edges, curRow)) {

        string cell;
        stringstream row(curRow);

        // skip index col
        getline(row, cell, ',');

        // Route
        getline(row, cell, ',');
        string route = cell;

        // To
        getline(row, cell, ',');
        int to = stoi(cell);

        // From
        getline(row, cell, ',');
        int from = stoi(cell);

        // Dist
        getline(row, cell, ',');
        double distance = stod(cell);

        // "to" direction
        pair<string, double> routeDist = make_pair(route, distance);
        pair<int, pair<string, double>> edge = make_pair(to, routeDist);

        if(adjList.find(from) == adjList.end()) {
            adjList[from] = {edge};
        } else {
            adjList[from].push_back(edge);
        }

        // "from" direction
        pair<int, pair<string, double>> reverseEdge = make_pair(from, routeDist);

        if(adjList.find(to) == adjList.end()) {
            adjList[to] = {reverseEdge};
        } else {
            adjList[to].push_back(reverseEdge);
        }
    }

}

int Graph::findClosestStation(pair<double, double> loc) {
    double min = INT_MAX;
    int minInd;

    for (auto iter = stationID.begin(); iter != stationID.end(); iter++){
        Station temp = iter->second;
        double dist = sqrt(((temp.latitude - loc.first)*(temp.latitude - loc.first)) + ((temp.longitude - loc.second)*(temp.longitude - loc.second)));

        if (dist <= min){
            minInd = iter->first;
            min = dist;
        }
    }

    return minInd;
}

vector<int> Graph::dijkstra(int src, int dest)
{
    map<int, pair<int, double>> m;
    unordered_set<int> v;
    unordered_set<int> nv;
    for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
    {
        nv.insert(iter->first);
    }
    if (nv.find(src) == nv.end())
    {
        cout << "ERROR" << endl;
    }
    else
    {
        int temp = src;
        double tempd = 0;
        int newid = 0;
        double newweight = 0;
        m[temp] = make_pair(-1, tempd);
        while (!nv.empty() && newweight != -1)
        {
            nv.erase(temp);
            v.insert(temp);

            for (int i = 0; i < adjList[temp].size(); i++)
            {
                newid = adjList[temp][i].first;
                newweight = adjList[temp][i].second.second;
                if (m.find(newid) == m.end())
                    //if there is no old weight, insert newweight plus current node's weight
                {
                    double tempd2 = m[temp].second + newweight;
                    m[newid] = make_pair(temp, tempd2);
                }
                else if ((newweight + tempd) < m[newid].second)
                    //if newweight plus current node's weight is less than the old weight, change the old weight to the new, shorter one
                {
                    double tempd2 = newweight + tempd;
                    m[newid] = make_pair(temp, tempd2);
                }
                //in every other case, move on to the next one
            }
            newweight = -1;
            for (auto iter = nv.begin(); iter != nv.end(); iter++)
                //go through the unvisited nodes
            {
                if (m.find((*iter)) != m.end())
                    //if a node has not been visited but has a weight
                {
                    if (newweight > m[*iter].second || newweight == -1)
                        //and if its weight is less than our previously found node or is the first one we've found, replace it with the new one
                    {
                        newid = *iter;
                        newweight = m[*iter].second;
                    }
                }
            }
            temp = newid;
            tempd = m[newid].second;
        }
        vector<int> vec;
        stack<int> s;
        temp = dest;
        while (temp != src)
        {
            s.push(temp);
            temp = m[temp].first;
        }
        s.push(temp);
        while (!s.empty())
        {
            vec.push_back(s.top());
            s.pop();
        }
        return vec;
    }
    vector<int> v2;
    return v2;
}

double Graph::distance(int src, int dest)
{
    if (stationID.find(src) == stationID.end() || stationID.find(dest) == stationID.end())
    {
        return -1;
    }
    double srcLat = stationID[src].latitude;
    double srcLong = stationID[src].longitude;
    double destLat = stationID[dest].latitude;
    double destLong = stationID[dest].longitude;
    return sqrt(((destLong - srcLong) * (destLong - srcLong)) + ((destLat - srcLat) * (destLat - srcLat)));
}

vector<int> Graph::aStar(int src, int dest)
{
    map<int, pair<double, pair<double, pair<double, int>>>> m;

    //m[ID]
    //m[ID].first = F
    //m[ID].second.first = G
    //m[ID].second.second.first = H
    //m[ID].second.second.second = ID of previous

    unordered_set<int> v;
    //set of visited nodes

    unordered_set<int> nv;
    //set of unvisited neighbors
    int currentid = src;
    int newid = 0;
    double newweight;
    nv.insert(currentid);
    m[currentid] = make_pair(0, make_pair(0, make_pair(0, -1)));
    while (!nv.empty() && currentid != -1 && v.find(dest) == v.end())
    {
        nv.erase(currentid);
        v.insert(currentid);
        for (int i = 0; i < adjList[currentid].size(); i++)
        {
            newid = adjList[currentid][i].first;
            newweight = adjList[currentid][i].second.second;
            if (v.find(adjList[currentid][i].first) == v.end())
                //if the node has not been visited already
            {
                if (m.find(newid) == m.end())
                    //and if the new node does not exist, add it to the map and the unvisited set
                {
                    double tempg = m[currentid].second.first + newweight;
                    double tempf = tempg + distance(newid, dest);
                    m[newid] = make_pair(tempf, make_pair(tempg, make_pair(distance(newid, dest), currentid)));
                    nv.insert(newid);
                }
                else if ((newweight + m[currentid].second.first) < m[newid].second.first)
                    //and if newweight plus current node's weight is less than old weight, change the old weight to the new, shorter one
                {
                    double tempg = m[currentid].second.first + newweight;
                    double tempf = tempg + distance(newid, dest);
                    m[newid] = make_pair(tempf, make_pair(tempg, make_pair(distance(newid, dest), currentid)));
                }
            }
            else if ((newweight + m[currentid].second.first) < m[newid].second.first)
                //if the node has been visited but the newweight plus current node's weight is less than old weight, change the old weight to the new, shorter one
            {
                double tempg = m[currentid].second.first + newweight;
                double tempf = tempg + distance(newid, dest);
                m[newid] = make_pair(tempf, make_pair(tempg, make_pair(distance(newid, dest), currentid)));
            }
        }
        newweight = -1;
        for (auto iter = nv.begin(); iter != nv.end(); iter++)
            //go through the unvisited nodes
        {
            if (m.find((*iter)) != m.end())
                //if a node has not been visited but has an F
            {
                if (newweight > m[*iter].first || newweight == -1)
                    //and if its F is less than our previously found node or is the first one we've found, replace it with the new one
                {
                    newid = *iter;
                    newweight = m[*iter].first;
                }
            }
        }
        currentid = newid;
    }
    vector<int> vec;
    stack<int> s;
    currentid = dest;
    while (currentid != src)
    {
        s.push(currentid);
        currentid = m[currentid].second.second.second;
    }
    s.push(currentid);
    while (!s.empty())
    {
        vec.push_back(s.top());
        s.pop();
    }
    return vec;
}

vector<string> getStationNameVector(vector<int> vi)
{
    vector<string> vs;
    for (unsigned int i = 0; i < vi.size(); i++)
    {
        vs.push_back(getStationName(vi[i]));
    }
    return vs;
}

string convertVectorToString(vector<string> vs)
{
    string s = "";
    for (unsigned int i = 0; i < vs.size() - 1; i++)
    {
        s += vs[i];
        s += " -> ";
    }
    s += vs[cs.size() - 1];
    return s;
}

string findSwitches(vector<int> vi)
{


}
