# hls
Probelm:
The input to our problem is:
 
 1. The network graph as a DAG. Each node is an operator connected by single direction edges.
  
  2. Depending on the operator type, each operator/node v can have k(v) choices. Each choice is
  associated with a known delay delay(v[k]) and area cost(v[k]) where 0 <= k <= k(v)- 1. The edges
  have 0 delays. Generally, the shorter delay is associated with larger area cost.
   
   3. The length of a path is defined as the accumulated delays of operators along the path.
    
    4. Initially all operators are implemented with a default choice. It is known the initial longest
    path exceeds target p (for example, clock period)
     
     The goal is to find a solution that chooses the operator implementations such that
      
      1. The longest path is less than or equal to p
       
       2. The total network cost is minimal, or the accumulative cost of all operators is minimal
        
	Notes: v[k] is normally small (< 10). DAG can be large and in the range of thousands.
	 
	 The number of operator types (add, mult, shift, etc.) is relatively small (<20). For each type of operator (e.g., add operator) the number of choices is a constant, which is small (<10). For example,
	  
	                                  # of choices
					  ---------------------------------------
					  Add                        3
					  Mult                      6
					  Shift                       3
					   
					   For each operator choice, we have a constant delay and area. The lower the delay is, the higher the area is.
					   For example we can have 3 architecture choices for add operator, add_c1, add_c2, add_c3. Area of them are 1, 2, 4. And delay of them are 3, 2, 1.
					   The goal is to have the most critical paths <= clock_period while minimize the total area cost of all operators.
					    
					    You can choose any format for importing DAG, operator costs, timing constraints, etc. You can give both the optimal solution and approximate solution for better runtime.  You can choose to program just one solution. DAG graph can be in the range of thousand nodes. For demonstration you just need to show the result on a small graph.

1. This approach takes advantage of simulated annealing algorithm.
	(1) initially, every cell take the option with the shortest delay and the largest area
	(2) check if it is possible to achieve the assign clock period in this extreme condition.
	(3) randomly select cell to try other options, if the new option violates the clock period, drop it. if not and make the total area decrease, take it. if the area increase, check the possibility comparison of this simlated annealing algorithm to decide if this option to be taken. loop this step a certain amount of times.
	(4) after the loop, check if the area is decreaing, if yes, decrease temperature parameter. otherwise, stop.

This approach is heuristic, will get a good result, but will not get the optimal solution.

2. Implementation is attached. graph.txt is input file, first line describe the size of the graph and clock period. Second line is the type of operation. 0: adder, 1: shifter, 2: multiplier. other lines are the edges, eg 2 3, there is a edge from 2 to 3 with direction. result.txt is the result of this small example. a.out is executable, which is compiled under c++11 by using gcc compiler.

3. potential improvement: 
	(1) should have better way to decide the temperature parameter and to decide when to decrease the temperature. 
	(2) when choosing cell, we just randomly choose the cell. Take advantage previous info and neighor info will improve the result.
