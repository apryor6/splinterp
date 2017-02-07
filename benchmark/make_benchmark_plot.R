setwd(".")
library(ggplot2)
library(dplyr)
library(tidyr)
df <- read.csv("benchmark_data.csv",col.names=c("N","interp2","splinterp2"))
df <- gather(df,key=time,value=value,2:3)
ggplot(data=df,aes(x=N,y=value, color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1)

ggplot(data=df,aes(x=N^2,y=log(value), color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position = "right") + 
  #theme(legend.position = c(.835,.85)) + 
  labs(title="2D to 1D Bilinear Interpolation Benchmark\n(i7-6800k, 12 threads)", y="Log Time (s)", x="N")

ggplot(data=df,aes(x=N^2,y=(value), color=time)) +
  geom_line(aes(group=time)) + 
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position = "right") + 
  #theme(legend.position = c(.835,.85)) + 
  labs(title="2D to 1D Bilinear Interpolation Benchmark\n(i7-6800k, 12 threads)", y="Time (s)", x="N")

df <- read.csv("benchmark_data.csv",col.names=c("N","interp2","splinterp2"))
df$ratio = df$interp2 / df$splinterp2
ggplot(data=df,aes(x=N^2,y=(ratio))) +
  scale_colour_brewer(type = "qual", palette = 6, direction = 1, labels=c("MATLAB interp2","C++ splinterp2")) + 
  theme(legend.position = "right") + 
  #theme(legend.position = c(.835,.85)) + 
  labs(title="Relative Speedup", y="Ratio", x="N")
