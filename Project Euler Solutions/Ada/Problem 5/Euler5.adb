--Project Euler #5
--2520 is the smallest number that can be divided by each of the
--numbers from 1 to 10 without any remainder.
--What is the smallest positive number that is evenly divisible
--be all of the numbers from 1 to 20?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Euler5 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO;

  --Variable declarations
  I : Integer := 1;
  
begin
  <<First_Loop>>
  if I mod 1 = 0 and then I mod 2 = 0 and then I mod 3 = 0 and then I mod 4 = 0 and then I mod 5 = 0 and then I mod 6 = 0 and then I mod 7 = 0 and then I mod 8 = 0 and then I mod 9 = 0 and then I mod 10 = 0 and then I mod 11 = 0 and then I mod 12 = 0 and then I mod 13 = 0 and then I mod 14 = 0 and then I mod 15 = 0 and then I mod 16 = 0 and then I mod 17 = 0 and then I mod 18 = 0 and then I mod 19 = 0 and then I mod 20 = 0 then
    IO.Put_Line("The answer is: " & Integer'Image(I));
    goto endProgram;
  end if;
  I := I + 1;
  if I < 1000000000 then
    goto First_Loop;
  end if;
<<endProgram>>

end Euler5;