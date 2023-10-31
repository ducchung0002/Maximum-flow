#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int&& inf = 32767;
void Init(vector<vector<int>>& weight, int& phat, int& thu) {
    fstream input_stream("input.txt", ios::in);
    int v, e;
    int begin, end;
    input_stream >> v >> e >> phat >> thu;
    --thu; --phat;
    weight = vector<vector<int>>(v, vector<int>(v));
    for (int i = 1; i <= e; i++) {
        input_stream >> begin >> end;
        input_stream >> weight[begin - 1][end - 1];
    }
};
void Ford_Fulkerson(const int& th, const vector<vector<int>>& weight, vector<vector<int>>& flow, vector<int>& label, vector<bool>& visited, vector<int>& path, const int& thu) {
    for (int i = 0; i < weight.size(); ++i) { // thuc hien gan nhan cac dinh ke dinh th
        if (weight[th][i] != 0 && weight[th][i] - flow[th][i] > 0 && visited[i] != 1) // cung th-i la cung thuan chua bao hoa
        {
            label[i] = min(label[th], weight[th][i] - flow[th][i]);
            path.push_back(i);
            visited[i] = 1;
            if (i == thu) { // diem thu duoc gan nhan
                // thuc hien tang luong
                for (int j = 0; j < path.size() - 1; ++j)
                {
                    if (weight[path[j]][path[j + 1]] != 0) // cung thuan
                        flow[path[j]][path[j + 1]] += label[thu];
                    else if (weight[path[j + 1]][path[j]] != 0) // cung nghich
                        flow[path[j + 1]][path[j]] -= label[thu];
                    label[path[j + 1]] -= label[thu];
                }
                visited[i] = 0;
                path.pop_back();
                continue;
            }
            Ford_Fulkerson(i, weight, flow, label, visited, path, thu);
            path.pop_back();
            visited[i] = 0;
        }
        if (weight[i][th] != 0 && flow[i][th] > 0 && visited[i] != 1) // cung th-i la cung nghich
        {
            label[i] = min(label[th], flow[i][th]);
            visited[i] = 1;
            path.push_back(i);
            Ford_Fulkerson(i, weight, flow, label, visited, path, thu);
            path.pop_back();
            visited[i] = 0;
        }
    }
};
int main() {
    cout << "Maximum Flow" << endl;
    vector<vector<int>> weight;
    int thu, phat;
    Init(weight, phat, thu);
    vector<int> label(weight.size());
    vector<bool> visited(weight.size());
    vector<vector<int>> flow(weight.size(), vector<int>(weight.size()));

    label[phat] = inf;
    visited[phat] = 1;
    vector<int> path{ phat };

    Ford_Fulkerson(phat, weight, flow, label, visited, path, thu);

    for (int i = 0; i < weight.size(); i++)
        for (int j = 0; j < weight.size(); j++)
            if (flow[i][j] != 0)
                cout << i + 1 << ' ' << j + 1 << ' ' << flow[i][j] << endl;
    return 0;
};