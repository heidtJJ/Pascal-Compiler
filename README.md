# Pascal-Compiler

Requirements by Tino: Simple Semantic Rules for the Dragon Pascal subset

1. Semantic rules for Scoping<br>
   1.1. Local objects cannot be declared more than once<br>
   1.2. Local objects hide non-local objects with the same name<br>
   1.3. Non-local objects should be visible from inner scopes (unless a local object of the same name exists)<br>
   1.4. Function and procedure names exist in the scope they are defined (and not in their own scopes)<br>
   1.5. Local objects cease to exist once their scopes cease to exist<br>

2. Semantic rules for Expressions<br>
   2.1. Expressions return typed-values<br>
   2.2. Objects must be declared before they used in expressions<br>
   2.3. Objects of different types cannot appear in the same expression (no type promotions)<br>

3. Semantic rules for Statements<br>
   3.1. Statements do not return values<br>
   3.2. The test expression for IF-THEN, IF-THEN-ELSE, WHILE-DO must be Boolean-valued;
        note that the Boolean type must be implicitly defined<br>
   3.3. The ELSE clause always binds to the closest IF (resolution of the dangling ELSE problem)<br>
   3.4. The variable type in FOR-DO must match the types of lower bound and upper bound expressions<br>

4. Semantic rules for Arrays<br>
   4.1. Non-integer valued expressions cannot be used for indexing arrays<br>

5. Semantic rules for Functions 
   5.1. Function calls return values of type Integer or Real<br>
   5.2. Function must contain a "return" statement within its own body;
        this is of the form: \<function_name\> := \<expression\> <br>
   5.3. Functions must accept exactly the same number of arguments as is 
        declared in its header, with the correct sequence of types<br>
   5.4. Functions are not allowed to update the value of nonlocal objects (via assignment statements)<br>

6. Semantic rules for Procedures
   6.1. Procedure calls do not return values<br>
   6.2. Procedures must accept exactly the same number of arguments as is 
        declared in its header, with the correct sequence of types<br>
        
        
<strong>Floating point (real) numbers are not currently supported for code generation (although they are semantically supported). Only integers may be used.</strong>

View <a href="yes" >faes</a><br>
Example input Pascal file:
```
program boo( input, output );
 var x: integer;
 procedure moo(a:integer);
 begin
 	x := 13;
 	write(x)
 end;
begin
 moo(0)
end.
```
Output x86 Assembly (64-bit):
```
	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
boo_moo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	$13, %ebx
	movq	-16(%rbp), %rax
	movl	%ebx, -8(%rax)
	movq	-16(%rbp), %rax
	movl	-8(%rax), %ebx
	movl	%esi, -36(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	-36(%rbp), %esi
	leave
	ret
.boo_moo:
	.size	boo_moo, .-boo_moo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movl	%esi, -48(%rbp)
	movq	%rbp, %rax
	movq	%rax, -80(%rbp)
	movl	$0, %ebx
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_moo
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	movl	-48(%rbp), %esi
	leave
	ret
.boo:
	.size	boo, .-boo
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	call	boo
	movl	$0, %eax
	leave
	ret
.main:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits
```
