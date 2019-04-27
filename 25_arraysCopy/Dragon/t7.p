program boo( input, output );
 var a: integer;
 var n: array [1..5] of integer;
 var b: integer;

 procedure bar(p: integer);
    procedure moo(p: integer);
      begin
        n[1] := 1;
        n[2] := 2;
        n[3] := 3;
        n[4] := 4;
        n[5] := 5;
        a := 69;
        b := 88;
      end;
  begin
    moo(202)
  end;
begin

  bar(101);



  write(a);
  write(n[1]);
  write(n[2]);
  write(n[3]);
  write(n[4]);
  write(n[5]);
  write(n[0]);
  write(b);

end.

