--Project Euler #15
--How many Lattice paths can be found in a 20X20 square?

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler15 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  Paths : Long_Integer := 1;
  GridSize : Long_Integer := 20;
  
begin
  for I in 0 .. GridSize loop
    Paths := Paths * ((2 * GridSize) - Long_Integer(I));
    Paths := Paths / (Long_integer(I) + 1);
  end loop;
  
  IO.Put("The answer is: "&Long_Integer'Image(Paths));
  
end Euler15;