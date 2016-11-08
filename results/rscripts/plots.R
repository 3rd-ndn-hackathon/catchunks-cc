library(ggplot2)
library(gridExtra)
library(reshape2)
library(extrafont)

brewer.palette <- "Set1"
ggplot <- function(...) ggplot2::ggplot(...) + scale_color_brewer(palette=paste(brewer.palette))


setwd("/home/klaus/git/ndn_2016/hackathon_3/code")


folder <- "../measurements/"

scen <- "scen9"

cwnd <- read.table(paste(folder,scen,"_cwnd.txt",sep=""), header=T)
rtt <- read.table(paste(folder,scen,"_rtt.txt",sep=""), header=T)
rate <- read.table(paste(folder,scen,"_rate.txt",sep=""), header=T)


summary(cwnd)
summary(rtt)
summary(rate)

rtt.melt <- melt(rtt, id=c('time','segment'))

summary(rtt.melt)

g.cwnd <- ggplot(cwnd, aes (x=time, y=cwndsize)) +
  geom_line(size=0.8) + 
  ylab("Cwnd [Pkts]") +
  labs(type='custom text') 
g.cwnd

g.rate <- ggplot(rate, aes (x=time, y=kbps/1000)) +
  geom_line(size=0.8) + 
  ylab("Rate [Mbit/s]") +
  ylim(0,50) +
  labs(type='custom text') 
g.rate


g.rtt <- ggplot(rtt.melt, aes (x=time, y=value, color=variable)) +
  geom_line(size=0.8) + 
  ylab("RTT") +
  xlab("") +
  labs(type='custom text')  + theme(legend.position="top")
g.rtt



pdfwidth <- 7


pdf(paste("../graphs/",scen,"1.pdf",sep=""), useDingbats=F, height=4, width=pdfwidth)
grid.arrange(g.rate, g.cwnd)
dev.off()

pdf(paste("../graphs/",scen,"2.pdf",sep=""), useDingbats=F, height=4, width=pdfwidth)
g.rtt
dev.off()


g.rtt



