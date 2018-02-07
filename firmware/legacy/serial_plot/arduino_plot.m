clc
clear all
close all

a=arduino;
ts=0.02;

figure(1)

for i=1:1*10e3
data(1,i) = readVoltage(a,'A0');
t(1,1:length(data))=0:ts:ts*length(data)-ts;
plot(t,data);
xlabel('Time (s)');
ylabel('Amplitude (V)');
hold on
pause(ts);
end
