reset                                           
set terminal gif animate delay 10
set output 'forest.gif'         
stats 'forest.txt' nooutput
unset tics
unset key
set size 0.99,0.95; set origin 0.01,0.05
set xrange[-1:100]
set yrange[-1:100]
set colorbox horizontal                         
set colorbox user origin 0.05,0.05 size 0.90,0.02
set cblabel "vazio, arvore, queimada, cinzas"
set palette defined ( 0 "#FFFFFF", 1 "#3ADF00", 2 "#2E2E2E", 3 "#FF8000")

do for [i=0:300] {
	#set output sprintf('matrix%03.0f.png',i)
    plot 'forest.txt' index i matrix with image notitle
}