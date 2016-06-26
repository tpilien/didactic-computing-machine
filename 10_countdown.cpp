#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct opPair{
  opPair(int u, int v, int w, int o) : a(u), b(v), res(w), op(o) {}
  int a;
  int b;
  int res;
  int op;
};


/*struct nextOp {
  std::vector<opPir> ops;
  std::vector<int> nums;
  int dist;
};*/

vector<opPair> bestOps;
vector<opPair> ops;

//priorityqueue<state> pq;(vector<, )

int closest;
int target;
bool found = false;

void recurse(std::vector<int> &nums){
 // std::cout << nums.size() << std::endl;
  if(found) return;
  
  if (nums.size() == 1){
    if (abs(nums[0] - target) < abs(closest - target)){
      closest = nums[0];
      bestOps = ops;
    }
    return;
  }
  
  vector<int> copy (nums.begin(), nums.end());
  
  for(unsigned int i = 0; i < nums.size(); i++){
    if(nums[i] == target){
      closest = nums[i]; 
      found = true;
      bestOps = ops;
      break;
    }
    copy.erase(copy.begin() + i);
    for(unsigned int j = 0; j < nums.size(); j++){
      if(i != j){
        if(j < i){
          copy.erase(copy.begin() + j);
        } else {
          copy.erase(copy.begin() + j - 1); 
        }
        int res;
        
        if(nums[i] <= nums[j]){
          res = nums[i] + nums[j];
          copy.push_back(res);
          ops.push_back(opPair(nums[i], nums[j], res, 0));
          recurse(copy); //+ op
          ops.pop_back();
          copy.pop_back();
        }
      
        res = nums[i] - nums[j];
        if(res > 0){
          copy.push_back(res); //- op
          ops.push_back(opPair(nums[i], nums[j], res, 1) );
          recurse(copy);
          copy.pop_back();
          ops.pop_back();
        }
        
        //only mult / div if not an identity operation
        if(nums[i] != 1 && nums[j] != 1){
          if(nums[i] <= nums[j]){
        
            res = nums[i] * nums[j];
            copy.push_back(res); // * op
            ops.push_back(opPair(nums[i], nums[j], res, 2));        
            recurse(copy);
            ops.pop_back();
            copy.pop_back();
          }
          if(nums[j] != 0 && nums[i] % nums[j] == 0){
            res = nums[i] / nums[j];
            copy.push_back(res); //div op
            ops.push_back(opPair(nums[i], nums[j], res, 3));
            recurse(copy);
            ops.pop_back();
            copy.pop_back();
          }
        }
        
        if(j < i){
          copy.insert(copy.begin() + j, nums[j]);
        } else {
          copy.insert(copy.begin() + j - 1, nums[j]);
        }
      
      }
    }
    copy.insert(copy.begin() + i, nums[i]);
  }
  return;
}


int main(){
  int cases;
  cin >> cases;
  vector<int> allnums(6);
  for(int c = 0; c < cases; c++){
    for(int i = 0; i < 6; i++){
      cin >> allnums[i];
    }
    sort(allnums.rbegin(), allnums.rend());
    
    cin >> target;
    recurse(allnums);
    
    
    
    
    
    
    
    
    
    
    
    
    cout << "Target: " << target << endl;
    for(opPair o : bestOps){
      cout << o.a;
      if(o.op == 0){
        cout << " + ";
      } else if (o.op == 1){
        cout << " - ";
      } else if (o.op == 2){
        cout << " * ";
      } else {
        cout << " / ";
      }
      cout << o.b << " = " << o.res << endl;
      
    }
    cout << "Best approx: " << closest << endl << endl;
    closest = 0;
    found = false;
  }
  return 0;
}

