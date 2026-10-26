# Graph diagrams for tests 01–05

All edges are undirected. Edge labels preserve the input edge number and weight.

## `test01.uwg`

- Vertices: `4`
- Edges: `2`
- M: `5`

```mermaid
graph LR
    v1((1))
    v2((2))
    v3((3))
    v4((4))
    v1 ---|e1: w = 1| v2
    v2 ---|e2: w = 5| v3
```

## `test02.uwg`

- Vertices: `4`
- Edges: `4`
- M: `10`

```mermaid
graph LR
    v1((1))
    v2((2))
    v3((3))
    v4((4))
    v1 ---|e1: w = 7| v2
    v2 ---|e2: w = 6| v4
    v1 ---|e3: w = 2| v3
    v3 ---|e4: w = 7| v4
```

## `test03.uwg`

- Vertices: `10`
- Edges: `10`
- M: `50`

```mermaid
graph LR
    v1((1))
    v2((2))
    v3((3))
    v4((4))
    v5((5))
    v6((6))
    v7((7))
    v8((8))
    v9((9))
    v10((10))
    v6 ---|e1: w = 40| v9
    v5 ---|e2: w = 38| v7
    v1 ---|e3: w = 37| v4
    v1 ---|e4: w = 26| v9
    v8 ---|e5: w = 20| v10
    v5 ---|e6: w = 23| v8
    v9 ---|e7: w = 24| v10
    v1 ---|e8: w = 27| v7
    v4 ---|e9: w = 31| v5
    v5 ---|e10: w = 39| v6
```
