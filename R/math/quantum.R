
matrixExponential <- function(m,K=100){
    N <- dim(m)[1]
    eX <- diag(N)
    Xk <- m
    for(k in 1:K){
        eX <- eX + 1/factorial(k)*Xk
        Xk <- Xk %*% Xk
    }
    return(eX)
}