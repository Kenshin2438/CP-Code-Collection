## 使用`tree`生成目录树

```bash
$ tree -I "*.gch|*.exe|*.cpp__tests"
.
├── data_structure
│   ├── chtholly_tree.hpp
│   ├── disjoint_set_union.hpp
│   ├── fenwick_tree.hpp
│   ├── lazy_segment_tree.hpp
│   ├── ordered_set.hpp
│   ├── rollback_dsu.hpp
│   ├── segment_tree.hpp
│   ├── sparse_table.hpp
│   └── weighted_dsu.hpp
├── debug
│   ├── debug.hpp
│   ├── random_number.hpp
│   └── test.bat
├── geometry
│   ├── Area_of_Two_Circles_Intersection.cpp
│   └── Melkman.hpp
├── graph
│   ├── bellman_ford.hpp
│   ├── dijkstra.hpp
│   ├── lca_rmq.hpp
│   ├── lowlink.hpp
│   ├── manhattan_mst.hpp
│   ├── spfa.hpp
│   └── toposort.hpp
├── main.hpp
├── number_theory
│   ├── BSGS.hpp
│   ├── Cipolla.hpp
│   ├── Tonelli_Shanks.hpp
│   ├── eratosthenes.hpp
│   └── exgcd.hpp
├── numerical
│   ├── int128.hpp
│   ├── inv.hpp
│   ├── linear_basis.hpp
│   └── mint.hpp
├── polynomial
│   ├── FFT-Mod.hpp
│   ├── lagrange.hpp
│   └── poly.cpp
└── strings
    ├── LPS_and_Z.md
    ├── hash.hpp
    ├── kmp.hpp
    ├── suffix_array_SA_IS.hpp
    ├── suffix_array_doubling.hpp
    └── z_algorithm.hpp

8 directories, 40 files
```