<center> <span style="font-size:250%"> Compiler of Simplified C Language</span>  </center> 

<br>
<center> <span style="font-size:180%"> Abstract </span> </center>

This project’s objective is to implement a compiler for a **simplified C language**. This compiler supports the following features: identifiers for **variables** and **functions**; types for **signed integers**, **characters**, and **booleans**; keywords for **true**, **false**, **if**, **else** and **while**; and operators for **comparisons**, **addition**, **subtraction**, **multiplication**, **division**, **unary addition**, and **unary subtraction**.

# **Contents**
1. **Lexical Analyzer**
1. **Syntax Analyzer**
1. **Syntax Tree**
1. **Semantic Analysis**
1. **~~Intermediate Code (TAC - Three Address Code)~~**
1. **~~Code Optimization~~**
1. **~~Code Generation~~**


# **Lexical Analyzer**
The **Lexical Analyzer** takes an input string, splits it into tokens (smallest unit of meaning), and passes each token to the **Syntax Analyzer**.

## **Lexical Rules**
### **Integer**
**Definition** : a sequence of one or more digits

**Regular expression** : (Digit)+

**Examples** : 01, 10, 1234 …



### **Character**
**Definition** : a single character that can be a letter, whitespace, or digit surrounded by single quotes.

**Regular expression** : 'Letter|Digit|WhilteSpace'

**Examples** : '\t', 'p', '5' …


### **Identifier**
**Definition** : a sequence of characters starting with an underscore or a letter, followed by zero or more underscores, letters, or digits.

**Regular expression** : (\_|letter)(\_|letter|digit)\*

**Examples** : _ ,_abc123, abc123_, abc_123_ …


### **Type**
**Definition** : data types: integer, character, and boolean.

**Regular expression** : int | char | bool


### **Boolean**
**Definition** : Boolean values.

**Regular expression** : true | false



### **Keyword**
**Definition** : reserved keywords in the language.

**Regular expression** : if | else | while | return


### **CompOp (Comparison Operator)**
**Regular expression** : == | != | <= | >= | < | >
###
### **LogicOp (Comparison Operator)**
**Regular expression** : | | &

### **UnaryOp**
**Regular expression** : ++ | --

### **AddSub**
**Regular expression** : + | -

### **muldiv**
**Regular expression** : \* | /

### **assign**
**Regular expression** : =

### **semi**
**Regular expression :** ;
### **comma**
**Regular expression :** ,

### **lbrace**
**Regular expression** : {

### **rbrace**
**Regular expression :** }

### **lparen**
**Regular expression :** (

### **rparen**
**Regular expression** : )


# **Syntax Analyzer**
The **Syntax Analyzer** takes a sequence of tokens from the **Lexical Analyzer**, verifies grammar, and constructs a syntax tree. This parser operates based on a CFG(context-free grammar)

## **CFG (Context-Free Grammar)**
### **Symbol Notations:**
- Terminal : PascalCase
- Non-terminal : SNAKE\_CASE
- **ε** : epsilon move

### **Reduction Rules**
S -> CODE

CODE -> FDECL CODE

CODE -> ε

FDECL -> Type Identifier LParen PARAMETER RParen LBrace BLOCK RETURN RBrace

PARAMETER -> Type Identifier MORE\_PARAMETER

PARAMETER -> ε

MORE\_PARAMETER -> Comma Type Identifier MORE\_PARAMETER

MORE\_PARAMETER -> ε

VDECL -> Type Identifier Semi

VDECL -> Type ASSIGN Semi

ASSIGN -> Identifier Assign EXPR

EXPR -> FUNC\_CALL

EXPR -> COND\_EXPR

EXPR -> TERM AddSub EXPR

EXPR -> TERM

TERM -> FACT MulDiv TERM

TERM -> FACT

FACT -> Integer

FACT -> AddSub Integer

FACT -> Character

FACT -> AddSub Character

FACT -> Identifier

FACT -> AddSub Identifier

