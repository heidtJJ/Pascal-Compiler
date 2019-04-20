program boo( input, output );
	var x: integer;
	
	procedure foo(a: integer);
		var x: integer;
		function coo(a: integer; x: integer) : integer;
			begin
				write(x);
				coo := 12;
			end;
		begin
			x := coo(1, 2);
			write(x);
			x := 2;
		end;
	begin
		x := 22+2*2/2+(43);
		foo(1);
		write(x);
		x := 3;
		write(x);
	end.

