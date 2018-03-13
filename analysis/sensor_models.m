%% Coil based geophone sensor response
clc
clear
close all
% Initialization
lambda = 0.25; % Damping ratio (relative to the critical damping)
w0 = 10; % Resonant frequency
Cs = 1; % Sensitivity constant
% Transfer Functions
H_displacement = tf([1 0 0 0],[1 2*lambda*w0 w0^2]);
H_velocity = tf([1 0 0],[1 2*lambda*w0 w0^2]);
H_acceleration = tf([1 0],[1 2*lambda*w0 w0^2]);
% Bode plots
figure(1)
bode(H_displacement);
title('Displacement to Electrical Signal Transfer Function');
figure(2)
bode(H_velocity);
title('Velocity to Electrical Signal Transfer Function');
figure(3)
bode(H_acceleration);
title('Acceleration to Electrical Signal Transfer Function');

%% MEMS sensor response
clc
clear
close all
% Initialization
lambda = 0.2; % Damping ratio (relative to the critical damping)
w0 = 10; % Resonant frequency
Cs = 1; % Sensitivity constant
% Transfer Functions
H_displacement = tf([1 0 0],[1 2*lambda*w0 w0^2]);
H_velocity = tf([1 0],[1 2*lambda*w0 w0^2]);
H_acceleration = tf([1],[1 2*lambda*w0 w0^2]);
% Bode plots
figure(1)
bode(H_displacement);
title('Displacement to Electrical Signal Transfer Function');
figure(2)
bode(H_velocity);
title('Velocity to Electrical Signal Transfer Function');
figure(3)
bode(H_acceleration);
title('Acceleration to Electrical Signal Transfer Function');
