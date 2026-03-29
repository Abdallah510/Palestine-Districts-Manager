# Palestine Districts Manager — C

A menu-driven C application. It manages a two-level hierarchy of Palestinian districts and their towns, loaded from a file and sorted using Radix Sort.

## How It Was Made

Written in C using doubly linked lists. Each district is a linked list head node, and its towns are stored as nodes in that list. Districts are sorted alphabetically using a character-bucket Radix Sort implemented manually with an auxiliary radix array. Towns are sorted by population using Bubble Sort. All data is read from and written to plain text files.

## Features

- Load district and town data from an input file (`districts.txt`)
- Sort districts alphabetically using Radix Sort
- Sort towns within each district by population in ascending order
- Add or delete districts and towns
- Change the population of a town
- Calculate total population of Palestine and find the min/max town by population
- Print full sorted data or a summary view (districts and totals only)
- Save results to an output file (`sorted_districts.txt`)

