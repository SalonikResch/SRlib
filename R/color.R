
colTransparent <- function(col,alpha){
    v <- col2rgb(col)
    rgb(red=v[1],green=v[2],blue=v[3],alpha=alpha,maxColorValue=255)
}

colorSet <- function(){
    col <- c(
        colTransparent('Red',0.5),
        colTransparent('Blue',0.75),
        colTransparent('Green',0.3),
        colTransparent('Grey',0.8),
        colTransparent('Purple',0.2)
    )
    col <- c('Red','Blue','Green','Grey','Purple')
}

colorSet2 <- function(){
    c(rgb(255, 225, 25,maxColorValue=255), rgb(0, 130, 200,maxColorValue=255), rgb(245, 130, 48,maxColorValue=255), 
      rgb(220, 190, 255,maxColorValue=255), rgb(128, 0, 0,maxColorValue=255), rgb(0, 0, 128,maxColorValue=255), 
      rgb(128, 128, 128,maxColorValue=255), rgb(255, 255, 255,maxColorValue=255), rgb(0, 0, 0,maxColorValue=255) )
}