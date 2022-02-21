pchSet <- function(){
    c(15,16,17,4,6,8,5,0,1,2,3,12,10,18)
}

plotWindow <- function(data,xlab,ylab,legend,legendCol){
    
}


bplot <- function(d,fname,
                  mar=c(5,2,2,1),
                  ylim=c(0,max(d)*1.2),
                  xaxt_at=NA,yaxt_at=NA,
                  xaxt_labels=NA,yaxt_labels=NA,
                  xlab='xlab',ylab='ylab',
                  height=800,width=800,
                  beside=is.matrix(d),
                  col='Grey',
                  names.arg=1:length(d)[1]
                 ){
    par(mar=mar)
    png(paste(fname,'.png',sep=''),height=height,width=width)
    
    bars <- barplot(d,beside=beside,col=col,ylim=ylim)
    
    if(!is.na(xaxt_at))
        axis(side=1,labels=xaxt_labels,at=bars[xaxt_at])
    if(!is.na(yaxt_at))
        axis(side=2,labels=yaxt_labels,at=bars[yaxt_at])
    mtext(side=1,text=xlab,line=3,cex=3)
    mtext(side=2,text=ylab,line=2,cex=2.5)
    
    dev.off()
}

heatmap_R <- function(d){
    nRow <- dim(d)[1]
    heatmap(d[nRow:1,],Rowv=NA, Colv=NA) #Reverse rows to make heatmap follow matrix coordinates
}





#Rectangle plots
r <- function(x,y,h=1,w=1,col='Grey',b=FALSE){
    polygon(x=c(x,x+w,x+w,x),y=c(y,y,y+h,y+h),col=col,border=b)
}

sheet <- function(h=100,w=100){
    par(mar=c(1,1,1,1))
    plot(1:2,1:2,type='n',ylim=c(h,0),xlim=c(0,w),xaxt='n',yaxt='n',main='')
}