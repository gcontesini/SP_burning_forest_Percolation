
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BEGIN OF HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#!/usr/bin/env  R
# 21 May 2013 - Luiz C. Mostaco-Guidolin - <luiz.guidolin@med.umanitoba.ca>
# Last Update: 13 May 2014
# [R]

rm( list = objects() )

c1 <- try( system('which most', intern = TRUE ) )
if( ! is.na( c1[1] ) ) { options( pager = c1 ) }
rm( c1 )

# to see help for reserved words (ex. function): ?'function'

par( family = 'Times' )

library( RColorBrewer )
#library( MASS )
#library( Hmisc )

# Sets the number of columns of the R output to the number of columns
# available
wideScreen <- function( howWide = Sys.getenv( "COLUMNS" ) )
{
  options( width = as.integer( howWide ) )
}

colors = brewer.pal( 5, 'Spectral' )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  library(psych)

  statistics = read.table(
    paste(
      'status.txt',
      sep = ' '
    )
  )

  statistics_vazio = describe(
    statistics,
    skew = FALSE
  )
  
  cat("\nNumero de sitios vazios:\n")
  
  statistics_vazio
  