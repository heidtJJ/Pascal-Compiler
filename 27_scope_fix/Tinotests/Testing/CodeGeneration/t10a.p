program boo( input, output );
  var n,i,sum: integer;
  var a: array[1 .. 10] of integer;

  procedure MyProcedure();
  begin
    a[i] := i;
    write(a[i]);
    i := i + 1
  end;
  
  begin
  read(n);
  i := 1;
  
  while (i < n) do
    MyProcedure();

  write(n)
end.

