# The Norm

### Forbidden stuff!
	You’re not allowed to use:
	◦ for
	◦ do...while
	◦ switch
	◦ case
	◦ goto
	Ternary operators such as ‘?’.
	VLAs - Variable Length Arrays.
	Implicit type in variable declarations
	Non const static global variables.

###  Denomination
	A structure’s name must start by s_.
	A typedef’s name must start by t_.
	A union’s name must start by u_.
	An enum’s name must start by e_.
	A global’s name must start by g_.
	Variables and functions names can only contain lowercases, digits and ’_’ (UnixCase).
	Files and directories names can only contain lowercases, digits and ’_’ (Unix Case).
	Characters that aren’t part of the standard ASCII table are forbidden.
	Variables, functions, and any other identifier must use snake case.
	All identifiers (functions, macros, types, variables, etc.) must be in English.
	Using global variables that are not marked const and static is forbidden and is
		considered a norm error, unless the project explicitly allows them.

### Formatting
	One instruction per line!
	You must indent your code with 4-space tabulations. This is not the same as 4
		average spaces, we’re talking about real tabulations here.
	Each function must be maximum 25 lines, not counting the function’s own curly
		brackets.
	Each line must be at most 80 columns wide, comments included. Warning: a
		tabulation doesn’t count as a column, but as the number of spaces it represents.
	Each function must be separated by a newline.
	An empty line must be empty: no spaces or tabulations.
	A line can never end with spaces or tabulations.
	You can never have two consecutive spaces.
	You need to start a new line after each curly bracket or end of control structure.
	Unless it’s the end of a line, each comma or semi-colon must be followed by a space.
	Each operator or operand must be separated by one - and only one - space.
	Each C keyword must be followed by a space, except for keywords for types (such
		as int, char, float, etc.), as well as sizeof.
	Each variable declaration must be indented on the same column for its scope.
	The asterisks that go with pointers must be stuck to variable names.
	One single variable declaration per line.
	Declaration and an initialisation cannot be on the same line, except for global
		variables (when allowed), static variables, and constants.
	Declarations must be at the beginning of a function.
	In a function, you must place an empty line between variable declarations and the
		remaining of the function. No other empty lines are allowed in a function.
	Multiple assignments are strictly forbidden.
	You may add a new line after an instruction or control structure, but you’ll have
		to add an indentation with brackets or assignment operator. Operators must be at
			the beginning of a line.
	Control structures (if, while..) must have braces, unless they contain a single line
		or a single condition.


### Functions
	A function can take 4 named parameters maximum.
	A function that doesn’t take arguments must be explicitly prototyped with the
		word "void" as the argument.
	Parameters in functions’ prototypes must be named.
	Each function must be separated from the next by an empty line.
	You can’t declare more than 5 variables per function.
	Return of a function has to be between parenthesis.
	Each function must have a single tabulation between its return type and its name.

### Typedef, struct, enum and union
	Add a tabulation when declaring a struct, enum or union.
	When declaring a variable of type struct, enum or union, add a single space in the
		type.
	When declaring a struct, union or enum with a typedef, all indentation rules apply.
	You must align the typedef’s name with the struct/union/enum’s name.
	You must indent all structures’ names on the same column for their scope.
	You cannot declare a structure in a .c file.


### Headers
	The things allowed in header files are: header inclusions (system or not),
		declarations, defines, prototypes and macros.
	All includes must be at the beginning of the file.
	You cannot include a C file.
	Header files must be protected from double inclusions. If the file is ft_foo.h, its
		bystander macro is FT_FOO_H.
	Unused header inclusions (.h) are forbidden.
	All header inclusions must be justified in a .c file as well as in a .h file.

###	Macros and Pre-processors
	Preprocessor constants (or #define) you create must be used only for literal and
		constant values.
	All #define created to bypass the norm and/or obfuscate code are forbidden. This
		part must be checked by a human.
	You can use macros available in standard libraries, only if those ones are allowed
		in the scope of the given project.
	Multiline macros are forbidden.
	Macro names must be all uppercase.
	You must indent characters following #if, #ifdef or #ifndef.

### Files
	You cannot include a .c file.
	You cannot have more than 5 function-definitions in a .c file.
