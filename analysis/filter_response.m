clear all
close all

Preamplifier_gain=10;

R1_LPF=8.2e3;
R2_LPF=15e3;

C1_LPF=22e-9;
C2_LPF=10e-9;

Gain_sellected= 11; %[The main 4 options:11, 69, 101 and 221]

R_HPF=10e3;
C_HPF=4.7e-6;

s=tf('s');
wo_LPF=1/[sqrt(R1_LPF*R2_LPF*C1_LPF*C2_LPF)]
fo_LPF=wo_LPF/(2*pi)
Q_LPF=1/[wo_LPF*(R1_LPF*C1_LPF+R2_LPF*C1_LPF)]
H_LPF=(wo_LPF^2)/[s^2+wo_LPF/Q_LPF*s+wo_LPF^2]

wo_HPF=1/(R_HPF*C_HPF)
fo_HPF=wo_HPF/(2*pi)
H_HPF=s/[s+wo_HPF]

BW=fo_LPF-fo_HPF
H=Preamplifier_gain*H_LPF*Gain_sellected*H_HPF
%%
figure(1)
bode(H_LPF)
title('Sallen-Key active 2nd order butterworth low-pass filter')
legend('cutoff frequency of 968 Hz')

figure(2)
bode(H_HPF)
title('Fist order passive high filter')
legend('cutoff frequency of 3.3863Hz')

figure(3)
bode(H)
title('Signal conditioning circuit without the ADC')
legend('Bandwidth of 964.1254Hz')
