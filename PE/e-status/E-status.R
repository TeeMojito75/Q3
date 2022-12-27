install.packages("googlesheets4")
install.packages("googledrive")
install.packages("emmeans")
install.packages("mvtnorm")
library(googlesheets4)
library(googledrive)

dades <- read_sheet("https://docs.google.com/spreadsheets/d/1Qv4TBDlyTJZ9ELlzZpUZQ2tVwxMFgDgEgQ82ep8bLAo/edit#gid=0")

S15 <-  dades[which(dades$seg == 15), ]
S20 <-  dades[which(dades$seg == 20), ]
S25 <-  dades[which(dades$seg == 25), ]
S30 <-  dades[which(dades$seg == 30), ]
S35 <-  dades[which(dades$seg == 35), ]
S40 <-  dades[which(dades$seg == 40), ]
S45 <-  dades[which(dades$seg == 45), ]
S50 <-  dades[which(dades$seg == 50), ]
S55 <-  dades[which(dades$seg == 55), ]
S60 <-  dades[which(dades$seg == 60), ]
