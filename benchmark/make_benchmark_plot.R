setwd("~/Documents/MATLAB/3d-refine/splinter/benchmark/")
library(ggplot2)
library(dplyr)
library(tidyr)
df <- read.csv("benchmark_data.csv",col.names=c("N","interp2","splinterp2"))
df <- gather(df,key=time,value=value,2:3)
ggplot(data=df,aes(x=N,y=value, color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1)

f<-ggplot(data=df,aes(x=N^2,y=log(value), color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position ="bottom") + 
  #theme(legend.position = c(.835,.85)) + 
  labs(title="2D to 1D Bilinear Interpolation Benchmark\n(i7-6800k, 12 threads)", y="Log Time (s)", x="N")
pdf("log_time.pdf")
print(f)
dev.off()

f<-ggplot(data=df,aes(x=N^2,y=(value), color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position = "bottom") + 
  #theme(legend.position = c(.835,.85)) + 
  labs(title="2D to 1D Bilinear Interpolation Benchmark\n(i7-6800k, 12 threads)", y="Time (s)", x="N")
pdf("linear_time.pdf")
print(f)
dev.off()

df <- read.csv("benchmark_data.csv",col.names=c("N","interp2","splinterp2"))
df$ratioT = df$interp2 / df$splinterp2
f<-ggplot(data=df,aes(x=N^2,y=(ratioT))) +
  geom_line() +
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position = "bottom") + 
  #theme(legend.position = "bottom") + 
  labs(title="Relative Speedup", y="Ratio", x="N")
pdf("ratio.pdf")
print(f)
dev.off()