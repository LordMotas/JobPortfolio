--Project Euler #1
--If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3,5,6, and 9. The sum of those muiltiples is 23.
--Find the sum of all the multiples of 3 or 5 below 1000.

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler1 is
  package IO renames Ada.Text_IO;

  --Variable declarations
  X : Integer := 1;
  answer : Integer := 0;

begin

  for X in Integer range 1 .. 999 loop
    if X mod 3 = 0 or else X mod 5 = 0 then
      answer := answer + X;
    end if;
  end loop;
  
  IO.Put_Line("The answer is: " & Integer'Image(answer));
  
end Euler1;
