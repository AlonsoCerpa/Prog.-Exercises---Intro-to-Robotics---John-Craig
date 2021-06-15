alpha_deg = input('Enter alpha: ');
beta_deg = input('Enter beta: ');
gamma_deg = input('Enter gamma: ');
pos_vector = input('Enter position vector: ');

hom_transf = ZYX_euler_pos_to_hom_transf(alpha_deg, beta_deg, gamma_deg, pos_vector);
disp(hom_transf);
P_A = hom_transf * [1; 0; 1; 1];
disp(P_A);
hom_transf_2 = rpy2tr(gamma_deg, beta_deg, alpha_deg, 'zyx');
hom_transf_2 = hom_transf_2 + transl(pos_vector);
hom_transf_2 = hom_transf_2 - eye(4);
disp(hom_transf_2);
P_A_2 = hom_transf_2 * [1; 0; 1; 1];
disp(P_A_2);

inv_hom_transf = inv_homogeneous_transf(hom_transf);
disp(inv_hom_transf);

disp(inv(hom_transf));

transf_B_rel_A = ZYX_euler_pos_to_hom_transf(10, 20, 30, [1, 2, 3]);
transf_C_rel_B = ZYX_euler_pos_to_hom_transf(0, 20, 0, [3, 0, 1]);
transf_C_rel_A = transf_B_rel_A * transf_C_rel_B;
disp(transf_C_rel_A);

transf_A_rel_C = inv_homogeneous_transf(transf_C_rel_B) * inv_homogeneous_transf(transf_B_rel_A);
disp(transf_A_rel_C);

transf_B_rel_A_2 = transf_C_rel_A * inv_homogeneous_transf(transf_C_rel_B);
disp(transf_B_rel_A_2);
disp(transf_B_rel_A);

transf_C_rel_B_2 = inv_homogeneous_transf(transf_B_rel_A) * transf_C_rel_A;
disp(transf_C_rel_B_2);
disp(transf_C_rel_B);

function angle_rad = degrees_to_radians(angle_deg)
    angle_rad = (angle_deg / 360.0) * (2.0*pi);
end

function angle_deg = radians_to_degrees(angle_rad)
    angle_deg = (angle_rad / (2.0*pi)) * 360.0;
end

function hom_transf = ZYX_euler_pos_to_hom_transf(alpha_deg, beta_deg, gamma_deg, pos)    
    alpha_rad = degrees_to_radians(alpha_deg);
    beta_rad = degrees_to_radians(beta_deg);
    gamma_rad = degrees_to_radians(gamma_deg);
    
    ca = cos(alpha_rad);
    sa = sin(alpha_rad);
    cb = cos(beta_rad);
    sb = sin(beta_rad);
    cg = cos(gamma_rad);
    sg = sin(gamma_rad);
    
    hom_transf = [ca*cb, ca*sb*sg - sa*cg, ca*sb*cg + sa*sg, pos(1);
                  sa*cb, sa*sb*sg + ca*cg, sa*sb*cg - ca*sg, pos(2);
                  -sb, cb*sg, cb*cg, pos(3);
                  0, 0, 0, 1];
end

function inv_hom_transf = inv_homogeneous_transf(hom_transf)
    inv_hom_transf = zeros(4);
    inv_hom_transf(1:3, 1:3) = transpose(hom_transf(1:3, 1:3));
    inv_hom_transf(1:3, 4) = (-1) * transpose(hom_transf(1:3, 1:3)) * hom_transf(1:3, 4);
    inv_hom_transf(4, 4) = 1.0;
end