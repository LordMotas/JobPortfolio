--Project Euler #9
--A Pythagorean triplet is a set of three natural numbers a < b < c, for which,
--a^2+b^2=c^2
--There exists exactly one Pythagorean triplet for which a+b+c=1000
--Find the product a*b*c

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler9 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  answer : Integer := 0;
  
begin
  for I in 1..1000 loop
    for J in 1..1000 loop
      for K in 1..1000 loop
        if I < J and then J < K and then (I + J + K = 1000) and then ((I*I) + (J*J) = (K*K)) then 
          IO.Put_Line(Integer'Image(I)&" "&Integer'Image(J)&" "&Integer'Image(K));
          IO.Put_Line("The answer is: " & Integer'Image(I * J * K));
          goto endProgram;
        end if;
      end loop;
    end loop;
  end loop;

<<endProgram>>

end Euler9;