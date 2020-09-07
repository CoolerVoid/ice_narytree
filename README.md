# ice n-ary tree C library
ICE narytree is a Open Source C library to help in n-ary tree creation and work(traversal, search, create nodes, insert childs/siblings, destroy tree).

You can use trees to solve file system problems, static analysis problems,  like recursive tree with N points with childs...
<img align="right" width="240" height="220" src="https://raw.githubusercontent.com/CoolerVoid/icenarytree/master/doc/wide-shot-isolated-tree-covered-snow-snowy-area-just-like-fairytale_181624-5468.jpg">

In computer science, a tree is a widely used abstract data type that simulates a hierarchical tree structure, with a root value and subtrees of children with a parent node, represented as a set of linked nodes. A tree data structure can be defined recursively as a collection of nodes (starting at a root node), where each node is a data structure consisting of a value, together with a list of references to nodes (the "children"), with the constraints that no reference is duplicated, and none points to the root.

<img align="right" width="240" height="220" src="https://upload.wikimedia.org/wikipedia/commons/5/5f/Tree_%28computer_science%29.svg">


First step, understand before run
--

Study the src/main.c to understand how to use...
Study calls to know how to use  lib...  lib/icenarytree.h

any doubts... create issue or send me a e-mail...


Second step, testing!
--


Look this following commands to run:
```
$ git clone https://github.com/CoolerVoid/icenarytree
$ cd icenarytree
$ make
$ ./bin/test_tree
$ cat src/main.c
```



Next resources:
--

* Functions to renderize tree using graphviz library (Its cool to debug the tree).
* Cmake config file to install in system library...
* Insert other functions...


References:
--
https://en.wikipedia.org/wiki/Tree_(data_structure)
https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/ (The best C book)
