#!/usr/bin/Rscript

svg("output.svg")

# Присвоение x вектора чисел от 1 до 10
x <- c(1:10)
y <- x

# Создать новый вектор путём деления 10 на каждый элемент вектора x
z <- 10/x

# Задать параметры для графика
opar <- par(no.readonly=TRUE)
par(mar=c(5, 4, 4, 8) + 0.1)

# построить график на основе x, y с использованием точек и линий, основной
# цвет - красный
plot(x, y, type="b", pch=21, col="red", yaxt="n", lty=3, ann=FALSE)

# добавить график к текущее окно на основе данных x и z, цвет точек и линий
# синий 
lines(x, z, type="b", pch=22, col="blue", lty=2)

# добавить оси к текущему графику
axis(2, at=x, labels=x, col.axis="red", las=2)
axis(4, at=z, labels=round(z, digits=2), col.axis="blue", las=2, cex.axis=0.7, tck=-.01)

# добавить подпись синего цвета справа от графика
mtext("y=1/x", side=4, line=3, cex.lab=1, las=2, col="blue")

# добавить название текущему графику, подписи осям абсцисс и ординат
title("Пример осей", xlab="значение переменной X", ylab="Y=X")


dev.off()
