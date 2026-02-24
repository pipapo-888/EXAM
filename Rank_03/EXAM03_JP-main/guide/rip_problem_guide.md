
# RIP 解法ガイド（Problem 6）
**対象課題**: `rip`  
**目的**: 距離ベクトル型ルーティング（Routing Information Protocol: RIP）のコアを実装し、
ノード間の最短パス距離から **各ノードの経路表** を構築する。  
**キーワード**: Bellman–Ford, distance vector, convergence, split horizon, route poisoning.

---

## 1. 問題の要約と入出力
### 入力（例）
```
A B 2
A C 5
B D 1
C D 2
```
- 1 行 = 「ノード1 ノード2 コスト」
- 無向グラフを想定（RIP は隣接ルータ間で相互に広告する）。

### 出力（例）
```
Routing table for A:
A:0
B:2
C:4
D:3
```
- 起点ノードごとの最短距離（必要なら次ホップを併記してもよい）。

### 目標
- 隣接ノードの情報交換を繰り返し、**距離ベクトル**の収束で各ノードの最短距離を求める。

---

## 2. アルゴリズム選択
RIP の中核は **Bellman–Ford** の反復更新です。  
**更新式**：`D[u][x] = min( D[u][x], D[u][v] + w(u,v) + D[v][x] )`  
実装では 1 ホップ分 `w(u,v)` を隣接辺のコスト、`D[v][x]` を隣接ノードの広告距離として扱います。

### 実装方針の2択
1. **集中型（学習に最適）**  
   - 全ノードの距離表 `D[node][dest]` を保持し、反復で同時更新（同期ステップ）。
2. **分散シミュレーション（忠実度高）**  
   - 各ノードが「送信キュー」と「受信キュー」を持ち、広告を受けて局所更新。

> 課題としては **集中型** が実装簡単＆デバッグ容易でおすすめ。

---

## 3. データ構造の設計
- **ノードID管理**: 文字（'A'..）→ 連番 `0..N-1` にマップ（`map<char,int>` または自作ハッシュ）。
- **隣接リスト**: `vector<edge> adj[N]` / C なら可変配列 or 単方向リスト。`edge = {to, cost}`。
- **距離表**: `int dist[N][N]`（初期は INF、`dist[i][i]=0`）。
- **前駆/ネクストホップ表（任意）**: `int next[N][N]`（経路再構築や表示に便利）。

### 定数
- `INF = 1e9` 等の大きな値。
- RIP 的には「**最大ホップ数 15**」などの制限もあるが、課題では **一般の重み** を扱ってよい。

---

## 4. 初期化と更新ループ
```c
// 初期化
for i in [0..N-1]:
  for j in [0..N-1]:
    dist[i][j] = (i==j) ? 0 : INF
for each edge (u,v,w):
  dist[u][v] = min(dist[u][v], w)
  dist[v][u] = min(dist[v][u], w) // 無向

// 反復更新（同期ステップ）
changed = true
while (changed):
  changed = false
  for u in V:
    for v in adj[u]: // 近傍
      for x in V:
        if dist[v][x] == INF: continue
        if dist[u][x] > dist[u][v] + dist[v][x]:
          dist[u][x] = dist[u][v] + dist[v][x]
          changed = true
```
- 反復が進むと、全ノードのビューが **一貫する最短距離** に収束します。

---

## 5. 収束の検知と停止条件
- **変化が1回も起きなかった反復**で停止（`changed == false`）。
- または最大イテレーション `N-1`（Bellman–Fordの理論上限）で停止。

---

## 6. 出力フォーマット
- ノード順（A, B, C, ...）で安定ソートしておくと採点が行いやすい。
- 表示は `Routing table for X:` に続けて `dest:cost`。  
- **到達不能**は `INF`/`-1`/`unreachable` など課題仕様に合わせて表示（統一）。

---

## 7. サンプルスケルトン（C, 集中型）
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 128
#define INF 1000000000

typedef struct { int to, w; } Edge;
typedef struct { Edge *e; int m, n; } Vec;

static void vec_push(Vec *v, Edge ed){
    if (v->n == v->m){
        v->m = v->m ? v->m * 2 : 8;
        v->e = (Edge*)realloc(v->e, sizeof(Edge)*v->m);
        if (!v->e){ perror("realloc"); exit(1); }
    }
    v->e[v->n++] = ed;
}

