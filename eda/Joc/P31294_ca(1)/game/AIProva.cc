#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Prova
#include <queue>

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  //Vector direccions
  typedef pair<Pos, Dir> pos_cola;
  typedef vector<vector<bool>> VVB;

  //Funció dfs per trobar nova pos
  Dir bfs_pos(int id) {
    VVB visit(board_rows(), vector<bool>(board_cols(), false));
    queue<pos_cola> Q;
    //Afegeixo a la cola les pos adjacents al jugador
    if (pos_ok(unit(id).pos + Up) and cell(unit(id).pos.i, unit(id).pos.j+1).type != Waste)
      Q.push(make_pair(unit(id).pos, Up));
    
    if (pos_ok(unit(id).pos + Down) and cell(unit(id).pos.i, unit(id).pos.j-1).type != Waste)
      Q.push(make_pair(unit(id).pos, Down));
    
    if (pos_ok(unit(id).pos + Left) and cell(unit(id).pos.i - 1, unit(id).pos.j).type != Waste)
      Q.push(make_pair(unit(id).pos, Left));

    if (pos_ok(unit(id).pos + Right) and cell(unit(id).pos.i + 1, unit(id).pos.j).type != Waste)
      Q.push(make_pair(unit(id).pos, Right));

    while (not Q.empty()) {
      pair<Pos, Dir> aux = Q.front();
      int  i = aux.first.i, j = aux.first.j;
      Dir aux_d = aux.second;
      Q.pop();
      
      if (cell(i, j) == Food) return aux_d;
      if (not visit[i][j]) {
        visit[i][j] = true;
        Pos p(i,j);
        if (not visit[i+1][j] and pos_ok(p + Right) and cell(unit(id).p.i, unit(id).p.j).type != Waste) 
        if (not visit[i-1][j])
        if (not visit[i][j+1])
        if (not visit[i][j+1])  
      }
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
  }
  //Getting alive units
  vector<int> alive = alive_units(me());
  
  //feim bucle general per tot el joc
  while (round() <= 200) {
    for (int id : alive) {
     Dir d = bfs_pos(id);
     move(id, d);
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
