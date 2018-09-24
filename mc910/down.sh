#!/bin/zsh
for i in $(seq 0 4)
wget --no-check-certificate https://susy.ic.unicamp.br:9999/mc910/myCalc/dados/arq$i.in && wget https://susy.ic.unicamp.br:9999/mc910/myCalc/dados/arq$i.res --no-check-certificate

