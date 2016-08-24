--Project Euler #38
--Take the number 192 and multiply it by each of 1, 2, and 3:
--This results in: 192, 384, and 576. 
--By concatenating each product we get a 1 to 9 pandigital number
--What is the largest 1 to 9 pandigital 9-digit number that can be formed
--as the concatenated product of an integer with (1,2,...,n) where n > 1?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;

procedure Euler38 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Answer : Integer := 0;
  TestString : SU.Unbounded_String := SU.To_Unbounded_String("");
  BoolArray : array(0..9) of Boolean := (0..9 => False);

begin
  for I in 1..1000000 loop
    for L in 1..9 loop
      BoolArray(L) := False;
    end loop;
    TestString := SU.To_Unbounded_String("");
    for J in 1..9 loop
      if Length(TestString) < 9 then
        Append(TestString, SU.To_Unbounded_String(Trim(SU.To_String(SU.To_Unbounded_String(Integer'Image(I*J))), Both)));
      end if;
    end loop;
    if Length(TestString) = 9 then
      for K in 1..Length(TestString) loop
        BoolArray (Character'Pos(SU.To_String(TestString)(K))-48) := True;
      end loop;
      for L in 1..9 loop
        if BoolArray (L) = False then
          goto nextLoop;
        end if;
      end loop;
      if Answer < Integer'Value(SU.To_String(TestString)) then
        Answer := Integer'Value(SU.To_String(TestString));
      end if;
    end if;
    <<nextLoop>>
  end loop;

  <<endProgram>>

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler38;