#include <iostream>
#include <string>
using namespace std;

int main() {
  unsigned int cc = 0;
  cin >> cc;

  for (unsigned int z = 1; z <= cc; ++z) {
    string ss, tt;
    cin >> ss >> tt;
    
    unsigned int ones = 0;
    unsigned int zeros = 0;
    
    unsigned int edit_ones = 0;
    unsigned int edit_zeros = 0;
    // find the amount of ones and zeros in the completed string
    // find the amount of ones and zeros in non-completed string
    for (unsigned int i = 0; i < tt.size(); ++i) {
      if (tt[i] == '0') {
        zeros++;
      } else if (tt[i] == '1') {
        ones++;
      }
      
      if (ss[i] == '0') {
        edit_zeros++;
      } else if (ss[i] == '1') {
        edit_ones++;
      }
    }
    
    // greedily place 1s in the old string
    unsigned int edits = 0;
    for (unsigned int i = 0; i < ss.size(); ++i) {
      if (ss[i] == '?' && tt[i] == '1' && edit_ones < ones) {
        edits++;
        edit_ones++;
        ss[i] = '1';
      } else if (ss[i] == '?' && tt[i] == '1' && edit_ones == ones) {
        edits++;
        edit_zeros++;
        ss[i] = '0';
      }
    }
    
    // now place 0s in the old string
    for (unsigned int i = 0; i < ss.size(); ++i) {
      if (ss[i] == '?' && tt[i] == '0' && edit_zeros < zeros) {
        edits++;
        edit_zeros++;
        ss[i] = '0';
      } else if (ss[i] == '?' && tt[i] == '0' && edit_zeros >= zeros) {
        edits++;
        edit_ones++;
        ss[i] = '1';
      }
    }
    
    // find the amount of misplaced tiles
    unsigned int misplaced_zero = 0;
    unsigned int misplaced_one = 0;
    for (unsigned int i = 0; i < ss.size(); ++i) {
      if (ss[i] == '0' && tt[i] == '1' && edit_ones < ones && edit_zeros != zeros) {
        edits++;
        edit_zeros--;
        edit_ones++;
        ss[i] = '1';
      }

      if (ss[i] != tt[i] && ss[i] == '0') {
        misplaced_zero++;
      } else if (ss[i] != tt[i] && ss[i] == '1') {
        misplaced_one++;
      } else if (ss[i] == '?') {
        misplaced_zero = 1;
        misplaced_one = 2;
        break;
      }
    }
    
    if (zeros != edit_zeros || ones != edit_ones || misplaced_one != misplaced_zero) {
      cout << "Case " << z << ": -1" << endl;
    } else {
      cout << "Case " << z << ": " << edits + (misplaced_one) << endl;
    }
  }

  return 0;
}
