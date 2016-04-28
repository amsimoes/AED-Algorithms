#! /bin/bash

counter=1
echo -e "Ficheiro de dicionario a carregar:"
read input
while [ $counter -le 100 ]; do
  ./main < $input
  let counter=counter+1
done
