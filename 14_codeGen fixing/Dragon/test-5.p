program main( input, output );
  var x, y: integer;
  function foo( x, y: integer ): integer;
  begin
	foo := x * x - y * y
  end;
begin
  y := foo( x+1, x-1 );
end.

