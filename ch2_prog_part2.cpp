#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

//Exercise 1:
double custom_atan2(double y, double x){
    if (x > 0){
        return atan(y/x);
    }
    else if (x < 0 && y >= 0){
        return atan(y/x) + M_PI;
    }
    else if (x < 0 && y < 0){
        return atan(y/x) - M_PI;
    }
    else if (x == 0 && y > 0){
        return M_PI/2;
    }
    else if (x == 0 && y < 0){
        return -M_PI/2;
    }
    else{
        return NAN;
    }
}

//Exercise 2:
void user_to_internal_form(Vector3d &user_form, Matrix3d &internal_form){
    double x = user_form(0);
    double y = user_form(1);
    double theta = user_form(2);

    double ct = cos(theta);
    double st = sin(theta);

    internal_form << ct, -st, x,
                     st, ct, y,
                     0, 0, 1;
}

void internal_to_user_form(Matrix3d &internal_form, Vector3d &user_form){
    user_form(0) = internal_form(0, 2);
    user_form(1) = internal_form(1, 2);
    user_form(2) = acos(internal_form(0, 0));
    if (asin(internal_form(1, 0) < 0)){
        user_form(2) = 2*M_PI - user_form(2);
    }
}

//Exercise 3:
void multiply_transforms(Matrix3d &B_relat_A, Matrix3d &C_relat_B, Matrix3d &C_relat_A){
    C_relat_A = B_relat_A * C_relat_B;
}

//Exercise 4:
void invert_transform(Matrix3d &B_relat_A, Matrix3d &A_relat_B){
    Matrix2d transpose_rot_B_relat_A = B_relat_A.block(0, 0, 2, 2).transpose();
    A_relat_B.block(0, 0, 2, 2) = transpose_rot_B_relat_A;
    A_relat_B.block(0, 2, 2, 1) = (-1) * transpose_rot_B_relat_A * B_relat_A.block(0, 2, 2, 1);
    A_relat_B.block(2, 0, 1, 2) = MatrixXd::Zero(1, 2);
    A_relat_B(2, 2) = 1.0;
}

int main(){
    //Exercise 1:
    double y = 3.0, x = 0.0;
    double res, res2;
    res = custom_atan2(y, x);
    res2 = atan2(y, x);

    cout << "Exercise 1:\n";
    cout << "custom atan2 result: " << res << "\n";
    cout << "lib atan2 result: " << res2 << "\n\n";

    //Exercise 2:
    Vector3d user_form(3, 2, 4*M_PI/3), user_form_r;
    Matrix3d internal_form;
    user_to_internal_form(user_form, internal_form);
    internal_to_user_form(internal_form, user_form_r);

    cout << "Exercise 2:\n";
    cout << "Result user form:\n" << user_form_r << "\n\n";

    //Exercise 3:
    Vector3d B_relat_A_u(3.0, 2.0, M_PI/2.0), C_relat_B_u(3.0, 2.0, 0.0), C_relat_A_u;
    Matrix3d B_relat_A_i, C_relat_B_i, C_relat_A_i;
    user_to_internal_form(B_relat_A_u, B_relat_A_i);
    user_to_internal_form(C_relat_B_u, C_relat_B_i);
    multiply_transforms(B_relat_A_i, C_relat_B_i, C_relat_A_i);
    internal_to_user_form(C_relat_A_i, C_relat_A_u);

    cout << "Exercise 3:\n";
    cout << "Multiplication result internal form:\n" << C_relat_A_i << "\n";
    cout << "Multiplication result user form:\n" << C_relat_A_u << "\n\n";

    //Exercise 4:
    Vector3d transform_u(3.0, 2.0, M_PI), inverted_transform_u;
    Matrix3d transform_i, inverted_transform_i;
    user_to_internal_form(transform_u, transform_i);
    invert_transform(transform_i, inverted_transform_i);
    internal_to_user_form(inverted_transform_i, inverted_transform_u);

    cout << "Exercise 4:\n";
    cout << "Inverted transform internal form:\n" << inverted_transform_i << "\n";
    cout << "Inverted transform user form:\n" << inverted_transform_u << "\n\n";

    //Exercise 5:
    Vector3d A_rel_U_u(11.0, -1.0, M_PI/6), A_rel_B_u(0.0, 7.0, M_PI/4), U_rel_C_u(-3.0, -3.0, -M_PI/6);
    Matrix3d A_rel_U_i, A_rel_B_i, U_rel_C_i;
    user_to_internal_form(A_rel_U_u, A_rel_U_i);
    user_to_internal_form(A_rel_B_u, A_rel_B_i);
    user_to_internal_form(U_rel_C_u, U_rel_C_i);
    Matrix3d inv_A_rel_U_i; 
    invert_transform(A_rel_U_i, inv_A_rel_U_i);
    Matrix3d inv_U_rel_C_i; 
    invert_transform(U_rel_C_i, inv_U_rel_C_i);
    Matrix3d mult1;
    multiply_transforms(inv_A_rel_U_i, inv_U_rel_C_i, mult1);
    Matrix3d C_rel_B_i;
    multiply_transforms(A_rel_B_i, mult1, C_rel_B_i);
    Vector3d C_rel_B_u;
    internal_to_user_form(C_rel_B_i, C_rel_B_u);

    cout << "Exercise 5:\n";
    cout << "Transform C relative to B - internal form:\n" << C_rel_B_i << "\n";
    cout << "Transform C relative to B - user form:\n" << C_rel_B_u << "\n\n";
}