#include <bits/stdc++.h>

int start[5000], to[10000], next[10000], cap[10000], seen[10000], m;

int add(int u, int v, int c = 1) {
    to[m] = v;
    cap[m] = c;
    next[m] = start[u];
    start[u] = m++;

    to[m] = u;
    cap[m] = 0;
    next[m] = start[v];
    start[v] = m++;
}

int inv ( int e) {
    return e ^1;
}
bool augment ( int u, int t, int f) {
    if (u == t)
        return true ;
    if ( seen [u])
        return false ;
    seen [u] = true ;
    for (int e = start [u]; ~e; e = next [e])
        if ( cap [e] >= f && augment (to[e] , t, f) ) {
            cap [e] -= f;
            cap [ inv (e) ] += f;
            return true ;
        }
    return false ;
}
int max_flow ( int s, int t) {
    int res = 0;
    memset (seen , 0, sizeof seen );
    while ( augment (s, t, 1) ) {
        memset (seen , 0, sizeof seen );
        res += 1;
    }
    return res ;
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        memset(start, -1, sizeof(start));
        m = 0;
        int X, Y;
        std::cin >> X >> Y;
        int P, W;
        std::cin >> P;
        int a, b;
        std::vector<std::vector<char> > grid = std::vector<std::vector<char> >(X, std::vector<char>(Y, '.'));
        for (int i = 0; i < P; ++i) {
            std::cin >> a >> b;
            grid[a-1][b-1] = '*';
        }

        std::cin >> W;
        for (int i = 0; i < W; ++i) {
            std::cin >> a >> b;
            grid[a-1][b-1] = '#';
        }
        
        //mark all the horizontal lines
        int horiz = 0;
        int line[100][100];       
        int vline[100][100];       
        memset(line, 0, sizeof(line));        
        memset(vline, 0, sizeof(vline));
        for (int i = 0; i < X; ++i) {
            bool online = false;
            for (int j = 0; j < Y; ++j) {
                if (grid[i][j] == '*') {
                    
                    if (!online) {
                        ++horiz;
                        online = true;
                    }
                    online = true;
                    line[i][j] = horiz;
                } else if (grid[i][j] == '#') {
                    online = false;
                } else if (online) {
                    //line[X][Y] = horiz;
                }
            }
        }
//        std::cout << horiz << std::endl;
    
        int vert = 0;
 
        //mark all vertical lines
        for (int j = 0; j < Y; ++j) {

            bool online = false;
            for (int i = 0; i < X; ++i) {            
                if (grid[i][j] == '*') {
                    if (!online) {
                        ++vert;
                        online = true;
                    }
                    vline[i][j] = vert;
                } else if (grid[i][j] == '#') {
                    online = false;
                } else if (online) {
                    //vline[X][Y] = vert;
                }

            }
        }
//        std::cout << vert << std::endl;

        //connected up a flow network
        int src = 1000;
        int sink = 1001;
        for (int i = 1; i <= horiz; ++i) {
            add(src, i, 1);
            //add(i, src, 0);
        }
        for (int i = 1; i <= vert; ++i) {
            add(i + horiz, sink, 1);
            //add(sink, i + horiz, 0);
        }

        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                if (line[i][j] && vline[i][j])          
                //std::cout << line[i][j] << std::endl;
                add(line[i][j], vline[i][j] + horiz, 1);
                //add(vline[i][j] + horiz, line[i][j], 0);      
            }
        }
 //       std::cout << m << std::endl;
 //       std::cout << "HERE" << std::endl << std::flush;
        std::cout << max_flow(src, sink) << std::endl;   
    }

    return 0;
}
