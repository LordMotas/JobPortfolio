--Project Euler #6
--The sum of the squares of the first ten natural numers is,
--1^2+2^2+...+10^2=385
--the square of the sum of the first ten natural numbers is,
--(1+2+..+10)^2=55^2=3025
--Hence the difference between the sum of the squares of the first
--ten natural numbers and the square of the sum is 3025-385=2640
--Find the difference between the sum of the squares of the first
--one hundred natural numbers and the square of the sum

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler6 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  SumOfSquares : Integer := 0;
  SquareOfSums : Integer := 0;
  I : Integer := 1;
  
begin
  <<First_Loop>>
    --Calculate the sum of squares
    SumOfSquares := SumOfSquares + (I * I);
    --Calculate the square of sums
    SquareOfSums := SquareOfSums + I;
  I := I + 1;
  if I <= 100 then
    goto First_Loop;
  end if;
  SquareOfSums := (SquareOfSums * SquareOfSums);

IO.Put_Line("The answer is: " & Integer'Image(SquareOfSums-SumOfSquares));

end Euler6;