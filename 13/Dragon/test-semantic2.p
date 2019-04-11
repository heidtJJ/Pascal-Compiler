
program main( input, output );

  var x, y: integer;
  var a, b, q: real;
  var c: array[ 1..10 ] of integer;
  var d: array[ 11..20 ] of real;

  procedure moo( a: real );
    begin
      b := 1.0;
    end;

  function foo( a: integer; x: real; z: integer ): integer;
    procedure boo( a: real );
    begin
      boo( a * b + d[y + z] );
    end;
  begin
    foo := a + y;
    moo(1.0);
  end;
  
begin


end.

