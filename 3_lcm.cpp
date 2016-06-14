#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define LIMIT 1000000007

vector<map<int, int>> factors;
map<int, int> primes; 
set<map<int, int>> factor_set;

long long int powpow (long long int x, long long int k) {
  if (k == 0)
    return 1;
  
  long long int a = powpow(x, k/2);
  a = a*a;
  
  if (k%2 == 1)
    a = a*x;
  
  return a;
}

void find_factors(int i, map<int, int> current) {
  if (i != -1) {
    if (current[i] + 1 > primes[i]) {
      return;
    }
  
    current[i]++;
    if (factor_set.find(current) != factor_set.end()) {
      return;
    }
  } else {
    // initialise current
    for (const auto &it : primes) {
      current[it.first] = 0;
    } 
  }
  
  factors.push_back(current);
  factor_set.insert(current);
  for (const auto &prime : primes) {
    find_factors(prime.first, current);
  }
}

int main() {
  unsigned int tt = 0;
  cin >> tt;

  for (unsigned int z = 1; z <= tt; ++z) {
    unsigned int cc = 0;
    cin >> cc;
   
    // clear variables for use
    factor_set.clear();
    factors.clear();
    primes.clear();
   
    for (unsigned int i = 0; i < cc; ++i) {
      unsigned int pp, a;
      cin >> pp >> a;
      
      primes[pp] = a;
    }
    
    map<int, int> current;   
    // generate factors
    find_factors(-1, current);
    
    // compare lcms and add
    long long int total = 0;
    for (unsigned int i = 0; i < factors.size(); ++i) {
      for (unsigned int j = i; j < factors.size(); ++j) {        
        bool lcm = true;
        
        for (const auto &it : primes) {
          if (max(factors[i][it.first], factors[j][it.first]) != primes[it.first]) {
            lcm = false;
            break;
          }
        }
                
        if (lcm) {
          long long int total_i = 1, total_j = 1;
          for (const auto &it : primes) {
            total_i *= powpow(it.first, factors[i][it.first]) % LIMIT;
            total_j *= powpow(it.first, factors[j][it.first]) % LIMIT;
          }
          total += (total_i + total_j % LIMIT);
        }
      }
    }
    
    cout << "Case " << z << ": " << total << endl;
  }

  return 0;
}
