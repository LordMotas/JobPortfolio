--Project Euler #52
--It can be seen that the number, 125874, and its double, 251748, 
--contain exactly the same digits, but in a different order.
--Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, 
--contain the same digits.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;

procedure Euler52 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO; 
  package SU renames Ada.Strings.Unbounded;

  function isPerm(M : Integer; N : Integer) return Boolean is
    Arr : array(0..9) of Integer := (0..9 => 0);
    Temp : Integer := N;
  begin
    while Temp > 0 loop
      Arr(Temp mod 10) := Arr(Temp mod 10) + 1;
      Temp := Temp / 10;
    end loop;
    Temp := M;
    while Temp > 0 loop
      Arr(Temp mod 10) := Arr(Temp mod 10) - 1;
      Temp := Temp / 10;
    end loop;
    for I in 0..9 loop
      if Arr(I) /= 0 then
        return False;
      end if;
    end loop;
    return True;
  end isPerm;

  --Variable Declarations
  Answer : Integer := 0;
  Start : Integer := 1;
  Found : Boolean := False;

begin

  while Found = False loop
    Start := Start * 10;
    for I in Start..(Start * 10 / 6) - 1 loop
      Found := True;
      for J in 2..6 loop
        if isPerm(I, J * I) = False then
          Found := False;
          exit;
        end if;
      end loop;
      if Found = True then
        Answer := I;
        goto endProgram;
      end if;
    end loop;
  end loop;

  <<endProgram>>

  Put_Line("The answer is: "&Integer'Image(Answer));

end Euler52;