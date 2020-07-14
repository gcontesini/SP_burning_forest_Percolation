reset                
set terminal png                           
set output 'stats.png'         
set xtics
set xrange[0:]
set yrange[0:0.65]
set multiplot

plot "status.txt" u ($1)/10000 w l title "sitios vazios"       ;
replot "status.txt" u ($2)/10000 w l title "sitios c/ arvores" ;
replot "status.txt" u ($3)/10000 w l title "sitios c/ cinzas"  ; 
replot "status.txt" u ($4)/10000 w l title "sitios c/ fogo" 

unset key
unset xlabel
unset ylabel
unset title
set grid

# zoom da esquerda

set xrange[ -1/10000 : 20/10000 ]
set yrange[ -1/10000 : 500/10000 ]
set origin 0.09,0.31
set size 0.35,0.3
replot 

# zoom da direita

set xrange[ 160/10000 : 165/10000 ] 
set yrange[ -1/10000 : 500/10000 ] 
set origin 0.6,0.31
set size 0.35,0.3
replot 

# zoom do meio

set xrange[ 80/10000 : 90/10000 ]
set yrange[ 2800/10000 : 3800/10000 ]
set origin 0.31,0.65
set size 0.35,0.3
replot 