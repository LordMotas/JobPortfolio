--Project Euler #21
--d(a)=b & d(b)=a where a/=b then a and b are amicable numbers
--Example:
--divisors of 220 are 1,2,4,5,10,11,20,22,44,55 and 110
--d(220)=284 & d(284)=220
--Evaluate the sum of all amicable numbers under 10000

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler21 is

  package IO renames Ada.Text_IO;
  package Math renames Ada.Numerics.Elementary_Functions;
  
  --Variable Declarations
  Answer : Integer := 0;
  
  function findDivisors(Number : Integer) return Integer is
      SumOfDivisors : Integer := 0;
  begin
    for I in 1 .. Number/2 loop
      if Number mod I = 0 then
        SumOfDivisors := SumOfDivisors + I;
      end if;
    end loop;
    return SumOfDivisors;
  end findDivisors;
  
  function isAmicable(Number : Integer) return Boolean is
    Digit : Integer := findDivisors(Number);
  begin
    return Digit /= Number and then findDivisors(Digit) = Number;
  end isAmicable;
  
begin
  
  for I in 0 .. 9999 loop
    if isAmicable(I) then
      Answer := Answer + I;
    end if;
  end loop;
  
  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler21;