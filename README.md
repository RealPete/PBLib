# PBLib -- A C++ Toolkit for Encoding Pseudo-Boolean Constraints into CNF
Many different encodings for Pseudo-Boolean (PB) constraints into conjunctive normal form (CNF) have been proposed in the past. The PBLib project starts to collect and implement these encodings to be able to encode PB constraints in a very simple, but effective way. The aim is not only to generate as few clauses as possible, but also using encodings that maintain generalized arc consistency by unit propagation, to speedup the run time of the SAT solver, solving the formula.

A major issue of the implementation is a high flexibility for the user. Consequently it is not required to bring a PB constraint into a certain normal form. The PBLib automatically normalizes the constraints and decides which encoder provides the most effective translation.

The user can also define constraints with two comparators (less equal and greater equal) and each PB constraint can be encoded in an incremental way: After an initial encoding it is possible to add a tighter bound with only a few additional clauses. This mechanism allows the user to develop SAT-based solvers for optimization problems with incremental strengthening and to keep the learned clauses for incremental SAT solver calls. 
### Implemented encodings

| At most one | At most K | PB |
| --- | --- | --- |
| sequential* |  BDD** | BDD |
| bimander | cardinality networks | adder networks |
| commander | adder networks | watchdog |
| k-product | | sorting networks |
| binary |  | binary merge |
| pairwise |  | sequential weight counter |
| nested |  |  | |

\* equivalent to BDD, latter and regular encoding
** equivalent to sequential counter

### Simple Example
Include the PBLib with "#include <pblib/PB2CNF.h>" and create an instance of the PB2CNF class:
`   PB2CNF pb2cnf;`
 And now we can start to encode a PBConstraint with the following c++ code:
 
       vector< int64_t > weights = {3,-2,7};
       vector< int32_t > literals = {-1,-2,3};
       vector< vector< int32_t > > formula;
       int32_t firstFreshVariable = 4;
       firstFreshVariable = pb2cnf.encodeGeq(weights, literals, -4, formula, firstFreshVariable) + 1;

If you only need a simple At-Most-k constraint you can use the following code (in this example at most 2 literals are true):

	   vector< int32_t > literals = {-1,-2,3};
	   vector< vector< int32_t > > formula;
	   int32_t firstFreshVariable = 4;
	   int k = 2;
	   firstFreshVariable = pb2cnf.encodeAtMostK(literals, k, formula, firstFreshVariable) + 1;

### Example Iterative Constraints

You can also add a less then or equal AND a greater then or equal comparator, as well as incremental constraints. For the later one we need the additional class ClauseDatabase (the generic formula container) and the AuxVarManager which takes care of the fresh variables and we will also use the config class of the PBLib:

	   using namespace PBLib;  
	   PBConfig config = make_shared< PBConfigClass >();
	   VectorClauseDatabase formula(config);
	   PB2CNF pb2cnf(config);
	   AuxVarManager auxvars(11);

	   vector< WeightedLit > literals 

	   {WeightedLit(1,-7), WeightedLit(-2,5), WeightedLit(-3,9), WeightedLit(-10,-3), WeightedLit(10,7)};

	   IncPBConstraint constraint(literals, BOTH, 100, -5);

	   pb2cnf.encodeIncInital(constraint, formula, auxvars);

This encodes the constraint:

$-5 \leq -7 x_1 + 5\overline{x_2} +9 \overline{x_3} -3 \overline{x_{10}} +7 x_{10} \leq 100 $

After adding more constraints and solve the formula with a SAT solver we can encode new bounds based on the previous constraint encoding:

	   constraint.encodeNewGeq(3, formula, auxvars);
	   constraint.encodeNewLeq(8, formula, auxvars);

This will - in combination with the formula encoded with encodeIncInital - encode the following constraint:

$-3 \leq -7 x_1 + 5\overline{x_2} +9 \overline{x_3} -3 \overline{x_{10}} +7 x_{10} \leq 8 $

### More Features

Besides the VectorClauseDatabase you can implement your own ClauseDatabase containers. There are already a CountingClauseDatabase, which only counts the number of generated clauses, and a SATSolverClauseDatabase, which directly add the generated clauses into a MiniSAT like SAT solver (therefor you have to include your SATsolver as a library).

You can add conditionals to each constraint (also to incremental constraints!), e.g.:

$(x_5 \land \overline{x_6}) \rightarrow (-3 \leq -7 x_1 + 5\overline{x_2} +9 \overline{x_3} -3 \overline{x_{10}} +7 x_{10} \leq 8) $

Simply add the to your instance of the class PBConstraint (or IncPBConstraint):

	   constraint.addConditional(5);
	   constraint.addConditional(-6);


There is no specific normal form necessary. Internally the PBlib automatically transform any PBConstraint into a specific normal form an applies various simplifications like merging multiple variable occurrences, detecting internally if the constraint is a at-most-one constraint, at-least-k constraint or a "real" PBConstraint and apply a appropriate encoder to it and much more.

With the PBConfig instance you have lots of options to customize the encoding at your specific needs.

And everything is free, open source and under the MIT license. So please do me a favor and cite this work where ever you use it and I would appreciate if you send me a short E-Mail so that I can cite you as well as an application for the PBLib.

### How to cite the pblib?

	@incollection{pblib.sat2015
		year={2015},
		isbn={978-3-319-24317-7},
		booktitle={Theory and Applications of Satisfiability Testing -- SAT 2015},
		volume={9340},
		series={Lecture Notes in Computer Science},
		editor={Heule, Marijn and Weaver, Sean},
		doi={10.1007/978-3-319-24318-4_2},
		title={PBLib -- A Library for Encoding Pseudo-Boolean Constraints into CNF},
		publisher={Springer International Publishing},
		author={Philipp, Tobias and Steinke, Peter},
		pages={9-16}
	}

### PB encoder
The PBLib also includes a PBEncoder which takes an opb input file and translate it into CNF using the PBLib: usage ./pbencoder inputfile

### Example PB Solver
The PBLib contains a folder BasicPBSolver with the implementations of an example PB Solver. It uses minisat 2.2 as a backend SAT solver. usage ./pbsolver inputfile 

### How to Compile

You will need at least a C++ compiler that supports the C++11
standard. Default compiler is g++. To change this edit the
CMakeLists.txt file.

    cmake .
    make



To compile also the basic PB solver and minisat zlib is need. Debain based systems can install this with the following command:

	apt-get install zlib1g-dev

To compile both use

	cmake .
	make setup
