#Wrapper for try-catch
tC <- function(f){
    rv <- tryCatch(
        {
            f
        },
        error=function(cond){
            message("Caught error and returning NA")
            message(cond)
            return(NA)
        },
        #warning=function(cond){
        #    message("Caught warning")
        #    message(cond)
        #},
        finally={}
    )
    return(rv)
}