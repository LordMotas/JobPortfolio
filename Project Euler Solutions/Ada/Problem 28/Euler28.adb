--Project Euler #28
--Starting with the number 1 and move to the right in a clockwise direction
--What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler28 is

  package IO renames Ada.Text_IO;
  
  function f(N : Natural) return Integer is
  begin
    if N = 0 then
      return 0;
    end if;
    return 4*((2*N+1)*(2*N+1)) - 12*N + f(N - 1);
  end f;
  
  --Variable Declarations
  Answer : Integer;
  
begin

  Answer := f(500);

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler28;