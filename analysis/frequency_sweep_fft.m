%********************************************************%
%****EE411, section , Wireless Seismic Data Aquistion****%
%**This is the MATLAB code that was used for section 4.3*%
%Where the wireless communication was tested and verified%
%********************************************************%

number_of_signals=14;
index=1;  %for the subplot
s=2;    %To decide in which figure the plot will be
R_mean=[1:14]; %frequencies results array without BPF
R_BPF=[1:14];  %frequencies results array with BPF
Fs = 281.531532;            % Sampling frequency
rangeStart=[0 0 0 0 0 5 5 5 15 20 30 40 50 60];
rangeStop=[5 5 15 15 20 30 35 40 50 75 80 90 100 110];

%%***************Design The BPF and generate it***************%%
d = fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2',80,85,95,100,100,0.05,100,Fs); %set the filter parameters
   Hd = design(d);    %design the filter
   fvtool(Hd);  %plot the filter
%%***************Design The BPF and generate it***************%%

for i=1:number_of_signals

    Signal_mean{i}=x{i}-mean(x{i}); %optimize the signal to 0V DC
    Signal_BPF{i} = filter(Hd,x{i}); %pass the signal to a BPF

%%***************Apply FFT the optimized signal***************%%
f_axis_mean=-Fs/2:Fs/length(Signal_mean{i}):Fs/2-Fs/length(Signal_mean{i});
Y_mean = abs(fftshift(fft(Signal_mean{i})));
%%***************Apply FFT the optimized signal***************%%

%%**Find the peak frequency then store it into R_mean array**%%
[~,f_index_mean]=max(Y_mean);
R_mean(i)=abs(f_axis_mean(f_index_mean));  %
%%**Find the peak frequency then store it into R_mean array**%%

%plot FFT of the signal
figure(s);subplot(5,3,index);plot(f_axis_mean,Y_mean);xlim([rangeStart(i) rangeStop(i)]);

%%***************Apply FFT to band passed signal***************%%
f_axis_BPF=-Fs/2:Fs/length(Signal_BPF{i}):Fs/2-Fs/length(Signal_BPF{i});
Y_BPF = abs(fftshift(fft(Signal_BPF{i})));
%%***************Apply FFT to band passed signal***************%%

%%**Find the peak frequency then store it into R_BPF array**%%
[m,f_index_BPF]=max(Y_BPF);
R_BPF(i)=abs(f_axis_BPF(f_index_BPF));
%%**Find the peak frequency then store it into R_BPF array**%%

%plot FFT of the signal
figure(s+1);subplot(5,3,index);plot(f_axis_BPF,Y_BPF);xlim([rangeStart(i) rangeStop(i)]);

index=index+1;  %increase the index to continue ploting
end

diff=R_mean-R_BPF    %to find how far do measured frequencies agree (with and
                %without BPF)
R_mean  %display the final results
R_BPF   %display the final results
