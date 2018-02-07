%%arduinoCom=serial('/dev/tty.usbmodem1411','BaudRate',9600);
%fopen(arduinoCom);
clear data t

ts=0.0005;

for i=1:1000
t(i)=i*ts;
data(i) = fscanf(arduinoCom,'%f');

end

figure(1)
plot(t,data);
xlabel('Time (s)');
ylabel('Amplitude (V)');
