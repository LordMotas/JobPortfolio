
--Project Euler #14
--The following iterative sequence is defined for the set of positive integers:
--n->n/2 (n is even)
--n->3n+1 (n is odd)
--Which starting number, under a million, produces the longest chain?

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler14 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  answer : Long_Integer := 0;
  CurrentValue : Long_Integer := 0;
  Count : Long_Integer := 0;
  PrevCount : Long_Integer := 0;
  
begin
  for I in 1..999999 loop
    Count := 0;
    CurrentValue := Long_Integer(I);
    while CurrentValue /= 1 loop
      if CurrentValue mod 2 = 0 then
        CurrentValue := CurrentValue / 2;
      else
        CurrentValue := (CurrentValue * 3) + 1;
      end if;
      Count := Count + 1;
    end loop;
    if Count > PrevCount then
      PrevCount := Count;
      answer := Long_integer(I);
    end if;
  end loop;
  
  IO.Put("The answer is: "&Long_Integer'Image(answer));
  
end Euler14;