#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

vector<bool> Visited;

class DFA_Class {
public:
    DFA_Class(int _statesNum, int _alphabetNum, set<int>& _FinalStates, vector<vector<int>> _delta) :
        statesNum(_statesNum), alphabetNum(_alphabetNum), FinalStates(_FinalStates), delta(_delta) {
    };
    int statesNum;
    int alphabetNum;
    set<int> FinalStates;
    vector<vector<int>> delta;
};

void dfs(vector<vector<pair<string, int>>>& DFA, int Current) {

    //if (!DFS[Current].size())return Current;
    for (int i = 0; i < DFA[Current].size(); i++)
    {
        Visited[Current] = true;
        if (!Visited[DFA[Current][i].second]) {
            dfs(DFA, DFA[Current][i].second);
        }
    }
    //return -1;
}

int Del_dfs(vector<vector<int>>& delta, int Current) {
    Visited[Current] = true;
    if (!delta[Current].size())return Current;
    for (int i = 0; i < delta[Current].size(); i++)
    {
        if (!Visited[delta[Current][i]]) {
            Del_dfs(delta, delta[Current][i]);
        }
    }
    return -1;
}

bool Equivalent(DFA_Class& dfa, int i, int j, vector<int>& partition_0) {
    for (int z = 0; z < dfa.alphabetNum; z++) {
        int dest_i = dfa.delta[i][z];
        int dest_j = dfa.delta[j][z];
        if (dest_i > 0 && dest_j > 0) {
            if (partition_0[dest_i] != partition_0[dest_j]) return false;
        }

    }
    return true;
}

vector<int> Minimize(DFA_Class& dfa) {
    int statesNum = dfa.statesNum;

    vector<int> partition_0(statesNum, -1);
    for (int i : dfa.FinalStates) {
        partition_0[i] = 1;
    }

    while (true) {
        vector<int> partition(statesNum, -1);
        int i = 0;
        while (i < statesNum) {
            partition[i] = i;
            int i_next = statesNum;
            for (int j = i + 1; j < statesNum; j++) {
                if (partition[j] >= 0) continue;
                if (partition_0[i] == partition_0[j] && Equivalent(dfa, i, j, partition_0)) {
                    partition[j] = i;
                }
                else if (i_next == statesNum) {
                    i_next = j;
                }
            }
            i = i_next;
        }
        if (partition_0 == partition) break;
        partition_0 = partition;
    }

    return partition_0;
}


int main() {
    unordered_map<string, int> states;
    vector<char> alphabet;
    set<int> finalStateSet;
    vector<vector<pair<string, int>>> DFA;

    int statesNum, alphabetNum, finalStateNum, transitionsNum, totalStatesNum;

    cin >> statesNum;
    for (int i = 0; i < statesNum; i++) {
        string x;
        cin >> x;
        states[x] = i;
    }
    Visited.resize(statesNum, 0);
    cin >> alphabetNum;
    alphabet.resize(alphabetNum);
    for (int i = 0; i < alphabetNum; i++) {
        cin >> alphabet[i];
    }

    cin >> finalStateNum;
    for (int i = 0; i < finalStateNum; i++) {
        string x;
        cin >> x;
        finalStateSet.insert(states[x]);
    }

    cin >> transitionsNum;
    DFA.resize(statesNum);
    for (int i = 0; i < transitionsNum; i++) {
        string str;
        cin >> str;
        vector<string> v;
        stringstream ss(str);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }
        DFA[states[v[0]]].push_back({ v[1], states[v[2]] });
    }
    //int idx = -1;
    /*if (idx >= 0) {
        DFA.erase(DFA.begin() + idx);
    }*/
    totalStatesNum = statesNum;
    dfs(DFA, 0);
    for (int i = 0; i < Visited.size(); i++)
    {
        if (!Visited[i]) {
            for (int h = 0; h < alphabetNum; h++) {
                DFA[i][h] = { {alphabet[h]}, -1 };
            }
            /*for (int k = i + 1; k < statesNum; k++)
            {
                for (int m = 0; m < DFA[k].size(); m++)
                {
                    if (DFA[k][m].second > i)DFA[k][m].second--;
                }
            }*/


            /*auto it = finalStateSet.find(i);
            if (it != finalStateSet.end()) {
                finalStateSet.erase(it, finalStateSet.end());
            }*/
            totalStatesNum--;

        }
    }
    Visited.assign(statesNum, 0);

    vector<vector<int>> delta(statesNum, vector<int>(alphabetNum, -1));
    for (int i = 0; i < statesNum; i++) {
        for (auto& transition : DFA[i]) {
            int inputIndex = find(alphabet.begin(), alphabet.end(), transition.first[0]) - alphabet.begin();
            delta[i][inputIndex] = transition.second;
        }
    }
    /*int idx2 = 0;
    for (int i = 0; i < statesNum; i++)
    {
        if (!Visited[i]) {
            idx2 = Del_dfs(delta, i);
        }
    }
    if (idx2 >= 0) {
        delta.erase(delta.begin() + idx2);
    }*/
    DFA_Class dfa(statesNum, alphabetNum, finalStateSet, delta);
    auto minimizedPartitions = Minimize(dfa);



    cout << unordered_set<int>{minimizedPartitions.begin(), minimizedPartitions.end()}.size();

    return 0;
}

