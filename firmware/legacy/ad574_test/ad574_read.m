%a = arduino();

for i=1:100
writeDigitalPin(a,'D13',1);% Read
writeDigitalPin(a,'D13',0);% Convert
Status = readDigitalPin(a,'D16');
D11 = readDigitalPin(a,'D15');
D10 = readDigitalPin(a,'D2');
D9 = readDigitalPin(a,'D3');
D8 = readDigitalPin(a,'D4');
D7 = readDigitalPin(a,'D5');
D6 = readDigitalPin(a,'D6');
D5 = readDigitalPin(a,'D7');
D4 = readDigitalPin(a,'D8');
D3 = readDigitalPin(a,'D9');
D2 = readDigitalPin(a,'D10');
D1 = readDigitalPin(a,'D11');
D0 = readDigitalPin(a,'D12');
Data(i) = 2048*D11 + 1028*D10 + 512*D9 + 256*D8 + 128*D7 + 64*D6 + 32*D5 + 16*D4 + 8*D3 + 4*D2 + 2*D1 + D0; 
end
