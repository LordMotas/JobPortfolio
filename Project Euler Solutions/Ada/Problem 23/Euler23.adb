--Project Euler #23
--A number n is called abundant if this sum exceeds n.
--Find the sum of all positive integers which cannot be written
--as a sum of two abundant numbers.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler23 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable declarations
  Answer : Integer := 0;
  type IntArray is array (Positive range <>) of Integer;
  type BoolArray is array (Positive range <>) of Boolean;
  AbundantNumbers : IntArray := (1..6965 => 0);
  IsSumOfAbundant : BoolArray := (1..28123 => False);
  Count : Integer := 1;

  function findDivisors(Number : Integer) return Integer is
    SumOfDivisors : Integer := 0;
  begin
    for I in 1..Number/2 loop
      if Number mod I = 0 then
        SumOfDivisors := SumOfDivisors + I;
      end if;
    end loop;
    return SumOfDivisors;
  end findDivisors;
  
begin

  --Find all abundant numbers
  for I in 12..28123 loop
    if findDivisors(I) > I then
      AbundantNumbers(Count) := I;
      Count := Count + 1;
    end if;
  end loop;

  Count := Count - 1;

  for I in 1..Count loop
    for J in 1..Count loop
      if AbundantNumbers(I) + AbundantNumbers(J) <= 28123 then
        IsSumOfAbundant((AbundantNumbers(I) + AbundantNumbers(J))) := True;
      end if;
    end loop;
  end loop;

  for I in IsSumOfAbundant'Range loop
    if IsSumOfAbundant(I) = False then
      Answer := Answer + I;
    end if;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler23;