#!/bin/bash

sdir="/home/lorenzo/Pictures/mostra23_fromStudio214/Selezione_Stampa"
ddir="../"

# 2 portraits
echo "1:: 2 portraits"
./process --save="${ddir}1.jpg" --config=parameters.cfg --ncols=2 "${sdir}/1.jpg" "${sdir}/2.jpg"

# 1 landscape
echo "2:: 1 landscape"
./process --save="${ddir}2.jpg" --config=parameters.cfg "${sdir}/3.jpg"

# 4 landscapes
echo "3:: 4 landscapes"
./process --save="${ddir}3.jpg" --config=parameters.cfg --nrows=2 --ncols=2 "${sdir}/4.jpg" "${sdir}/5.jpg" "${sdir}/6.jpg" "${sdir}/7.jpg"

# 3 portraits
echo "4:: 3 portraits"
./process --save="${ddir}4.jpg" --config=parameters.cfg --ncols=3 "${sdir}/8.jpg" "${sdir}/9.jpg" "${sdir}/10.jpg"

# 2 landscapes
echo "5:: 2 landscapes"
./process --save="${ddir}5.jpg" --config=parameters.cfg --nrows=2 "${sdir}/11.jpg" "${sdir}/12.jpg" 

# 2 portraits
echo "6:: 2 portraits"
./process --save="${ddir}6.jpg" --config=parameters.cfg --ncols=2 "${sdir}/13.jpg" "${sdir}/14.jpg"

# 1 portrait
echo "7:: 1 portrait"
./process --save="${ddir}7.jpg" --config=parameters.cfg "${sdir}/15.jpg"

# cross (4 landscapes)
echo "8:: cross"
./process --save="${ddir}8.jpg" --config=parameters.cfg --cross "${sdir}/16.jpg" "${sdir}/17.jpg" "${sdir}/18.jpg" "${sdir}/19.jpg"

# 1 landscape
echo "9:: 1 landscape"
./process --save="${ddir}9.jpg" --config=parameters.cfg "${sdir}/20.jpg"

# 3 portraits
echo "10:: 3 portraits"
#./process --save="${ddir}10.jpg" --config=parameters.cfg --ncols=3 "${sdir}/21.jpg" "${sdir}/22.jpg" "${sdir}/23.jpg"

# 4 landscapes
echo "11:: 4 landscapes"
./process --save="${ddir}11.jpg" --config=parameters.cfg --nrows=2 --ncols=2 "${sdir}/24.jpg" "${sdir}/25.jpg" "${sdir}/26.jpg" "${sdir}/27.jpg"

# 2 portraits
echo "12:: 2 portraits"
#./process --save="${ddir}12.jpg" --config=parameters.cfg --ncols=2 "${sdir}/28.jpg" "${sdir}/29.jpg"

# 4 landscapes
echo "13:: 4 landscapes"
#./process --save="${ddir}13.jpg" --config=parameters.cfg --nrows=2 --ncols=2 "${sdir}/30.jpg" "${sdir}/31.jpg" "${sdir}/32.jpg" "${sdir}/33.jpg"

# 1 portrait
echo "14:: 1 portrait"
./process --save="${ddir}14.jpg" --config=parameters.cfg "${sdir}/34.jpg"

# 4 landscapes
echo "15:: 4 landscapes"
#./process --save="${ddir}15.jpg" --config=parameters.cfg --nrows=2 --ncols=2 "${sdir}/35.jpg" "${sdir}/36.jpg" "${sdir}/37.jpg" "${sdir}/38.jpg"

# 1 landscape
echo "16:: 1 landscape"
#./process --save="${ddir}16.jpg" --config=parameters.cfg "${sdir}/39.jpg"

# 2 portraits
echo "17:: 2 portraits"
./process --save="${ddir}17.jpg" --config=parameters.cfg --ncols=2 "${sdir}/40.jpg" "${sdir}/41.jpg"

