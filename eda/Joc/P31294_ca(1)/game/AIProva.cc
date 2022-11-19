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
    Pos jug = unit(id).pos;
    visit[jug.i][jug.j] = true; 
    Dir d;

    if (pos_ok(jug + Up) and (cell(jug + Up).type != Waste and (cell(jug+Up).id != -1 and unit(cell(jug+Up).id).type != Dead))) {
      if (cell(jug + Up).food or (cell(jug + Up).id != -1 and unit(cell(jug + Up).id).type == Zombie)) return Up;
      else Q.push(make_pair(jug, Up));
    }

    if (pos_ok(jug + Down) and (cell(jug + Down).type != Waste and (cell(jug+Down).id != -1 and unit(cell(jug+Down).id).type != Dead))) {
      if (cell(jug + Down).food or (cell(jug + Down).id != -1 and unit(cell(jug + Down).id).type == Zombie)) return Down; 
      else Q.push(make_pair(jug, Down));
    }

    if (pos_ok(jug + Left) and (cell(jug + Left).type != Waste and (cell(jug+Left).id != -1 and unit(cell(jug+Left).id).type != Dead))) {
      if (cell(jug + Left).food or (cell(jug + Left).id != -1 and unit(cell(jug + Left).id).type == Zombie)) return Left; 
      else Q.push(make_pair(jug, Left));
    }

    if (pos_ok(jug + Right) and (cell(jug + Right).type != Waste and (cell(jug+Right).id != -1 and unit(cell(jug+Right).id).type != Dead))) {
      if (cell(jug + Right).food or (cell(jug + Right).id != -1 and unit(cell(jug + Right).id).type == Zombie)) return Right; 
      else Q.push(make_pair(jug, Right));
    }

    while (not Q.empty()) {
      pair<Pos, Dir> aux = Q.front();
      d = aux.second;
      Pos p = aux.first + d;
      Q.pop();
      
      if (not visit[p.i][p.j]) {
        visit[p.i][p.j] = true;
        
        if (pos_ok(p+Up) and cell(p+Up).type != Waste and not visit[p.i][p.j+1]) {
          if (cell(p+Up).food or (cell(p+Up).id != -1 and unit(cell(p+Up).id).type == Zombie)) d = Up;
          else Q.push(make_pair(p, Up));
        }
        
        if (pos_ok(p+Down) and cell(p+Down).type != Waste and not visit[p.i][p.j-1]) {
          if (cell(p+Down).food or (cell(p+Down).id != -1 and unit(cell(p+Down).id).type == Zombie)) d = Down;
          else Q.push(make_pair(p, Down));
        }
        
        if (pos_ok(p+Left) and cell(p+Left).type != Waste and not visit[p.i-1][p.j]) { 
          if (cell(p+Left).food or (cell(p+Left).id != -1 and unit(cell(p+Left).id).type == Zombie)) d = Left;
          else Q.push(make_pair(p, Left)); 
          }
        
        if (pos_ok(p+Right) and cell(p+Right).type != Waste and not visit[p.i+1][p.j]) {
          if (cell(p+Right).food or (cell(p+Right).id != -1 and unit(cell(p+Right).id).type == Zombie)) d = Right;
          else Q.push(make_pair(p, Right));
        }
      }
    }
    return d;
}

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
  
    //Getting alive units
    vector<int> alive = alive_units(me());
  
    //feim bucle general per tot el joc
    for (int id : alive) {
      Dir mov = bfs_pos(id);
      move(id, mov); 
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
