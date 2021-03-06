#include "SphereObstacle.hpp"
#include "error.hpp"

SphereObstacle::SphereObstacle(VEC3 p, FLOAT r, FLOAT ha, VEC3 hn, int shader) : Obstacle(shader){
  pos = p;
  ray = r;

  hole_angle = ha;
  hole_normal = hn;
  cosangle = cos(hole_angle);
}

SphereObstacle::~SphereObstacle() {
}

void SphereObstacle::apply(Motion m) {
  pos += m.translation;
  ray *= m.scale;
  hole_normal = m.rotation*hole_normal;
}

#ifndef NO_GRAPHICS_ 
void SphereObstacle::draw(glm::mat4 m, int s) {
  
  GLfloat lines[18] = {pos(0),  pos(1), pos(2) + ray,    pos(0), pos(1), pos(2) - ray,
		       pos(0) + ray,  pos(1), pos(2),    pos(0) - ray, pos(1), pos(2),
		       pos(0),  pos(1) + ray, pos(2),    pos(0), pos(1) - ray, pos(2)};
  GLfloat colors[18] = {0, 1, 1,     0, 1, 1,
			0, 1, 1,     0, 1, 1,
			0, 1, 1,     0, 1, 1};

  enableShader();
  setMVP(m, s);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, lines);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
  glEnableVertexAttribArray(1);
  
  glDrawArrays(GL_LINES, 0, 6);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  
  disableShader();
}
#endif
  
VEC3 SphereObstacle::getPosition() const {
  return pos;
}

FLOAT SphereObstacle::getRay() const {
  return ray;
}


VEC3 SphereObstacle::getNormal(VEC3 p) const {
  VEC3 normal;
  
  VEC3 n = p - pos;
  FLOAT norm = n.norm();
  assert(norm != 0);
  n /= norm;

  normal = -n;
  
  FLOAT cosalpha = n.dot(hole_normal);
  if (cosangle < cosalpha) {
    FLOAT alpha = acos(cosalpha);
    VEC3 axe = hole_normal.cross(n);
    axe.normalize();
    ANGLE_AXIS rot = ANGLE_AXIS(hole_angle, axe);

    VEC3 closest = pos + ray * (rot * hole_normal);
    normal = p - closest;
    normal.normalize();
  }
  return normal;
}

FLOAT SphereObstacle::distance(VEC3 v) const {
  FLOAT dist;
  VEC3 n = v - pos;
  FLOAT norm = n.norm();
  dist = ray - norm;
  
  FLOAT cosalpha = n.dot(hole_normal);
  if (cosangle < cosalpha) {
    dist = sqrt(norm*norm + ray*ray - 2 * norm * ray * cosalpha);
  }

  return dist;
}

void SphereObstacle::getCollisionValues(VEC3 p, FLOAT & dist, VEC3 &normal) const {
  VEC3 n = p - pos;
  FLOAT norm = n.norm();
  assert(norm != 0);
  n /= norm;

  normal = -n;
  dist = ray - norm;
  
  FLOAT cosalpha = n.dot(hole_normal);
  if (cosangle < cosalpha) {
    FLOAT alpha = acos(cosalpha);
    VEC3 axe = hole_normal.cross(n);
    axe.normalize();
    ANGLE_AXIS rot = ANGLE_AXIS(hole_angle, axe);

    VEC3 closest = pos + ray * (rot * hole_normal);
    normal = p - closest;
    normal.normalize();

    dist = sqrt(norm*norm + ray*ray - 2 * norm * ray * cosalpha);
  }

}


void SphereObstacle::exportMitsuba(std::ofstream & file) const {
  TEST(false); //TODO
}
