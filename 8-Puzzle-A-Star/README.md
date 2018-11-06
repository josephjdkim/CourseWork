# A* Graph Search (8 Puzzle)
### Background
This is my code for one of Dr. E. K. Wong's projects in his *Artificial Intelligence* course.

### Implementation
My code implements only one class, `State`, which represents a state (or node) of the puzzle in the context of an A\* search algorithm.

A\* is defined by the equation:
>
>*f(n) = g(n) + h(n)* where:
>
>*f(n)* = the evaluation function
>
>*g(n)* = the cost from the start node to the current node
>
>*h(n)* = estimated cost from current node to goal.


The (slightly confusingly named) `.cost` attribute represents *g(n)*. The `.heuristic` attribute represents *h(n)*.

The `.board` attribute represents the configuration of the board, given as a 3x3 matrix.

### Functionality
The script can be run as an executable using the following command:

```
$ ./a-star.py INPUT OUTPUT
```
`INPUT` is the input file, which provides the initial and goal board configurations. It is a necessary argument.

`OUTPUT` is the destination output file, where the solution will be written. It is an optional argument. Absence of the `OUTPUT` argument will make the script default to writing to a file called `output.txt`.
