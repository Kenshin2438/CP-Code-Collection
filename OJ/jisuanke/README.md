## A1108 百度地图的实时路况

def: d(u, v, w) = 从u到v不经过w的最短路。

求$Ans = \sum d(u, v, w)$, 暴力$O(n^4)$ -> 分治 $O(n^3\log{n})$