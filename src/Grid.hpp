#ifndef GRID_HPP
#define GRID_HPP

#include "Object.hpp"

#include <vector>
#include <list>
#include "Eigen/Core"
#include "Particule.hpp"
#include "Subparticule.hpp"
#include "Obstacle.hpp"

using namespace Eigen;

class Grid : public Object {

private :
#ifndef NO_GRAPHICS_ 
  GLfloat* vertices;
  GLfloat* colors;
#endif
  uint nb_lines;

  FLOAT spacing;
  
  FLOAT x_max, y_max, z_max;
  uint i_max, j_max, k_max;
  uint nb_nodes;
  uint nb_cells;

  std::vector<FLOAT> masses;
  std::vector<bool> active_nodes;
  std::vector<bool> fixed_nodes;
  std::vector<VEC3> fixed_velocities;
  std::vector<VEC3> velocities;
  std::vector<VEC3> inter_velocities;
  std::vector<VEC3> prev_velocities;
  std::vector<VEC3> positions;
  std::vector<VEC3> new_positions;
  std::vector<std::list<Particule*> > cells;
  std::vector<FLOAT> distance_collision;
  std::vector<MAT3> rotations;
  
  inline uint index(uint i, uint j, uint k) const;
  Vector3i nodeFromIndex(int ind) const;
public :
  Grid();
  Grid(FLOAT width, FLOAT depth, FLOAT height, FLOAT space_step, int shader = -1);

  void init(std::vector<Particule*> & particules);
  
  void animate();

#ifndef NO_GRAPHICS_ 
  void draw(glm::mat4 m = glm::mat4(1.0f), int s = -1);
#endif
  
  VEC3 position(uint i, uint j, uint k) const;
  VEC3 velocity(uint i, uint j, uint k) const;
  VEC3 & velocity(uint i, uint j, uint k);

  void nextStep(); //reset values in vectors
  void smoothVelocity();

  /*** not tested ***/
  void smoothRotation(std::vector<Particule*> & particules, std::vector<Subparticule*> & subparticules);
  
  void particulesToGrid(std::vector<Particule*> & particules);
  /*** not tested **/
  void particulesToGridImplicite(std::vector<Particule*> & particules);
  void gridToParticules(std::vector<Particule*> & particules);
  void gridToSubparticules(std::vector<Subparticule*> & subparticules);


  void initCollision(std::list<Obstacle*> obstacles);
  void collision(std::list<Obstacle*> obstacles);

  /** not tested **/
  MAT3 secondDer(uint i, uint j, std::vector<Particule*> & particules);

  /** fix the velocity of the nodes between min and max to null */
  void fix(VEC3 min, VEC3 max);
  /** fix the velocity of the nodes between min and max to dt*trans */
  void move(VEC3 min, VEC3 max, VEC3 trans);

  void exportGrid(std::ofstream & file) const;
  void importGrid(std::ifstream & file);
};

#endif
