#!/usr/bin/Rscript

library(plotrix)
 
x <- c(210, 450, 250, 100, 50, 90)
names(x) <- c("Algo", "DS", "Java", "C", "C++", "Python")
 
svg("output.svg")
par(mfrow=c(2, 2))

# столбчатая диаграмма
barplot(x, xlab = "Языки программирования", ylab = "Популярность", col = "white")

# прямоугольная диаграмма
boxplot(x, xlab = "Языки программирования", ylab = "Популярность")

# круговая диаграмма
pie(x, labels = names(x), col = "white")

# круговая 3D диаграмма
pie3D(x, labels = names(x), col = "white")
 
dev.off()
