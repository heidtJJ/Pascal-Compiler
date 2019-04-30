program boo( input, output );
  var x: integer; 
  var a: array[1 .. 3] of integer;
  var y: integer; 

  function MyProcedureHelper(d: integer; b: array[1 .. 3] of integer; c: integer): integer;
    var pp: integer;
  begin
    if x < 9
      then pp := MyProcedureHelper(d, b, c)
      else pp := x + 1;

    MyProcedureHelper := pp;

    write(d);

    write(b[1]);
    write(b[1]);
    write(c);
    
    write(a[1]);
    write(b[1]);

    write(d);
    write(d);
  end;

  procedure MyProcedure(d: integer; b: array[1 .. 3] of integer; c: integer);
    var dodo: integer;
  begin
    dodo := MyProcedureHelper(d, b, c);
  end;
  
  begin
    x := 0;
    a[1] := 12;
    MyProcedure(666, a, 2);
    write(a[1]);
    write(x);
    write(y);

  end.

