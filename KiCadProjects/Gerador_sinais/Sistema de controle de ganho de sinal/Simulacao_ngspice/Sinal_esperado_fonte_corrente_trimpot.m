clear all; close all; clc;

Rf = 50e3;
Rs = linspace(1e3,100e3,99);

Gain = -(Rf./Rs);

A = 1; f=100e3;
tempo = [0 : 1/(100*f) : 3/f]; % cinco periodos do sinal
sinal = A*sin(2*pi*f*tempo);      %geracao da onda senoidal , sin(w.t), w = 2.pi/T

for idx = 1:length(Gain)
  ss(idx,:)= sinal*Gain(idx);
end




figure(1)
plot(tempo,sinal,'DisplayName','Sinal de entrada')
%plot(tempo,sinal,";Sinal de entrada;","color", "r",'linewidth',1.5)
ylim([-9 9])
grid on
hold on
n_plots = 99; %plota os n primeiros sinais com os ganhos testados.
for idx = 1:n_plots
plot (tempo,ss(idx,:),'DisplayName','ganho')
end
hold off
lgd= legend;


figure(2)
line([0 1] , [A A] ,"linestyle", "-", "color", "r")
ylim([-9 A])
grid on
hold on
for idx = 1:n_plots
line ([0 1] , [Gain(idx) Gain(idx)])
end
hold off

