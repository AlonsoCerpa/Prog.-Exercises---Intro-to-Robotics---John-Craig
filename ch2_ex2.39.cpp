#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
 
using namespace Eigen;
using namespace std;
 
void unit_quaternion_from_rot_mat(Matrix3d &R, Vector4d &q){
    q(3) = 0.5 * sqrt(1 + R(0, 0) + R(1, 1) + R(2, 2));
    q(0) = (R(2, 1) - R(1, 2)) / (4 * q(3));
    q(1) = (R(0, 2) - R(2, 0)) / (4 * q(3));
    q(2) = (R(1, 0) - R(0, 1)) / (4 * q(3));
}

double sum_squared_elements(Vector4d &q){
    return pow(q(0), 2) + pow(q(1), 2) + pow(q(2), 2) + pow(q(3), 2);
}

int main(){
    Matrix3d R;
    R << 0.25, 0.43, 0.86,
         0.87, -0.5, 0.0,
         0.43, 0.75, -0.5;
    Vector4d q;

    unit_quaternion_from_rot_mat(R, q);

    cout << "Quaternion\n" << q << "\n";
    cout << "Sum of squared elements: " << sum_squared_elements(q) << "\n";
}