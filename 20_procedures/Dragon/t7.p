program boo( input, output );
	var x: integer;
	
	procedure foo(a: integer);
		procedure coo(a: integer);
			begin
				write(x);
				x := 1;
			end;
		begin
			coo(1);
			write(x);
			x := 2;
		end;
	begin
		x := 22;
		foo(1);
		write(x);
		x := 3;
		write(x);
	end.

