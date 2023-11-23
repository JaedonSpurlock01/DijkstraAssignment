<h1 align="center">CS311 Group Assignment 8 </h1>

## Description

This practical program is used to find the shortest route between cities using a graph data structure

- city.txt -- It contains info of 20 cities with 5 columns: ID, City_Code(2 letters), City_Name, Population, and Elevation.
- road.txt -- It contains 3 columns: From_City, To_City, and Distance. Note that each road is one-directional from the from_city to the to_city, and the distances are not supposed to realistic.

The executable should be called `prog8` and run with two command-line arguments. The first argument is the two-letter code of the from_city and the second argument is the code of the to_city. For example:

```
./prog8 AN BK
```

When the program runs, it should first print out your group names and the info about the two cities, for example:

```
Author: xxxxxx and xxxxxxx
Date: xx/xx/20xx
Course: CS311 (Data structures and Algorithms)
Description : Program to find the shortest route between cities
----------------------------------------------------------------
From City: ANAHEIM, population 1273000, elevation 310
To City: BAKERSFIELD, population 31100, elevation 390
```

Then it prints out the shortest route, for example:

```
The shortest distance from ANAHEIM to BAKERSFIELD is 225
through the route: ANAHEIM->VICTORVILLE->CHINO->GRPVE->ISABELLA->BAKERSFIELD
```

If the input city code dosen't exist, the program should exit and print out an error message, for example

```
Invalid city code: AA
```

If there is not a path between two cities, it should print out

```
No route from WRIGHTWOOD to KERNVILLE
```

## Code Report

Check out how this program was made: [LINK]
