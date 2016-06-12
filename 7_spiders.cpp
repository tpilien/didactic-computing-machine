#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int Dist, J;
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
        //set the max to 1001 (since jump distance is max 1000)
        //prevent overflows
        newMat.m[0][0] = std::min((m[0][0]*other.m[0][0] + m[0][1]*other.m[1][0]), (unsigned long long) 1001);
        newMat.m[0][1] = std::min((m[0][0]*other.m[0][1] + m[0][1]*other.m[1][1]), (unsigned long long) 1001);
        newMat.m[1][0] = std::min((m[1][0]*other.m[0][0] + m[1][1]*other.m[1][0]), (unsigned long long) 1001);        
        newMat.m[1][1] = std::min((m[1][0]*other.m[0][1] + m[1][1]*other.m[1][1]), (unsigned long long) 1001);
        return newMat;
    }
    
    unsigned long long m[2][2];
};

Matrix exp;
Matrix base;

//fast exponentiation for fibonacci
Matrix fib(unsigned long long N) {
    
    if (N == 0) {
        return base;        
    }
    if (N == 1) {
        return exp;
    }
    
    Matrix part = fib(N/2);
    Matrix ret = part.multiply(part);
    if (N % 2 == 1) {
        return ret.multiply(exp);            
    }
    return ret;
    
}


std::vector<int> dist;

int binary_search(int lo, int hi, int x) {
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool condition;
        //if we have a value for the distance at position mid
        if (mid < dist.size()) {
            condition = dist[mid] > x;
        } else {
            //else calculate a value
            condition = fib(mid).multiply(base).m[1][1] > x;            
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

        is >> Dist >> J;

        dist.clear();
        int x;
        //read in distances
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
                        
            A = dist[0], B = dist[1], C = dist[2], D = dist[3];
            //if a*e - b*d = 0
            if (A * C != B * B) {
                //magic formula :). Solves the 2 linear eqns. 
                //Ax + By = C, Bx + Cy = D
                x = (C*C - B*D) / (A*C - B*B);
                y = (A*D - C*B) / (A*C - B*B);
            } else {
                //otherwise we set x and y to 1
                x = 1;
                y = 1;
            }                            
            //the matrix used for fast exponentiation
            exp.m[0][0] = y; exp.m[0][1] = x; exp.m[1][0] = 1; exp.m[1][1] = 0;
 
            //the base case
            base.m[0][0] = C; base.m[0][1] = B; base.m[1][0] = B; base.m[1][1] = A;

            int idx = binary_search(0, Dist + 1, J);
                                                        
            if (idx >= Dist) {
                std::cout << "The spider may fall!" << std::endl;
            } else {
                std::cout << (Dist) - idx << std::endl;
            }

        }
 
    }

}
