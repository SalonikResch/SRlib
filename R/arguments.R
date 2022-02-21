

getArgs <- function(){
    args = commandArgs(trailingOnly=TRUE)
    if(length(args) > 0)
        arg <- as.integer(args[1])
    return(arg)
}

#Convert integer index to many indices (assume from 0)
#idx = single integer index
#lengths = the length (modulus) of the different indices
int2ints <- function(idx,lengths){
    indices <- rep(NA,length(lengths))  #Indices to return
    len <- 1              #Current length to divide by
    for(i in 1:length(lengths)){
        indices[i] <- floor(idx/len) %% lengths[i]
        len <- len * lengths[i]
    }
    return(indices)
}