program boo( input, output );
  var x: integer; 
  var a: array[1 .. 3] of integer;
  var y: integer; 

  procedure MyProcedure(d: integer; b: array[0 .. 3] of integer; c: integer);
  begin
    write(d);



    write(b[1]);
    b[1] := 96;
    write(b[1]);
    write(c);
    
    a[1] := 69;
    write(a[1]);
    write(b[1]);

    write(d);
    d := 999;
    write(d);
    x := 1001;
    y := 8008;
  end;
  
  begin
    a[1] := 12;
    MyProcedure(666, a, 2);
    write(a[1]);
    write(x);
    write(y);

  end.

