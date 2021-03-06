#ifndef MPM_CONF_HPP
#define MPM_CONF_HPP

#include "Eigen/Core"

#define FLOAT double
#define VEC2 Vector2d
#define VEC3 Vector3d
#define VEC4 Vector4d
#define VECX VectorXd
#define MAT2 Matrix2d
#define MAT3 Matrix3d
#define MAT4 Matrix4d
#define MATX MatrixXd
#define ANGLE_AXIS AngleAxisd
#define QUATERNION Quaterniond

using namespace Eigen;

class Tensor;

namespace mpm_conf {

  enum method_t {apic_ = 0, 
		 pic_,
		 flip_,
		 mix_,
		 nMethods};

  //Grid
  extern Eigen::VEC3 size_grid_; // meter
  extern Eigen::Vector3i size_grid_n_; // nb nodes per side
  extern FLOAT grid_spacing_; // m
  
  // isotropic elasticity
  extern FLOAT mu_, lambda_;
  extern FLOAT young_modulus_, poisson_;

  //anisotropic elasticity
  extern Eigen::VEC3 young_vec_;
  extern Eigen::VEC3 poisson_vec_;
  extern Eigen::VEC3 shearing_vec_;
  
  extern FLOAT dt_; // second
  extern Eigen::VEC3 gravity_; // m/s^2

  extern FLOAT density_; //kg/m^3 

  extern FLOAT friction_coef_;

  extern bool display_sphere_;
  extern int replay_speed_;

  extern unsigned int plastic_mode_; //0 drucker_prager (sand), 1 clamp eigenvalues (snow), 2 clamp diff between eigenvalues, 3 no plasticity
  extern unsigned int elastic_mode_; //0 sand, 1 snow, 2 linear

  extern bool anisotropy_on;

  // drucker-prager param
  extern Eigen::VEC4 hardenning_param_;
  // plastic_mode 1 param (snow-Stomakhin)
  extern Eigen::VEC3 stretch_max;
  extern Eigen::VEC3 stretch_min;
  // todo param plastic 2

  // damping
  extern FLOAT damping_;
  extern FLOAT cheat_damping_;
  extern bool smooth_vel_;

  // generalized anis
  extern Eigen::VEC3 anisotropy_values_;
  extern Tensor anisotropy_stress_;
  extern Tensor inv_anisotropy_stress_;
  extern Tensor anisotropy_strain_;
  extern Tensor inv_anisotropy_strain_;

  // elatic tangent tensors
  extern MATX tangent_stiffness;
  extern MATX inverse_tangent_stiffness;
  extern MATX tangent_stiffness_iso;
  extern MATX inverse_tangent_stiffness_iso;

  extern uint method_; //0 apic, 1 pic, 2 flip, 3 0.5*pic+0.95*flip
  extern bool implicit_;
  
  extern uint export_step_; //export particules every x steps 
  void loadConf(std::string file);
};

#endif
