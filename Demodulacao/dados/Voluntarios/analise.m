#Octave 7.1.0
#Autor: Gustavo Pinheiro

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Descricao do codigo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
Analise dos dados de bioimpedancia dos voluntarios do experimento
CAAE: 78985417.0.0000.5594
XXXXXXXXX
%}

#pre-defifinicoes do octave
clear all; more off;clc; close all; %limpa o ambiente de trabalho
#clearvars -except A ##### apaga todas as variaveis, menos a tabela A
pkg load control; pkg load signal; pkg load io;  %carrega pacotes

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Dados %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

A = xlsread('voluntarios.ods');                %abre o arquivo de dados txt
B = importdata('voluntarios.ods','\t', 2);

