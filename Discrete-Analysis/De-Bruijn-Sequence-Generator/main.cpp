#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// This function generates De Bruijn sequence by the rule "0 is better than 1"
void EulerCycle( int v, int k, const vector<vector<int>>& g, vector<int>& edge )
{
    while( edge[v] != k ) {
        v = g[v][edge[v]++];
        cout << v % k << ' ';
    }
}

int main() {
    int n, k;

    cout << "Enter n and k parameters split by space or end of line:" << endl;
    cin >> n >> k;

    if( n == 1 ) {
        for( int i = 0; i < k; ++i ) {
            cout << i << ' ';
        }
        cout << endl;
        return 0;
    }

    int v = 1;
    for( int i = 0; i < n - 1; ++i ) {
        if( static_cast<long long>( v ) * k > 1e9 ) {
            cout << "Too big sequence" << endl;
            return 0;
        }
        v *= k;
    }

    vector<vector<int>> g( v, vector<int>( k ) );
    vector<int> edge( v, 0 );

    int delim = v / k;
    for( int i = 0; i < v; ++i ) {
        int succ_mask = ( i - i / delim * delim ) * k;
        for( int j = 0; j < k; ++j ) {
            g[i][j] = succ_mask++;
        }
    }

    cout << "The following De Brujin sequence has a size of " << v * k << ":\n";
    EulerCycle( v - 1, k, g, edge );
    cout << endl;

    return 0;
}
