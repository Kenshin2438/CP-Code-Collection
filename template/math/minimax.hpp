inline int doMin(int step, int alpha, int beta);
inline int doMax(int step, int alpha, int beta);
inline bool assess() {} // 如果输赢（平局）已定，返回结果 
int doMax(int step, int alpha, int beta) {
  if (assess()) return res;
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    if (g[i][j] == 0) {
      g[i][j] = playerX;
      int now = doMin(step + 1, alpha, beta);
      g[i][j] = 0;

      if (now > alpha) alpha = now;
      if (alpha >= beta) return alpha;
    }
  }
  return alpha;
}
int doMin(int step, int alpha, int beta) {
  if (assess()) return res;
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    if (g[i][j] == 0) {
      g[i][j] = playerO;
      int now = doMax(step + 1, alpha, beta);
      g[i][j] = 0;

      if (now < beta) beta = now;
      if (alpha >= beta) return beta;
    }
  }
  return beta;
}
int battle(int step, int alpha, int beta) {
  if (step & 1) { // playerO 最小化得分
    return doMin(step, alpha, beta);
  } else { // playerX 最大化得分
    return doMax(step, alpha, beta);
  } 
}