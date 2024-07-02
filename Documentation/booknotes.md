# The Parts of a language:
. Scanning - takes the stream of all characters from the code file and chunks them into 'tokens', words essentially that individually have meaning in our language

. Parser - this understands the structure of the language and it has to as its job is to take the tokens made from scanning and organize them into a tree that reflects the nested nature of whatever 'grammar', aka. rules, we employ in our language. This is called a syntax tree. As a parser understands the syntax of our language, this is where the interpreter will catch syntax errors

. Static Analysis -  a few things occur here: determine scope declared variables; connect the name of said variables to their declarations; type checking of said variables; storage of this collected data (usually stored in syntax tree, symbol chart, or creation of a new tree that represents this)

## Apparently, the steps up till now are considered the front-end of implementation

. Intermediate Representation - I don't this this is relevant to our project as we are strictly interpreting to be compiled in one language 'C' and this step is about translating everything up till now into a more 'platform agnostic' format

. Optimization - this step takes the written code and alters it at compile time to make the execution faster (ex: user makes a variable equal to an expression and we solve said expression in this step and reassign the variable to the solution)

. Code Generation - this step converts the code into an executable or bytecode that a VM(Virtual Machine) can read. I believe that we are going the executable route as translating the code into C which produces an executable seems straightforward enough

. VM - Putting this here in case we go this route. To circle back to Code generation, if we go down the route of generating an executable, I think that the biggest thing here is that we will have to write our script to generate an executable for Windows vs Unix as it has a different c compiler from macOS and Linux

. Runtime - Services that occur during the life of the execution like garbage collection
