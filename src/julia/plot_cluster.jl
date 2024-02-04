using Plots
using CSV
using DataFrames


df = CSV.File("D:\\DEVEL\\Development_Datasets\\Mall_Customers.csv") |> DataFrame
scatter(df[!, 4], df[!, 5], 
        xlabel="Annual income (k\$)", 
        ylabel="Spending Score (1-100)",
        title="Scatterplot of spending (y) vs income (x)")

println(pwd())
# After clustering
df2 = CSV.File(".\\output\\output.csv") |> DataFrame
scatter(df2.x, df2.y, group=df2.c, 
        xlabel="Annual income (k\$)", 
        ylabel="Spending Score (1-100)",
        title="Clustered: spending (y) vs income (x)",
        palette=:auto)