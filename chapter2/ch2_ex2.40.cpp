#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void rot_mat_to_zxz_euler_angles(Matrix3d &R, double &gamma, double &beta, double &alpha){
    beta = acos(R(2, 2));
    alpha = acos(-R(1, 2)/sin(beta));
    gamma = acos(R(2, 1)/sin(beta));
}

void zxz_euler_angles_to_rot_mat(double &gamma, double &beta, double &alpha, Matrix3d &R){
    double cg = cos(gamma);
    double sg = sin(gamma);
    double cb = cos(beta);
    double sb = sin(beta);
    double ca = cos(alpha);
    double sa = sin(alpha);
    R << -sa*cb*sg + ca*cg, -sa*cb*cg - ca*sg, sa*sb,
         ca*cb*sg + sa*cg, ca*cb*cg - sa*sg, -ca*sb,
         sb*sg, sb*cg, cb;
}

int main(){
    double gamma = M_PI/2, beta = M_PI, alpha = M_PI;
    double gamma_r, beta_r, alpha_r;
    Matrix3d R;

    zxz_euler_angles_to_rot_mat(gamma, beta, alpha, R);
    rot_mat_to_zxz_euler_angles(R, gamma_r, beta_r, alpha_r);

    cout << "Gamma result:\n" << gamma_r << "\n";
    cout << "Beta result:\n" << beta_r << "\n";
    cout << "Alpha result:\n" << alpha_r << "\n";
}