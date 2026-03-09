# Symbolic Math Optimizer [SMO]

**Symbolic Math Optimizer *(SMO)*** is a lightweight C++ library meant for both symbolic math (making it a simple CAS) to be used for
optmization routines (like line search, section based search etc.) so that when derivatives are required in that, you don't need
to auto calculate them. They'll be automatically calculated for you.

## Running Tests

So, some few test cases deomonstrating how to use this library are provided in the `test/` directory. To visualize the computation
graph of a `symbolic::expr`, the demo shows how to create a dot file, which works on windows and linux both (tested!).
After creating a dot file, the command to get output image from that is:

```
dot -Tpng /path/to/dot -o /path/to/output
```

This requires you to install the `graphviz` toolkit available for both windows and linux. 
Link to GraphViz: <a href="https://graphviz.org/download/">Here</a>
