program boo( input, output );
 var z: integer;
 var x: integer;

begin
    x := 2;

    read(z);
    (* write(4/(2*2/4)); *)
    (* write(4/(2*2/4)*4/4*(1+1)); *)
    (* write(16/(4/(2*2/4)*4/4*(1+1))); *)
    write((16/(z/(x*x/z)*z/z*(1+1))+20*z/x)/x/(3+z)); 
end.