FACT -> PREFIX\_STMT

FACT -> POSTFIX\_STMT

FACT -> LParen EXPR RParen

BLOCK -> STMT BLOCK

BLOCK -> ε

STMT -> VDECL

STMT -> ASSIGN Semi

STMT -> FUNC\_CALL Semi

STMT -> If LParen COND RParen LBrace BLOCK RBrace ELSE

STMT -> While LParen COND RParen LBrace BLOCK RBrace

STMT -> PREFIX\_STMT Semi

STMT -> POSTFIX\_STMT Semi

PREFIX\_STMT -> UnaryOp Identifier

POSTFIX\_STMT -> Identifier UnaryOp

FUNC\_CALL -> Identifier LParen ARGUMENT RParen

ARGUMENT -> EXPR MORE\_ARGUMENT

ARGUMENT -> ε

MORE\_ARGUMENT -> Comma EXPR MORE\_ARGUMENT

MORE\_ARGUMENT -> ε

COND -> COND\_EXPR LOGIC\_EXPR

COND\_EXPR -> Boolean

COND\_EXPR -> FACT CompOp FACT

LOGIC\_EXPR -> ε

LOGIC\_EXPR -> LogicOp COND

ELSE -> Else LBrace BLOCK RBrace

ELSE -> ε

RETURN -> Return EXPR Semi
### **Terminals**
1. **Type** : types of variables and return types of functions
1. **Identifier** : identifiers of variables and functions
1. **LParen**, **RParen**, **LBrace**, **RBrace**, **Semi**, and **Comma**

   **:** syntactic symbols

1. **Integer** : integer values
1. **Character** : single-charactered values
1. **Boolean** : true, false
1. **Assign** : =
1. **AddSub** : +, -
1. **MulDiv** : \*, /
1. **UnaryOp** : ++, --
1. **CompOp** : ==, != ,>, <, >=, <=
1. **LogicOp** : &, |
1. **If**, **While**, **Else**, and **Return** : keywords for specific statements

### **Non-terminals**
S, CODE, FDECL, PARAMETER, MORE\_PARAMETER, VDECL, ASSIGN, EXPR, TERM, FACT, BLOCK, STMT, PREFIX\_STMT, POSTFIX\_STMT, FUNC\_CALL, ARGUMENT, MORE\_ARGUMENT, COND, COND\_EXPR, LOGIC\_EXPR, ELSE, RETURN

**Start symbol** : S



1. Code includes zero or more function declarations
1. A function is declared with zero or more parameters
1. A function includes zero or more statements
1. A variable is declared with or without an assignment
1. Expressions are categorized into
    1. function call
    1. conditional expression
    1. arithmetic operation
    1. unary operation
    1. sign operation
    1. const value
    1. variable
1. statements are classified into
    1. variable declaration
    1. assignment
    1. function call
    1. if statement
    1. while statement
    1. prefix statement
    1. postfix statement
1. if and while statements contain one or more conditional expressions a pair of which is bridged by a logical operation
1. An if statement is written with or without an else statement
1. A function call involves zero or more arguments
1. A return statement returns any category of expression
## **CFG and SLR Parsing Table**
The **Syntax Analyzer** verifies grammar of a sequence of tokens based on a stack and an **SLR parsing table** which is derived from the CFG.

## **Abstract Syntax Tree**
Reduction rules contain some semantically useless successors such as syntactic symbols. These are included in the resulting syntax tree as well. In addition, some nodes have only one successor, which is also meaningless.

Excluding these two cases, there are other inefficient structural obstacles. These should be removed for a faster and efficient tree traverse.

Getting rid of them is called '**abstraction**', which is implemented by ***NodeFactory*** where every node is created by a '**semantic action**'.


# **Semantic Analysis**
Semantic analysis includes checking

1. Scopes
1. Types
1. Well-formedness of statements

As well as these verifications, while traversing the abstract syntax tree, the symbol table is also constructed.
