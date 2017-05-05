%Subject: EE 3410 Take Home Quiz
%Name: Samuel Itschner
%Date: 11/9/2014
clc; clear all; close all;
[received_signal,fs,dontcare]= wavread('radiodata.wav');
received_signal = received_signal (:,1);
tn=[1:length(received_signal)];
t = transpose(tn);


Fc1 = 6000;%Cutoff Frequencies
Fc2 = 12000;

mod1 = cos(2*pi*(Fc1/fs)*t);

mod2 = cos(2*pi*(Fc2/fs)*t);

N = 8;%Filter Order
Rp = .5;%Passband Ripple
Rs = 50;%Stopband Rejection

%Bandpass Filter

Wp = 2.*[3000,9000]./fs;
[b,a]=ellip(N,Rp,Rs,Wp);

y = filter(b,a,received_signal);

signal_tilde = y .* mod1;

%LPF
[b,a]=ellip(8,.5,50,2*Fc1/fs);

y1 = filter(b,a,signal_tilde);

y1=0.98.*y1./max(abs(y1));

% wavwrite(y1,fs,16,'my_result1');

%Part 2

Wp = 2.*[9001,15000]./fs;

[b,a]=ellip(N,Rp,Rs,Wp);

y = filter(b,a,received_signal);

signal_tilde = y .* mod2;

[b,a]=ellip(8,.5,50,2*Fc2/fs);

y1 = filter(b,a,signal_tilde);

y1=0.98.*y1./max(abs(y1));

%wavwrite(y1,fs,16,'my_result2');