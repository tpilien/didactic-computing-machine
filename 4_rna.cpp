#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


int main() {
  int cases;
  cin >> cases;
  while(cases--){
    string curr;
    cin >> curr;
    stringstream ss;
    ss << curr;
    char c; 
    int times;
    vector<char> str;
    while(ss >> c && ss >> times){
      while(times--){
        str.push_back(c);
      }
    }
    vector<vector<int> > cache;
    vector<vector<int> > bigR;
    cache.resize(str.size()+1);
    bigR.resize(str.size()+1);
    
    cout << "  ";
    for(char c : str){
      cout << c << " ";
    }
    cout << endl;
    
    for(unsigned i = 0; i < str.size()+1; i++){
      cache[i].resize(str.size() + 1);
      bigR[i].resize(str.size() + 1);
    }

    int size = (int) str.size();    
    for (int i = 0; i < size; i++){
      for (int j = size - 1; j >= i; j--){
        if ((str[i] == 'A' && str[j] == 'U') || (str[i] == 'C' && str[j] == 'G') || (str[i] == 'U' && str[j] == 'A') || (str[i] == 'G' && str[j] == 'C') ){
          cache[i][j] = 1;          
        }
        
        if (i > 0){
          cache[i][j] += bigR[i-1][j+1];
          bigR[i][j] = max(max(bigR[i-1][j], bigR[i][j+1]), cache[i][j]);
        } else {
          if(cache[i][j] > bigR[i][j+1]){
            bigR[i][j] = cache[i][j];
          } else {
            bigR[i][j] = bigR[i][j+1];
          }
        }
       
      }
    }
    
    for(unsigned int i = 0; i < str.size(); i++){
      cout << str[i] << " ";
      for(unsigned int j = 0; j < str.size(); j++){
        cout << cache[i][j] << " ";
      }
      cout << endl;
    }
    cout << "BIG R: " << endl;
    for(unsigned int i = 0; i < str.size()+1; i++){
      for(unsigned int j = 0; j < str.size()+1; j++){
        cout << bigR[i][j] << " ";
      }
      cout << endl;
    }
    
    
    
  }
  return 0;
}
