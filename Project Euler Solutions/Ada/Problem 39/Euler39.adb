--Project Euler #39
--If p is the perimeter of a right angle triangle with integral length sides,
--{a,b,c}, there are exactly three solutions for p = 120.
--For which value of p <= 1000, is the number of solutions maximised.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler39 is

  package IO renames Ada.Text_IO;

  --Variable Declarations
  Answer : Integer := 0;
  NumSolutions : Integer;
  PrevSolutions : Integer := 0;

begin

  for P in 1..1000 loop
    NumSolutions := 0;
    for A in 1..Integer(P/3) loop
      if P*(P-2*A) mod (2*(P-A)) = 0 then
        NumSolutions := NumSolutions + 1;
      end if;
    end loop;
    if NumSolutions > PrevSolutions then
      PrevSolutions := NumSolutions;
      Answer := P;
    end if;
    NumSolutions := 0;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler39;