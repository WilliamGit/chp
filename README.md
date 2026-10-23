# Course Project - 02249 Computationally Hard Problems

## Description

This repository contains a C++ implementation of the optimization problem for the Weight Balance Path (WBP) problem.

### WeightBalancePath (WBP)

#### (Decision Problem)

**Input:** An undirected, weighted graph $G = (V, E, w)$, where $V = \{1, 2, \dots n\}$,
$E = \{e_1, e_2, \dots e_m\}$ and $w : E \rightarrow \mathbb{N}_0$, a number $M \in N$ and
a number $B \in \mathbb{N}_0$, such that $w(e) \le M$ for every $e \in E$.

**Output:**

- *YES* if there is a simple path $P \subseteq E$ from vertex $1$ to vertex $n$ such that:

    $ max \left\{\ \sum_{e \in P}{w(e),\ \sum_{e \in P}(M - w(e))} \ \right\} \le B \ \ \ \ \ (1)$

- *NO* if there is no such path.

#### (Optimization Problem)

Given the same input as the decision problem but without $B$, the algorithm should 
find the simple path $P$ from $1$ to $n$ which satisfies inequality $(1)$ for the smallest right-side value ($B$) possible, or anwer *NO* if no such path exists.

### Implementation

<TODO_Implementation_Description>

## How-to-run

- On Unix, run `make all` in the current directory to build the project and the final executable `wb-path` is created.

- You can use the executable like so:

    ```bash
    ./wb-path <test-file>
    ```
