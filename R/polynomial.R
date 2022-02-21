
#Get polynomial coefficients of a function
polyCoeff <- function(x,y,n=3,print=FALSE){
    r <- lm(y ~ poly(x, n, raw=TRUE))
    c <- as.vector(r$coefficients)
    if(print)
        print(paste(  rev(paste(c,'*x^',1:n-1,sep='')) ,sep=' + '))
    return(c)
}
