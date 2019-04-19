program boo( input, output );
	var x,y: integer;
	function foo(a: integer; b: integer): integer;
		begin
			foo := a * 10;
			b := 4;
			foo := b; 
		end;
	procedure coo(a: integer);
		begin
			x := 22;
			write(x)
		end;
	begin
		read(x);
		write(x);

		coo(1);
		write(x);

	end.

