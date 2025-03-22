import math
import heapq
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import LinearSegmentedColormap

class Point:
   def __init__(self, x, y, z, h, t):
        self.x = x # x coordinate
        self.y = y # y coordinate
        self.z = z # z coordinate
        self.h = h # heuristic value
        self.t = t # if obstructed 1, else 0
   def __lt__(self,other):
       return self.h<other.h
   def __hash__(self):
        return hash((self.x, self.y))  
   def __eq__(self, other):
        return (self.x, self.y) == (other.x, other.y) 
def dist(p1, p2):
    #d = abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z)
    d = math.sqrt((p1.x-p2.x)**2 + (p1.y-p2.y)**2 + (p1.z-p2.z)**2)
    return d

def flatdist(p1, p2):
    d = max(abs(p1.x-p2.x),abs(p1.y-p2.y))
    return d

def point_s_f(filename):
    points = []
    with open(filename, 'r') as file:
        for line in file:
            val = line.strip().split()
            x,y = map(float,val[:2])
            x=int(x)
            y=int(y)
            points.append(Point(x,y,0,0,0))
    return points[0], points[1]
        

def point_map(filename,fin):
    points = {}
    with open(filename, 'r') as file:
        for line in file:
            val = line.strip().split()
            x,y,z,t = map(float,val[:4])
            x=int(x)
            y=int(y)
            t=bool(int(t))
            p=Point(x,y,z,0,t)
            d=dist(p,fin)
            p.h=d
            points[(x,y)]=p
    return points

def path(fin,os):
    ut = []
    current = fin
    w=0
    while current is not None:
        if os.get(current) is not None:
            w = w + dist(current,os.get(current))
        ut.append(current)
        current = os.get(current)
    ut.reverse()
    
    for p in ut:
        print(f"{p.x} , {p.y}\n")   
    print(f"{w}")
    return ut

def nbr_points(pontok, p):
   
    x, y = p.x, p.y
    nbr = []
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            if dx == 0 and dy == 0:
                continue
            new_x, new_y = x + dx, y + dy
            if (new_x, new_y) in pontok: 
                nbr.append(pontok[(new_x, new_y)])
    return nbr


def a_star(pontok ,s,fin):
    for p in pontok.values():
        p.h = dist(p, fin)
    os = {}
    g = {point: float('inf') for point in pontok.values()}
    f = {point: float('inf') for point in pontok.values()}
    open_list = []
    closed_set = set()
    heapq.heappush(open_list, (0, s))
    g[s] = 0
    f[s] = dist(s, fin)
    
    
    while open_list:
        
        current = heapq.heappop(open_list)[1]
        if current.x == fin.x and current.y == fin.y:
            fin.z=current.z
            s.z =pontok[(s.x,s.y)].z
            print(g[fin])
            return path(fin, os)
        closed_set.add(current)
        for szomszed in nbr_points(pontok,current):
            if szomszed.t == 0 :
                score = g[current] + dist(current, szomszed)
                if score < g[szomszed]:
                    os[szomszed] = current
                    g[szomszed] = score
                    f[szomszed] = score + dist(szomszed, fin)
                    heapq.heappush(open_list, (f[szomszed], szomszed))
    return None

def visualize_3d(pontok, path):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    X = [p.x for p in pontok.values()]
    Y = [p.y for p in pontok.values()]
    Z = [p.z for p in pontok.values()]
    T = [p.t for p in pontok.values()]

    ax.plot_trisurf(X, Y, Z, cmap=create_custom_colormap(), edgecolor='none')

    black_points = [(p.x, p.y, p.z) for p in pontok.values() if p.t == 1]
    red_points = [(p.x, p.y, p.z) for p in path]
    ax.scatter(*zip(*black_points), c='black', marker='.', s=50)
    ax.scatter(*zip(*red_points), c='red', marker=',', s=50)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.legend()

    plt.show()
def create_custom_colormap():
    colors = [(0, "green"), (0.5, "yellow"), (1, "brown")]
    cmap = LinearSegmentedColormap.from_list("geographical_topological", colors)
    return cmap

input_c = 7
if input_c == 1:
    filename='surface_100x100.end_points.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='surface_100x100.txt'
if input_c == 2:
    filename='surface_100x100.end_points.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='surface_100x100_test1.txt'
if input_c == 3:
    filename='surface_100x100.end_points.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='surface_100x100_test2.txt'
if input_c == 4:
    filename='start_end_129.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='points_129.txt'
if input_c == 5:
    filename='surface_256x256.end_points.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='surface_256x256.txt'
if input_c == 6:
    filename='surface_512x512.end_points.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='surface_512x512.txt'   
if input_c == 7:
    filename='start_end_1025.txt'
    filename='inputs/aStar/'+str(filename)
    s,fin=point_s_f(filename)
    filename='points_1025.txt'
filename='inputs/astar/'+str(filename)
pontok=point_map(filename,fin)
path=a_star(pontok,s,fin)
visualize_3d(pontok,path)