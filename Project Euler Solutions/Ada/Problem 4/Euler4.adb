--Project Euler #4
--A palindromic number reads the same both ways. The largest palindrome
--made from the product of two 2-digit numbers is 9009 = 91*99
--Find the largest palindrom made form the product of two 3-digit numbers.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler4 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function Check (Line: String) return Boolean is
  begin
    for I in 0 .. Line'Length/2-1 loop
      if (Line(Line'First+I)/=Line(Line'Last-I)) then
        return False;
      end if;
    end loop;
    return True;
  end Check;

  --Variable declarations
  Line : SU.Unbounded_String;
  answer : Integer := 0;
  Length : Integer;
  InitialLine : String(1..7);
  StringLine : String(1..6);
  I : Integer := 999;
  J : Integer := 999;
  
begin
  <<First_Loop>>
    J := 999;
    <<Second_Loop>>
      InitialLine := Integer'Image(I*J);
      StringLine := InitialLine(2..7);
      Length := StringLine'Length;
      if Check(StringLine (1..Length)) then
        if I*J > answer then
          answer := I*J;
        end if;
      end if;
    J := J - 1;
    if J >= 500 then
      goto Second_Loop;
    end if;
  I := I - 1;
  if I >= 500 then
    goto First_Loop;
  end if;
  
<<endProgram>>
IO.Put_Line("The answer is: " & Integer'Image(answer));

end Euler4;