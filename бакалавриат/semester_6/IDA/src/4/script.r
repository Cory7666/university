.cluster <-  KMeans(model.matrix(~-1 + freedom_to_make_life_choices + gdp_per_capita + generosity + healthy_life_expectancy + perceptions_of_corruption + score + social_support, Dataset), centers = 2, iter.max = 10, num.seeds = 10)
.cluster$size # Cluster Sizes
.cluster$tot.withinss # Total Within Sum of Squares
.cluster$betweenss # Between Cluster Sum of Squares
