--Project Euler #30
--Find the sum of all numbers that can be written
--as the sum of fifth powers of their digits

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler30 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;
  
  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  StartString : SU.Unbounded_String;
  Temp : Long_Long_Integer := 1;
  
begin

  for I in 1..1000000 loop
    StartString := SU.To_Unbounded_String(Integer'Image(I));
    for J in 2..Length(StartString) loop
      Temp := Temp + (Character'Pos(Element(StartString, J)) - 48)**5;
    end loop;
    if Temp = Long_Long_Integer(I) then
      Answer := Answer + Temp;
    end if;
    Temp := 0;
  end loop;

  IO.Put_Line("The answer is: "&Long_Long_Integer'Image(Answer));
  
end Euler30;