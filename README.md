Interesting-Algorithms
======================

Non trivial Algorithms usually taught in Junior Senior year Algorithm Classes.

Current Contents

* strassen.cpp
    Strassens Algorithm for matrix multiplication which has time complexity of O(n^2.7)
    - Compiling Instructions
         g++ -I/<ogdfsnapshot PATH>/OGDF-snapshot/include -L/<ogdfsnapshot PATH>/OGDF-snapshot/_release ./strassen.cpp -o strassen -lOGDF -lCOIN -pthread
    - Note : You need to have ogdf installed for this.

    
* dynamicKnapsack.cpp
    Soluition to the Binary Knapsack problem using dynamic approach.
    - Compiling Instructions
        g++ dynamicKnapsack.cpp -o dynamicKnapsack
 
