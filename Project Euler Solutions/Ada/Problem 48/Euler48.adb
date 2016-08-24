--Project Euler #48
--Find the last 10 digits of the series 1^1+2^2+3^3+...+1000^1000

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler48 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO; 
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  Modulo : Long_Long_Integer := 10000000000;

begin

  for I in 1..1000 loop
    declare
      Temp : Long_Long_Integer := Long_Long_Integer(I);
    begin
      for J in 1..I-1 loop
        Temp := Temp * Long_Long_Integer(I);
        if Temp >= Long_Long_Integer'Last / 1000 then
          Temp := Temp mod Modulo;
        end if;
      end loop;
      Answer := Answer + Temp;
      Answer := Answer mod Modulo;
    end;
  end loop;

  IO.Put_Line("The answer is: "&Long_Long_Integer'Image(Answer));

end Euler48;