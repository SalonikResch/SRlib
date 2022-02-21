library(filelock) 

lWrite <- function(file,data){
    l <- lock(path=file)
    write(x=data,file=file)
    unlock(l)
}
