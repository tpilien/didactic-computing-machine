#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int x, y;
int A, B, C, D, E, F;
class Matrix {
    public:
    Matrix() {
        m[0][0] = 1;
        m[0][1] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
    }
    
    Matrix multiply(const Matrix &other) {
        Matrix newMat;
        newMat.m[0][0] = std::min((m[0][0]*other.m[0][0] + m[0][1]*other.m[1][0]), (unsigned long long) 1001);
        newMat.m[0][1] = std::min((m[0][0]*other.m[0][1] + m[0][1]*other.m[1][1]), (unsigned long long) 1001);
        newMat.m[1][0] = std::min((m[1][0]*other.m[0][0] + m[1][1]*other.m[1][0]), (unsigned long long) 1001);
        //set the max to 1001
        newMat.m[1][1] = std::min((m[1][0]*other.m[0][1] + m[1][1]*other.m[1][1]), (unsigned long long) 1001);
        return newMat;
    }
    
    unsigned long long m[2][2];
};

Matrix base;
Matrix start;
Matrix fib(unsigned long long N) {

    if (N == 0) {
        return start;
    }
    if (N == 1) {
        return base;
    }
    
    Matrix part = fib(N/2);
    Matrix ret = part.multiply(part);
    if (N % 2 == 1) {
        return ret.multiply(base);            
    }
    return ret;
    
}


std::vector<int> dist;

int binary_search(int lo, int hi, int x, bool usefib = false) {
    //std::cout << lo << " " << hi << std::endl;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool condition;
        if (!usefib) {
            condition = dist[mid] > x;
        } else {
            condition = fib(mid).multiply(start).m[1][1] > x;            
        }
        if (condition) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

int main() {

    std::string line;
    while (std::getline(std::cin, line)) {
  
        std::stringstream is(line);
        int Dist, J;
        is >> Dist >> J;

        dist.clear();
        int x;
        while (is >> x) {
            dist.push_back(x);
        }
        //we always have dist[0], so we can check if its going to fall
        if (J < dist[0]) {
            std::cout << "The spider is going to fall!" << std::endl;
            continue;
        }
        //no pattern            
        if (dist.size() == Dist + 1) {
            //Can jump when its at the water fall
            if (dist[Dist] <= J) {
                std::cout << "The spider may fall!" << std::endl;
            } else {
                //search for correct place
                int idx = binary_search(0, Dist + 1, J);
                std::cout << (Dist) - idx << std::endl;
            }
            
            
        } else {
            //pattern
            //magic formula :). Solves the linear eqns
            A = dist[0], B = dist[1], C = dist[2], D = dist[1], E = dist[2], F = dist[3];
            //if a*e - b*d = 0
            if (A * E != B * D) {
                x = (C*E - B*F) / (A*E - B*D);
                y = (A*F - C*D) / (A*E - B*D);
            } else {
                x = 1;
                y = 1;
            }                            
            
            base.m[0][0] = y; base.m[0][1] = x; base.m[1][0] = 1; base.m[1][1] = 0;

            start.m[0][0] = C; start.m[0][1] = B; start.m[1][0] = B; start.m[1][1] = A;

            int idx = binary_search(0, Dist + 1, J, true);
                                                        
            if (idx >= Dist) {
                std::cout << "The spider may fall!" << std::endl;
            } else {
                std::cout << (Dist) - idx << std::endl;
            }

        }
 
    }

}
