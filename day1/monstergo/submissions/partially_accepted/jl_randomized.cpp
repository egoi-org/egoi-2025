// A randomized approach to MonsterGO based on the observation that if you have two lists A and B, for each element x
// in the intersection, you also need a list that is a subset of (A \cup B) \ {x} 

#include <bits/stdc++.h>

using namespace std;

const int MONS = 46;
const int BING = 12;
const int MAXN = 50;
const int PRINT_const = 500;

int main() {
  int N; cin >> N;
  vector<int> solve_count(MAXN+1);
  vector<pair < int, vector<vector<int> > > > blocks; // num of used monsters, lists of monsters
  for(int its = 0; its < 1500; its++){
    // generate blocks: we start out with two lists a and b and then continue to add lists based on the observation
    vector<int> a(BING);
    iota(a.begin(), a.end(), 0);
    int overlap = rand() % BING;
    vector<int> b = a;
    iota(b.begin() + overlap, b.end(), BING + 1);

    vector<vector<int> > res = {a, b};
    while(res.size() <= MAXN){
      vector<vector<int> > new_res = res;
      for(int i = 0; i < res.size() && new_res.size() <= MAXN; i++){
        for(int j = 0; j < res.size() && new_res.size() <= MAXN; j++){
          if (i == j) continue; 
          vector<int> union_list;
          set_union(res[i].begin(), res[i].end(), res[j].begin(), res[j].end(), back_inserter(union_list));


          vector<int> intersec_list;
          set_intersection(res[i].begin(),res[i].end(), res[j].begin(),res[j].end(), back_inserter(intersec_list));

          vector<int> base_ext;
          set_difference(union_list.begin(), union_list.end(), intersec_list.begin(), intersec_list.end(), back_inserter(base_ext));


          if(base_ext.size() >= BING ){
            int found = false;
            for(int k = 0; k < new_res.size(); k++){             
                if (includes(base_ext.begin(), base_ext.end(), new_res[k].begin(), new_res[k].end())){
                  found = true;
                  break;
                }
             }

            if(found) continue;
            random_shuffle(base_ext.begin(), base_ext.end());
            vector<int> new_list(base_ext.begin(), base_ext.begin() + BING);
            sort(new_list.begin(), new_list.end());
            new_res.push_back(new_list);
            continue;
          }

          for(int x : intersec_list){
             bool found = false;
             vector<int> union_list2 = union_list;
             union_list2.erase(std::remove(union_list2.begin(), union_list2.end(), x), union_list2.end());
             for(int k = 0; k < new_res.size(); k++){             
                if (includes(union_list2.begin(), union_list2.end(), new_res[k].begin(), new_res[k].end())){
                  found = true;
                  break;
                }
             }

             if(found) continue;
             vector<int> intersec_list2 = intersec_list;
             intersec_list2.erase(std::remove(intersec_list2.begin(), intersec_list2.end(), x), intersec_list2.end());
             random_shuffle(intersec_list2.begin(), intersec_list2.end());
             vector<int> new_list = base_ext;
             new_list.insert(new_list.end(), intersec_list2.begin(), intersec_list2.begin() + BING - base_ext.size());
             sort(new_list.begin(), new_list.end());
             new_res.push_back(new_list);
          }
        }
      }
      if(res == new_res) break;
      res = new_res;
    }

    
    if(res.size() > MAXN) continue;
    
    solve_count[res.size()]++;

    if(solve_count[res.size()] == 1){
      blocks.push_back({2 * BING - overlap, res});
    }
  }

  blocks.push_back({0, {}});
  vector<int> trivial(BING);
  iota(trivial.begin(), trivial.end(), 0);
  blocks.push_back({BING, {trivial}});

  // we combine at most 3 blocks to get N lists
   for(int i = 0; i < blocks.size(); i++){
      for(int j = 0; j < blocks.size(); j++){
        for(int k = 0; k < blocks.size(); k++){
           if(blocks[i].first + blocks[j].first + blocks[k].first > MONS) continue;
           if(blocks[i].second.size() + blocks[j].second.size() + blocks[k].second.size() != N) continue;
           for(int a = 0; a < blocks[i].second.size(); a++){
             for(int b = 0; b < BING; b++){
               cout << blocks[i].second[a][b] << " ";
              }
              cout << endl;
            }

            for(int a = 0; a < blocks[j].second.size(); a++){
              for(int b = 0; b < BING; b++){
                cout << blocks[j].second[a][b] + blocks[i].first << " ";
              }
              cout << endl;
            }

            for(int a = 0; a < blocks[k].second.size(); a++){
              for(int b = 0; b < BING; b++){
                cout << blocks[k].second[a][b] + blocks[i].first + blocks[j].first << " ";
              }
              cout << endl;
            }
           return 0;
        }
      }
    }

  return 0;
}
