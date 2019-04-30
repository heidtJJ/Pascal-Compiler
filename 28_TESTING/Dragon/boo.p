program boo(input,output);
  var a,b,c: integer;
  var p: array [7 .. 11] of integer; 
  function foo(q,u: integer):integer;
    var a,b: integer;
  begin
    a := c+1;
    b := (a - 1)*(a + 1) + 1;
    foo := b
  end;
  function moo(q: array[7 .. 11] of integer):integer;
    var a,b: integer;
  begin
    a := q[8];
    b := (a - 1)*(a + 1) + 1;
    moo := b
  end;
  function bar(x:integer):integer;
  begin
    bar := x + 1
  end;
begin
  read(a);
  c := a+1;
  p[7] := a;
  b := foo(p[bar(6)],c);
  write(b)
end.
