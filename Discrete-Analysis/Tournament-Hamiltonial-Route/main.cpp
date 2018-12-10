#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>

using namespace std;

typedef chrono::high_resolution_clock my_clock;

int has( const vector<int>& successors, int dir, const vector<bool>& inPath );
void input_graph( vector<vector<int>>& graph );
void generate_graph( vector<vector<int>>& graph, mt19937& random_generator );
bool check_tournament( const vector<vector<int>>& graph );
void solve( int n, mt19937& random_generator );

int main() {
    ios_base::sync_with_stdio( false );
    cin.tie( nullptr );
    cout.tie( nullptr );

    mt19937 random_generator;

    cout << "Enter the number of vertices in tournament graph n:" << endl;
    int n;
    cin >> n;

    int t = 1;
    for( int i = 0; i < t; ++i ) {
        solve( n, random_generator );
    }

    return 0;
}

// Данная функция решает задачу
void solve( int n, mt19937& random_generator )
{
    // Инициализация генератора рандомных чисел
    random_generator.seed( my_clock::now().time_since_epoch().count() );

    vector<vector<int>> graph( n, vector<int>( n ) );

    // Инициализация матрицы смежности случайными значениями
    // generate_graph( graph, random_generator );

    // Возможен ввод матрицы вручную
    input_graph( graph );

    if( !check_tournament( graph ) ) {
        cout << "Graph is not a tournament" << endl;
        return;
    }

    // Следующие несколько строк выводят матрицу смежности турнира
    cout << "Tournament matrix:" << endl;
    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < n; ++j ) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    // Инициализация данных для нахождения гамильтонова пути
    list<int> path;         // path содержить текущий путь, который в конце станет гамильтоновым
    path.push_back( 0 );    // В начале добавляем туда нулевую вершину
    vector<bool> inPath( n, false );
    int v = 0;
    inPath[0] = true;
    int pos;

    // Пока из последней вершины есть исходящее ребро
    while( ( pos = has( graph[v], 1, inPath ) ) != -1 ) {
        path.push_back( pos );      // Добавляем новую вершину в путь ( в которую входит ребро из последней )
        inPath[pos] = true;
        v = pos;                    // И далее в цикле рассматриваем ее
    }

    v = 0;
    // Пока в первую вершину есть входящее ребро
    while( ( pos = has( graph[v], 0, inPath ) ) != -1 ) {
        path.push_front( pos );     // Добавляем новую вершину в путь ( из которой исходит ребро в первую )
        inPath[pos] = true;
        v = pos;                    // И далее в цикле рассматриваем ее
    }

    pos = 0;
    // Пока длина пути меньше количества вершин
    for( int len = path.size(); len < n; ++len ) {
        while( inPath[pos] ) {
            ++pos;                  // Находим позицию вершины, которой еще нет в пути
        }

        auto it = path.begin(); ++it;
        // В цикле находим, в какое место пути ее вставить
        for( ; it != path.end(); ++it ) {
            auto previt = it; --previt;
            int prev = *previt;
            int current = *it;
            // Если в вершину есть входящее ребро от предыдущей вершины в пути и есть исходящще в следующую
            if( graph[prev][pos] && graph[pos][current] ) {
                path.insert( it, pos );     // Вставляем ее в путь
                break;
            }
        }

        inPath[pos] = true;
    }

    // Выводим вершины в порядке, в котором они идут в пути
    cout << "Hamiltonial path" << endl;
    for( auto vertex : path ) {
        cout << vertex + 1 << ' ';
    }
    cout << endl;
}

void generate_graph( vector<vector<int>>& graph, mt19937& random_generator )
{
    for( int i = 0; i < graph.size(); ++i ) {
        for( int j = 0; j <= i; ++j ) {
            if( i == j ) {
                graph[i][j] = -1;
            } else if( random_generator() % 2 == 1 ) {
                graph[i][j] = 1;
            } else {
                graph[j][i] = 1;
            }
        }
    }
}

void input_graph( vector<vector<int>>& graph )
{
    cout << "Enter adjacency matrix for the graph ( n * n numbers split either by space or end of line characters,\n"
            "-1 stands for the diagonal, 1 if there's an oriented edge from the row number vertex to the column number\n"
            "vertex and 0 if the edge satisfies the case of 1 but it is reverted )" << endl;
    for( int i = 0; i < graph.size(); ++i ) {
        for( int j = 0; j < graph.size(); ++j ) {
            cin >> graph[i][j];
        }
    }
}

bool check_tournament( const vector<vector<int>>& graph )
{
    for( int i = 0; i < graph.size(); ++i ) {
        for( int j = 0; j < graph[i].size(); ++j ) {
            if(  i != j && ( j > graph.size() || i > graph[i].size() || graph[j][i] != 1 - graph[i][j] ) ) {
                return false;
            }
            if( i == j && graph[i][j] != -1 ) {
                return false;
            }
            if( abs( graph[i][j] ) > 1 ) {
                return false;
            }
        }
    }
    return true;
}

// Проверка на наличие входящих или исходящих ребер в зависимости от параметра dir
int has( const vector<int>& successors, int dir, const vector<bool>& inPath )
{
    for( int i = 0; i < successors.size(); ++i ) {
        if( successors[i] == dir && !inPath[i] ) {
            return i;
        }
    }
    return -1;
}