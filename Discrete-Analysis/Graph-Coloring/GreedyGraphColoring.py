from random import uniform
from random import shuffle
from math import *

def gen_graph(n, p):
    graph = [[True if j > i and uniform(0, 1) < p else False for j in range(n)] for i in range(n)]
    for i in range(n):
        for j in range(i):
            graph[i][j] = graph[j][i]
    return graph


def is_undirected(graph):
    for i in range(n):
        for j in range(i + 1):
            if i == j and graph[i][i]:
                return False
            if graph[i][j] != graph[j][i]:
                return False
    return True


def greedy_graph_color(graph):
    colors_count = 0
    coloring = [-1] * len(graph)
    shuffled_vertices = list(range(len(graph)))
#   shuffle(shuffled_vertices)
    for vertex in shuffled_vertices:
        used_colors = [False] * len(graph)
        for successor in range(len(graph)):
            if graph[vertex][successor] and coloring[successor] != -1:
                used_colors[coloring[successor]] = True
        for color in range(len(coloring)):
            if not used_colors[color]:
                coloring[vertex] = color
                colors_count = max(color + 1, colors_count)
                break
    return coloring, colors_count


#input_fmt = int(input("Enter a number:\n1)Random graph\n2)Custom graph\n"))
n = int(input("Enter number of vertices n:\n"))
graph = []
#if input_fmt == 1:
#    p = input("Enter the probability of an edge p (python arithmetic expression, may be depending on n):\n")
#    try:
#        p = eval(p)
#    except:
#        print("Incorrect probability expression")
#    graph = gen_graph(n, p)
#elif input_fmt == 2:
print("Enter an undirected graph (adjacency matrix, 1 if there is an edge, 0 else):")
for i in range(n):
        graph.append(list(map(lambda x: bool(int(x)), input().split())))
if not is_undirected(graph):
    print("Incorrect graph")
    exit(0)
coloring, colors_count = greedy_graph_color(graph)
print("\nNumber of colors returned by the greedy algorithm:\n", colors_count, sep='')
print("Vertex: color")
for item in ((i + 1, coloring[i] + 1) for i in range(n)):
    print("{}: {}; ".format(*item), end='')
