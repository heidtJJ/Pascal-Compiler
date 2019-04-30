program boo( input, output );
	var n,i: integer;
	var a: array[1 .. 10] of integer;

	procedure alpha(x: integer);
    begin
		a[i] := i*i;
		i := i + 1
    end;

	procedure beta(x: integer);
    begin
		write(a[i]);
		i := i + 1
    end;

	begin
		read(n);
		i := 1;
		while ( i <= n ) do
			alpha(1);
		i := 1;
		while ( i <= n ) do
			beta(2)
	end.

