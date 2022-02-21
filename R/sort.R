
#Sort a vector and get sorted indices of the vector (what order it was in orginally)
sortAndIndex <- function(v,decreasing=FALSE){
    idx <- order(v,decreasing=decreasing)
    v <- v[idx]
    return(list(v,idx))
}