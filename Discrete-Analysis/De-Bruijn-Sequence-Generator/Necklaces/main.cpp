#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// The function returns the position of lexicographically minimal string rotation
int MinCyclicShift ( vector<int>::iterator beg, vector<int>::iterator end, int n ) {
    int nstr = end - beg;
    int i = 0;
    int ans = 0;
    while( i < n ) {
        ans = i;
        int j = i + 1;
        int k = i;
        while( j < 2 * n && *( beg + k % n % nstr ) >= *( beg + j % n % nstr ) ) {
            if( *( beg + k % n % nstr ) > *( beg + j % n % nstr ) ) {
                k = i;
            } else {
                ++k;
            }
            ++j;
        }
        while( i <= k ) {
            i += j - k;
        }
    }
    return ans;
}

// The function returns period of the string
int WordPeriod( const vector<int>& word, vector<int>& p )
{
    int n = word.size();
    for( int i = 1; i < n; ++i ) {
        int j = p[i - 1];
        while( j > 0 && word[i] != word[j] ) {
            j = p[j - 1];
        }
        if( word[i] == word[j] ) {
            ++j;
        }
        p[i] = j;
    }
    return n - p[n - 1];
}

void GetDeBruijnSequence( vector<vector<int>>& words, int n, int k )
{
    vector<int> p( n );
    vector<int> last( n, k - 1 );
    cout << 0 << ' ';
    while( last[0] != 0 ) {
        int j = n;
        while( last[j - 1] == 0 ) {
            --j;
        }

        int q = n / j;
        --last[j - 1];
        for( int i = 1; i < q; ++i ) {
            for( int h = 0; h < j; ++h ) {
                last[h + i * j] = last[h];
            }
        }
        for( int h = 0; h + q * j < n; ++h ) {
            last[h + q * j] = last[h];
        }

        if( MinCyclicShift( last.begin(), last.begin() + j, j + n % j ) == 0 ) {
            int d = WordPeriod( last, p );
            for( int i = 0; i < d; ++i ) {
                cout << k - 1 - last[i] << ' ';
            }
        }
    }
}

int main() {
    cout << "Enter n and k parameters:" << endl;
    int n, k;
    cin >> n >> k;

    size_t len = 1;
    for( int i = 0; i < n; ++i ) len *= k;
    cout << "The following De Bruijn sequence has a length of " << len << ":" << endl;

    vector<vector<int>> words;
    GetDeBruijnSequence( words, n, k );
    cout << endl;

    return 0;
}
