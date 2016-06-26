#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#define INF 1e9

int start[100], next[10000], to[10000], m;

int add(int u, int v) {
    to[m] = v;
    next[m] = start[u];
    start[u] = m++;
}

struct Place {
    float x;
    float y;
    int satis;
    std::string id;
};

std::map<std::string, int> nameToNum;
Place places[100];
float dist[65][65];

struct State {
    
    float time;
    int satis;
    
    unsigned long long visited;
    std::vector<short> path;
    short pathlength;
    short place;
};


inline float d(int u, int v) {
    return sqrt((places[u].x - places[v].x) * (places[u].x - places[v].x) + (places[u].y - places[v].y) * (places[u].y - places[v].y));
}

float targetS;
int targetP;


inline bool cmp(float x, float y) {
    return fabs(x - y) < 0.1;
}

bool operator<(const State& a, const State& b) {
    return fabs((a.satis - (a.time) - dist[a.place][targetP]) - targetS) > fabs((b.satis - (b.time) - dist[b.place][targetP]) - targetS);
}


//Need to find a path that has satisfaction difference of less than 0.1
bool path(int src, int dest, float target_satisfaction, float time) {
    //to increase satisfaction we must wait at a place for 15 mins
    //as we travel, we lose satisfaction

    targetS = target_satisfaction;
    targetP = dest;
    std::priority_queue<State> pq;
    State nextS, nextS2, curr;
    nextS.path = std::vector<short>(64, 0);
    nextS.pathlength = 0;
    nextS.satis = 0;
    nextS.time = 0;
    nextS.place = src;
    nextS.visited = 0;
    
    nextS2 = nextS;    
    nextS.path[nextS.pathlength++] = src;
    
    
    pq.push(nextS);            

    nextS2.path[nextS2.pathlength++] = (src + 65);
    //not walking for 15 mins
    nextS2.time += 15;
    nextS2.satis += (places[src].satis) + 15;
    pq.push(nextS2);            
    
    
    int e, v;
    
    while (!pq.empty()) {
        
        curr = pq.top(); pq.pop();
        if (curr.time + dist[curr.place][dest] > time) continue;

        curr.visited = curr.visited | (1 << curr.place);

        if ((curr.place == dest)) {
            std::cout << pq.size() << std::endl;
            if (fabs(targetS - (curr.satis - (curr.time))) < 0.1) {
                std::vector<short> p = curr.path;                       
                printf("PATH FOUND: %0.3f ", curr.satis - curr.time);            
                for (int i = 0; i < curr.pathlength - 1; ++i) {
                    if (p[i] >= 65) {
                        printf("%s ", places[p[i] - 65].id.c_str());
                    } else {                    
                        printf("!%s ", places[p[i]].id.c_str());
                    }                    
                }
                printf("%s\n", places[dest].id.c_str());
                
                return true;
            }
            continue;
        }
        for (e = start[curr.place]; ~e; e = next[e]) {
            v = to[e];    
            if ((curr.visited & (1 << v))) continue;
//            if (curr.time + dist[curr.place][v] * 15 + dist[v][dest] > time) continue;
            nextS = curr;            
            nextS.time += dist[curr.place][v] * 15;
                        
            nextS.place = v;
            nextS2 = nextS;
            nextS.path[nextS.pathlength++] = (v);
            if (v == dest) continue;
            pq.push(nextS);
//            nextS2.time += 15;
            nextS2.path[nextS2.pathlength++] = (v + 65);
            //not walking for 15 mins
            nextS2.satis += (places[v].satis) + 15;
            pq.push(nextS2);            

        }
        
    }
    printf("Impossible!\n");
    return false;

}




int main() {
    std::string tmp;
    int P, M;
    std::string line;
    int caseNum = 1;    
    std::cin >> tmp;
    while (std::cin >> P >> M) {
        nameToNum.clear();
        memset(start, -1, sizeof(start));
        memset(next, 0, sizeof(next));
        memset(to, 0, sizeof(to));
        m = 0;
        //places = <Place>(200);
        //initialise distance matrix
        for (int i = 0; i < 65; ++i)
            for (int j = 0; j < 65; ++j)
                dist[i][j] = INF;
        //nodes
        getline(std::cin, line);
        for (int i = 0; i < P; ++i) {
            getline(std::cin, line);
            std::stringstream ss(line);
            float x, y;
            int satis;
            std::string id;
            ss >> x >> y >> satis >> id;
            nameToNum[id] = i;
            
            Place p = {x, y, satis, id};
            places[i] = p;
        }
        std::string start, end;
        int u, v;
        //edges
        for (int i = 0; i < M; ++i) {

            std::cin >> start >> end;
            u = nameToNum[start];
            v = nameToNum[end];
            add(u, v);
            //add(u+65, v);            
            add(v, u);
            //add(v+65, u);
            float x = d(u, v);
            dist[u][v] = x;
            //dist[u+65][v] = x;
            dist[v][u] = x;
            //dist[v+65][u] = x;
        }
        int n = 65;
        for (int i = 0; i < n; i++)
            for (int u = 0; u < n; u ++)
                for (int v = 0; v < n; v ++)
                    dist [u][v] = std::min ( dist [u][v] , dist [u][i]+ dist [i][v]) ;
        //read arrivals
        std::cin >> tmp;

        std::string startTime, endTime, startPlace, endPlace;
        printf("MAP %d\n", caseNum++);
        while (std::cin >> startTime) {
            //end of cases
            if (startTime == "MAP") break;
            float target;
            std::cin >> startPlace >> endTime >> endPlace >> target;
            
            int startH, startM, endH, endM;
            
            std::stringstream ss(startTime);
            std::stringstream ss2(endTime);            
            std::getline(ss, line, ':');
            startH = stoi(line);           
            std::getline(ss, line);
            startM = stoi(line);           
            std::getline(ss2, line, ':');
            endH = stoi(line);
            std::getline(ss2, line);
            endM = stoi(line);
            
            float minutes = ((24 + endH - startH) % 24) * 60 + (endM - startM);             
            
//            std::cout << minutes << std::endl;
//            continue;
            path(nameToNum[startPlace], nameToNum[endPlace], target, minutes);

        }
        
    }

}
