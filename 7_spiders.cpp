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
        newMat.m[0][0] = (m[0][0]*other.m[0][0] + m[0][1]*other.m[1][0]);
        newMat.m[0][1] = (m[0][0]*other.m[0][1] + m[0][1]*other.m[1][1]);
        newMat.m[1][0] = (m[1][0]*other.m[0][0] + m[1][1]*other.m[1][0]);
        newMat.m[1][1] = (m[1][0]*other.m[0][1] + m[1][1]*other.m[1][1]);
        return newMat;
    }
    
    unsigned long long m[2][2];
};

Matrix base;
Matrix fib(unsigned long long N) {

    if (N == 1) {
        return base;
    }
    
    Matrix part = fib(N/2);
    Matrix ret = part.multiply(part);
    if (N % 2 == 1) {
        return ret.multiply(Matrix());            
    }
    return ret;
    
}


std::vector<int> dist;

int binary_search(int lo, int hi, int x, bool pat = false) {
    //std::cout << lo << " " << hi << std::endl;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool condition;
        if (!pat) {
            condition = dist[mid] > x;
        } else {

//            std::cout << mid << " " << fib(mid).m[0][0] << " " << x << std::endl;
            condition = fib(mid).m[0][0] > x;
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
//    std::cout << fib(5).m[0][0] << std::endl;
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
        if (J < dist[0]) {
            std::cout << "The spider is going to fall!" << std::endl;
            continue;
        }
        if (dist.size() == Dist + 1) {

            //no pattern            
            if (dist[Dist] <= J) {
                std::cout << "The spider may fall!" << std::endl;
                continue;
            }
            int idx = binary_search(0, Dist + 1, J);
            std::cout << (Dist) - idx << std::endl;
            continue;
            
        } else {
            //pattern
            //magic formula :). Solves the linear eqns
            A = dist[0], B = dist[1], C = dist[2], D = dist[1], E = dist[2], F = dist[3];
            x = (C*E - B*F) / (A*E - B*D);
            y = (A*F - C*D) / (A*E - B*D);

            base.m[0][0] = y; base.m[0][1] = 1; base.m[1][0] = x; base.m[1][1] = 0;
            Matrix start;
            start.m[0][0] = C; start.m[0][1] = B; start.m[1][0] = B; start.m[1][1] = A;

            int idx = binary_search(0, Dist + 1, J, true);

            
            
            
            continue;                       
            

        }
        line = "";
        std::cout << std::endl;
    }

}
