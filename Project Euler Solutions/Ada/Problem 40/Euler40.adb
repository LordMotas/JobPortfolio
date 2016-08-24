--Project Euler #40
--0.1232456789101112131415161718192021...
--The 12th digit is a 1
--Find the value of the following:
--d1*d10*d100*d1000*d10000*d100000*d1000000

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;

procedure Euler40 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  CurrentString : SU.Unbounded_String := SU.To_Unbounded_String("");
  Answer : SU.Unbounded_String := SU.To_Unbounded_String("");

begin

  for I in 1..185185 loop
    Append(CurrentString, SU.To_Unbounded_String(Trim(Integer'Image(I), Both)));
  end loop;

  Append(Answer, SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(1..1), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(10..10), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(100..100), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(1000..1000), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(10000..10000), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(100000..100000), Both))&SU.To_Unbounded_String(Trim(SU.To_String(CurrentString)(1000000..1000000), Both)));

  IO.Put_Line("The answer is: "&SU.To_String(Answer));

end Euler40;