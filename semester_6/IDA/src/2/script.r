#!/usr/bin/Rscript

dataframe = read.csv("/home/alex/Documents/Yandex.Disk/files/Work/University/Activity/IDA/datasets/accepted/2019_converted.csv")

print("Корреляция Пирсона.")
print(cor(dataframe, method='pearson'))

print("Корреляция Спирмена.")
print(cor(dataframe, method='spearman'))
