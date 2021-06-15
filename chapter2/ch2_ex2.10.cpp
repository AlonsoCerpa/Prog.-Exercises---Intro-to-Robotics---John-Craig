#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void rot_mat_to_zyz_euler_angles(Matrix3d &R, double &gamma, double &beta, double &alpha){
    beta = atan2(sqrt(pow(R(2, 0), 2) + pow(R(2, 1), 2)), R(2, 2));
    if (beta == 0.0){
        alpha = 0.0;
        gamma = atan2(R(0, 1), -R(0, 0));
    }
    else{
        alpha = atan2(R(1, 2) / sin(beta), R(0, 2) / sin(beta));
        gamma = atan2(R(2, 1) / sin(beta), R(2, 0) / sin(beta));
    }
}

void zyz_euler_angles_to_rot_mat(double &gamma, double &beta, double &alpha, Matrix3d &R){
    double cg = cos(gamma);
    double sg = sin(gamma);
    double cb = cos(beta);
    double sb = sin(beta);
    double ca = cos(alpha);
    double sa = sin(alpha);
    R << ca*cb*cg - sa*sg, -ca*cb*sg - sa*cg, ca*sb,
         sa*cb*cg + ca*sg, -sa*cb*sg + ca*cg, sa*sb,
         -sb*cg, sb*sg, cb;
}

int main(){
    double gamma = M_PI/2, beta = M_PI/2, alpha = M_PI;
    double gamma_r, beta_r, alpha_r;
    Matrix3d R;

    zyz_euler_angles_to_rot_mat(gamma, beta, alpha, R);
    rot_mat_to_zyz_euler_angles(R, gamma_r, beta_r, alpha_r);

    cout << "Gamma result:\n" << gamma_r << "\n";
    cout << "Beta result:\n" << beta_r << "\n";
    cout << "Alpha result:\n" << alpha_r << "\n";
}