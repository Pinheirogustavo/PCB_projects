### A partir dos valores de amplitude e fase de Z1(canal 1 do medidor)
### e Z2(canal 2 do medidor), calcula Z (z1-z2), apresentando modulo e fase

modulo_z1 = 1101.30;
theta1 = -0.16  ; #graus
theta1 = deg2rad(theta1);
modulo_z2 = 1003.43;
theta2 = 0.24; #graus
theta2 = deg2rad(theta2);

z1 = modulo_z1*exp(i*theta1);
z2 = modulo_z2*exp(i*theta2);

z = z1-z2

modulo_z = abs(z)
theta_z = angle(z)
theta_z = rad2deg(theta_z)

sdsd = atan2(imag(z), real(z))
sdsd = rad2deg(sdsd);



ffff = atan2( (modulo_z1*sin(theta1) - modulo_z2*sin(theta2)) , (modulo_z1*cos(theta1) - modulo_z2*cos(theta2)))
tttt = ffff*180/3.1415
ffff = rad2deg(ffff)

seno = sin(theta1)
