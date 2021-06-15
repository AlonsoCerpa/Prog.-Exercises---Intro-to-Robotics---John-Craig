alpha_deg = input('Enter alpha: ');
beta_deg = input('Enter beta: ');
gamma_deg = input('Enter gamma: ');

rot_mat = ZYX_euler_to_rot_matrix(alpha_deg, beta_deg, gamma_deg);
disp(rot_mat);
angles = rot_matrix_to_ZYX_euler(rot_mat);
disp(angles);

rot_mat2 = rotz(alpha_deg) * roty(beta_deg) * rotx(gamma_deg);
disp(rot_mat2);
angles_ret = tr2rpy(rot_mat2, 'zyx');
angles_ret = radians_to_degrees(angles_ret);
angles = [angles_ret(3), angles_ret(2), angles_ret(1)];
disp(angles);

function angle_rad = degrees_to_radians(angle_deg)
    angle_rad = (angle_deg / 360.0) * (2.0*pi);
end

function angle_deg = radians_to_degrees(angle_rad)
    angle_deg = (angle_rad / (2.0*pi)) * 360.0;
end

function rot_matrix = ZYX_euler_to_rot_matrix(alpha_deg, beta_deg, gamma_deg)    
    alpha_rad = degrees_to_radians(alpha_deg);
    beta_rad = degrees_to_radians(beta_deg);
    gamma_rad = degrees_to_radians(gamma_deg);
    
    ca = cos(alpha_rad);
    sa = sin(alpha_rad);
    cb = cos(beta_rad);
    sb = sin(beta_rad);
    cg = cos(gamma_rad);
    sg = sin(gamma_rad);
    
    rot_matrix = [ca*cb, ca*sb*sg - sa*cg, ca*sb*cg + sa*sg;
                  sa*cb, sa*sb*sg + ca*cg, sa*sb*cg - ca*sg;
                  -sb, cb*sg, cb*cg];
end

function angles = rot_matrix_to_ZYX_euler(rot_mat)
    beta = asin(-rot_mat(3, 1));
    alpha = acos(rot_mat(1, 1) / cos(beta));
    gamma = asin(rot_mat(3, 2) / cos(beta));
    angles = radians_to_degrees([alpha, beta, gamma]);
end