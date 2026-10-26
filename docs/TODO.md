# Dijkstra and WBP Fixes

- [x] Fix path reconstruction termination.
  - Pass `v_start` to `constructPath()`.
  - Stop when `current == v_start`.
  - Never call `getEdges(-1)`.

- [x] Store the exact predecessor edge.
  - Replace `vector<int> prev` with something that records the complete `Edge` or its index.
  - Reconstruct the path using those stored edges.
  - Ensure parallel edges are handled correctly.

- [x] Represent the graph as undirected.
  - Add an adjacency entry for both `v1 -> v2` and `v2 -> v1`.
  - Give both entries the same original input-edge index.
  - Increment the graph's edge count only once per input edge.

- [ ] Prevent integer overflow.
  - Change edge weights, queue scores, path sums, and `INF` to `std::int64_t`.
  - Use `std::numeric_limits<std::int64_t>::max()`.
  - Guard additions involving `INF`.

- [ ] Handle stale priority-queue entries.
  - Pop the complete `QueueEntry`.
  - Skip it when its recorded score differs from the current best score.
  - Check for the target only after discarding stale entries.

- [ ] Clean up the Dijkstra interface.
  - Remove the unused `M` parameter when this function only minimizes edge weights.
  - Consider renaming it to `searchDijkstra()` while its heuristic is always zero.

- [ ] Test ordinary Dijkstra correctness.
  - Reachable target with one path.
  - Multiple paths with different total weights.
  - A path requiring traversal opposite an input edge's written direction.
  - Parallel edges.
  - Disconnected target.
  - Large weights exceeding 32-bit path totals.

- [ ] Run sanitizers.
  - Compile with AddressSanitizer and UndefinedBehaviorSanitizer.
  - Run all files in `test/`.
  - Confirm there are no out-of-bounds accesses or signed overflows.

- [ ] Keep Dijkstra separate from the WBP solver.
  - Document that Dijkstra minimizes only `sum(w)`.
  - Do not treat the resulting path as the optimal WBP path.
  - Design the WBP search around the complete objective:

    $$
    \max\left(\sum w(e), \sum(M-w(e))\right).
    $$

- [ ] Restore evaluator output after debugging.
  - Switch from `printDebug()` back to `printAnswer()`.
  - Verify the expected executable name and input/output format.
