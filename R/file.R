mkdir <- function(path){
    dir.create(path,recursive=TRUE,showWarnings=FALSE)
}

#Make a folder for a file name (remove file name if necessary)
mkdirFor <- function(path){
    RV <- gregexpr(pattern='/',text=path) #Find locations of '/'
    idx <- RV[[1]]
    path <- substr(x=path,start=0,stop=idx[length(idx)]) #Go from start to last '/'
    mkdir(path)
}