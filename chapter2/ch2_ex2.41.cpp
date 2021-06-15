#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void rot_mat_to_xyx_fixed_angles(Matrix3d &R, double &gamma, double &beta, double &alpha){
    beta = acos(R(0, 0));
    alpha = asin(R(1, 0)/sin(beta));
    gamma = asin(R(0, 1)/sin(beta));
}

void xyx_fixed_angles_to_rot_mat(double &gamma, double &beta, double &alpha, Matrix3d &R){
    double cg = cos(gamma);
    double sg = sin(gamma);
    double cb = cos(beta);
    double sb = sin(beta);
    double ca = cos(alpha);
    double sa = sin(alpha);
    R << cb, sb*sg, sb*cg,
         sa*sb, -sa*cb*sg + ca*cg, -sa*cb*cg - ca*sg,
         -ca*sb, ca*cb*sg + sa*cg, ca*cb*cg - sa*sg;
}

int main(){
    double gamma = M_PI/2, beta = M_PI, alpha = M_PI/2;
    double gamma_r, beta_r, alpha_r;
    Matrix3d R;

    xyx_fixed_angles_to_rot_mat(gamma, beta, alpha, R);
    rot_mat_to_xyx_fixed_angles(R, gamma_r, beta_r, alpha_r);

    cout << "Gamma result:\n" << gamma_r << "\n";
    cout << "Beta result:\n" << beta_r << "\n";
    cout << "Alpha result:\n" << alpha_r << "\n";
}