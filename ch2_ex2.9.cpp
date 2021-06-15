#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void rot_mat_to_xyz_fixed_angles(Matrix3d &R, double &gamma, double &beta, double &alpha){
    beta = atan2(-R(2, 0), sqrt(pow(R(0, 0), 2) + pow(R(1, 0), 2)));
    alpha = atan2(R(1, 0) / cos(beta), R(0, 0) / cos(beta));
    gamma = atan2(R(2, 1) / cos(beta), R(2, 2) / cos(beta));
}

void xyz_fixed_angles_to_rot_mat(double &gamma, double &beta, double &alpha, Matrix3d &R){
    double cg = cos(gamma);
    double sg = sin(gamma);
    double cb = cos(beta);
    double sb = sin(beta);
    double ca = cos(alpha);
    double sa = sin(alpha);
    R << ca*cb, ca*sb*sg - sa*cg, ca*sb*cg + sa*sg,
         sa*cb, sa*sb*sg + ca*cg, sa*sb*cg - ca*sg,
         -sb, cb*sg, cb*cg;
}

int main(){
    double gamma = M_PI/2, beta = -M_PI/2, alpha = M_PI;
    double gamma_r, beta_r, alpha_r;
    Matrix3d R;

    xyz_fixed_angles_to_rot_mat(gamma, beta, alpha, R);
    rot_mat_to_xyz_fixed_angles(R, gamma_r, beta_r, alpha_r);

    cout << "Gamma result:\n" << gamma_r << "\n";
    cout << "Beta result:\n" << beta_r << "\n";
    cout << "Alpha result:\n" << alpha_r << "\n";
}