static int id_of(int *idmap, int *n, int ch){
    if (!isalpha(ch)) return -1;
    ch = toupper(ch);
    int idx = ch - 'A';
    if (!idmap[idx]){ idmap[idx] = ++(*n); }
    return idmap[idx]-1;
}

int main(void){
    // 1) 入力読み込み
    Vec adj[MAXN] = {0};
    int idmap[26] = {0}; // 'A'..'Z' の簡易マップ
    int N = 0;
    char a[64], b[64]; int w;
    while (scanf("%63s %63s %d", a, b, &w) == 3){
        int u = id_of(idmap, &N, a[0]);
        int v = id_of(idmap, &N, b[0]);
        vec_push(&adj[u], (Edge){v, w});
        vec_push(&adj[v], (Edge){u, w});
    }

    // 2) 距離表初期化
    static int dist[MAXN][MAXN];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++) dist[i][j] = (i==j)?0:INF;
        for (int k=0;k<adj[i].n;k++){
            Edge e = adj[i].e[k];
            if (e.w < dist[i][e.to]) dist[i][e.to] = e.w;
        }
    }

    // 3) 収束まで反復更新（Bellman–Ford的）
    int changed = 1, iter = 0;
    while (changed && iter < N-1){
        changed = 0; iter++;
        for (int u=0; u<N; u++){
            for (int k=0; k<adj[u].n; k++){
                int v = adj[u].e[k].to;
                int wuv = adj[u].e[k].w;
                for (int x=0; x<N; x++){
                    if (dist[v][x] >= INF) continue;
                    int cand = wuv + dist[v][x];
                    if (cand < dist[u][x]){
                        dist[u][x] = cand;
                        changed = 1;
                    }
                }
            }
        }
    }

    // 4) 出力（A..Z順にしたい場合は idmap を逆引きして安定化する）
    for (int u=0; u<N; u++){
        printf("Routing table for %c:\n", 'A' + u);
        for (int x=0; x<N; x++){
            if (dist[u][x] >= INF) printf("%c:unreachable\n", 'A' + x);
            else                   printf("%c:%d\n", 'A' + x, dist[u][x]);
        }
    }
    return 0;
}
```
> **注意**: 入力のノード名が `'A'..'Z'` 前提の簡易実装です。実運用では汎用マップ/辞書を実装してください。

---

## 8. テスト計画
### 8.1 正常系
```bash
cat <<EOF | ./rip
A B 1
B C 3
A C 10
EOF
# Routing table for A:
# A:0
# B:1
# C:4
```

### 8.2 到達不能ノード
```bash
cat <<EOF | ./rip
A B 1
C D 2
EOF
# A から C/D は unreachable
```

### 8.3 複数辺・負コストなし
- 複数の同一エッジ行がある場合は **最小コスト** を採用。
- **負コスト**は RIP では非現実的なので **受け付けない** か、ガードする。

### 8.4 退行テスト（収束）
- ランダムグラフを複数回流し、反復回数が `<= N-1` で止まることを確認。

---

## 9. よくある落とし穴
- **初期化漏れ**（`dist[i][i]=0` 忘れ）。
- **無向/有向の不整合**（片方向だけ張る）。
- **INFのオーバーフロー**（足し算で `INF + w` が 32bit 上限超え）。
- **停止条件の欠落**（無限ループ）。
- **出力順・フォーマットが不安定**（自動採点で失敗）。

---

## 10. RIP らしい拡張（任意）
- **Split Horizon**: `u→v` へ広告する際、次ホップが `v` の経路は広告しない。
- **Route Poisoning**: ダウンした経路を `∞`（例: 16ホップ）で広告。
- **Triggered Update**: 変化が起きたら周期を待たずに即広告。

---

## 11. まとめ（攻略ポイント）
- 中心は **Bellman–Ford の反復更新**。まずは集中型で正しさを固める。
- 表示仕様（順序・unreachableの表記）を固定して、採点に強い実装にする。
- 余力があれば **分散シミュレーション** や **RIP 風拡張** を追加し、理解を深める。

