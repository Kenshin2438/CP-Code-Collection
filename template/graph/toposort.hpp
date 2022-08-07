// 0-indexed
// `G` denotes the Graph
// `d` denotes the in-degree

auto toposort = [](const auto &G, auto d) -> vector<int> {
  queue<int> Q;
  for (int i = 0; i < (int)d.size(); i++) {
    if (d[i] == 0) Q.push(i);
  }
  vector<int> topo;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    topo.emplace_back(u);
    for (const int &v : G[u]) {
      if (--d[v] == 0) Q.push(v);
    }
  }
  return topo;
};
