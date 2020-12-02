#include "graph.h"

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

    return 0;
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
    if (!nv[src])
    {
        cout << "ERROR: Source vertex does not exist!" << endl;
    }
    else if (!nv[dest])
    {
        cout << "ERROR: Destination vertex does not exist!" << endl;
    }
    else
    {
        int temp = src;
        double tempd = 0;
        int newid = 0;
        double newweight = 0;
        m[temp] = pair<-1, tempd>;
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
                    m[newid] = pair<temp, tempd2>;
                }
                else if (m[newid].second > (newweight + tempd)) 
                    //if old weight is greater than newweight plus current node's weight, change the old weight to the new, shorter one
                {
                    double tempd2 = newweight + tempd;
                    m[newid] = pair<temp, tempd2>;
                }
                    //in every other case, move on to the next one
            }
            newweight = -1;
            for (auto iter = nv.begin(); iter != nv.end(); iter++)
                //go through the unvisited nodes
            {
                if (m.find((iter*)) != m.end())
                    //if a node has not been visited but has a weight
                {
                    if (newweight > m[iter*].second || newweight == -1)
                        //and if its weight is less than our previously found node or is the first one we've found, replace it with the new one
                    {
                        newid = iter*;
                        newweight = m[iter*].second;
                    }
                }
            }
            temp = newid;
            tempd = m[newid].second;
        }
        vector<int> v;
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
            v.push_back(s.top());
            s.pop();
        }
        return v;
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
    //literally copy/pasted the other one and then i'm gonna edit it so ignore the below


    map<int, pair<int, double>> m;
    unordered_set<int> v;


    for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
    {
        nv.insert(iter->first);
    }
    if (!nv[src])
    {
        cout << "ERROR: Source vertex does not exist!" << endl;
    }
    else if (!nv[dest])
    {
        cout << "ERROR: Destination vertex does not exist!" << endl;
    }
    else
    {
        int temp = src;
        double tempd = 0;
        int newid = 0;
        double newweight = 0;
        m[temp] = pair<-1, tempd>;
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
                    m[newid] = pair<temp, tempd2>;
                }
                else if (m[newid].second > (newweight + tempd))
                    //if old weight is greater than newweight plus current node's weight, change the old weight to the new, shorter one
                {
                    double tempd2 = newweight + tempd;
                    m[newid] = pair<temp, tempd2>;
                }
                //in every other case, move on to the next one
            }
            newweight = -1;
            for (auto iter = nv.begin(); iter != nv.end(); iter++)
                //go through the unvisited nodes
            {
                if (m.find((iter*)) != m.end())
                    //if a node has not been visited but has a weight
                {
                    if (newweight > m[iter*].second || newweight == -1)
                        //and if its weight is less than our previously found node or is the first one we've found, replace it with the new one
                    {
                        newid = iter*;
                        newweight = m[iter*].second;
                    }
                }
            }
            temp = newid;
            tempd = m[newid].second;
        }
        vector<int> v;
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
            v.push_back(s.top());
            s.pop();
        }
        return v;
    }
    vector<int> v2;
    return v2;
}