#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void rot_mat_to_angle_axis(Matrix3d &R, Vector3d &K, double &theta){
    theta = acos((R(0, 0) + R(1, 1) + R(2, 2) - 1.0) / 2.0);
    if (theta == 0.0){
        K << 1, 0, 0;
    }
    else{
        K = (1.0/(2.0*sin(theta))) * Vector3d(R(2, 1) - R(1, 2), R(0, 2) - R(2, 0), R(1, 0) - R(0, 1));
    }    
}

void angle_axis_to_rot_mat(Vector3d &K, double &theta, Matrix3d &R){
    if (theta == 0.0){
        R << 1.0, 0.0, 0.0,
             0.0, 1.0, 0.0,
             0.0, 0.0, 1.0;
    }
    else{
        double kx = K(0);
        double ky = K(1);
        double kz = K(2);
        double vthe = 1.0 - cos(theta);
        double cthe = cos(theta);
        double sthe = sin(theta);

        R << kx*kx*vthe + cthe, kx*ky*vthe - kz*sthe, kx*kz*vthe + ky*sthe,
             kx*ky*vthe + kz*sthe, ky*ky*vthe + cthe, ky*kz*vthe - kx*sthe,
             kx*kz*vthe - ky*sthe, ky*kz*vthe + kx*sthe, kz*kz*vthe + cthe;
    }
}

int main(){
    Vector3d K(0.0, 1.0, 0.0), K_r;
    double theta = M_PI/2, theta_r;
    Matrix3d R;

    angle_axis_to_rot_mat(K, theta, R);
    rot_mat_to_angle_axis(R, K_r, theta_r);

    cout << "K result:\n" << K_r << "\n";
    cout << "theta result:\n" << theta_r << "\n";
}