install.packages("googleshe1ets4")
install.packages("googledrive")
library(googlesheets4)
library(googledrive)

dades <- read_sheet("https://docs.google.com/spreadsheets/d/1Qv4TBDlyTJZ9ELlzZpUZQ2tVwxMFgDgEgQ82ep8bLAo/edit#gid=0")
dades


Preu <- dades$Preu
Capa <-dades$Capacitat 
Prov <- dades$Proveïdor
n <- 26
G1 <- dades[which(dades$Proveïdor == 1), ]
G2 <- dades[which(dades$Proveïdor == 2), ]
G3 <- dades[which(dades$Proveïdor == 3), ]

summary(lm(Preu~Capa))

new <- data.frame("Capa"=650)
predict(lm(Preu~Capa),new,int="prediction")

mean(G1$Capacitat)
mean(G2$Capacitat)
mean(G3$Capacitat)

t.test(G1$Preu,G3$Preu,var.equal = F)
