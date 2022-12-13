## 使用`tree`生成目录树

```bash
$ tree -I "*.gch|*.exe|*.cpp__tests" | clip.exe
.
├── README.md
├── data_structure
│   ├── KD_tree.hpp
│   ├── chtholly_tree.hpp
│   ├── disjoint_set_union.hpp
│   ├── fenwick_tree.hpp
│   ├── hash_map.hpp
│   ├── lazy_segment_tree.hpp
│   ├── linear_basis.hpp
│   ├── ordered_set.hpp
│   ├── rollback_dsu.hpp
│   ├── segment_tree.hpp
│   ├── sparse_table.hpp
│   └── weighted_dsu.hpp
├── debug
│   ├── debug.hpp
│   ├── random_number.hpp
│   └── test.bat
├── dynamic_programing
│   ├── Incremental_Convex_Hull_Trick.hpp
│   └── Matrix.hpp
├── geometry
│   ├── Area_of_Two_Circles_Intersection.cpp
│   └── Melkman.hpp
├── graph
│   ├── bellman_ford.hpp
│   ├── dijkstra.hpp
│   ├── dinic.hpp
│   ├── kosaraju.hpp
│   ├── lca_rmq.hpp
│   ├── lowlink.hpp
│   ├── manhattan_mst.hpp
│   ├── spfa.hpp
│   └── toposort.hpp
├── main.hpp
├── math
│   ├── combination.hpp
│   ├── minimax.hpp
│   └── stirling_number_module_small_p.hpp
├── misc
│   ├── BS.hpp
│   ├── int128.hpp
│   ├── mint.hpp
│   └── tree_hash.hpp
├── number_theory
│   ├── BSGS.hpp
│   ├── Cipolla.hpp
│   ├── Tonelli_Shanks.hpp
│   ├── eratosthenes.hpp
│   ├── exgcd.hpp
│   ├── inv.hpp
│   └── miller_rabin.hpp
├── polynomial
│   ├── FFT-Mod.hpp
│   ├── FFT.hpp
│   ├── lagrange.hpp
│   └── poly.cpp
└── strings
    ├── LPS_and_Z.md
    ├── hash.hpp
    ├── kmp.hpp
    ├── suffix_array_SA_IS.hpp
    ├── suffix_array_doubling.hpp
    └── z_algorithm.hpp

10 directories, 54 files
```