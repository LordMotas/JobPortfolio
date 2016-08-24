--Project Euler #20
--Find the sum of all the digits in 100!

with Ada.Text_IO; use Ada.Text_IO;
with  ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler20 is

  package IO renames Ada.Text_IO; 
  package SU renames Ada.Strings.Unbounded;
  
  --Functions
  function To_Integer(Char : Character) return Integer is (Character'Pos(Char) - Character'Pos('0'));
  
  function To_String(Int : Integer) return String is
    Str : String := Integer'Image(Int);
  begin
    if int >= 0 then
      return Str(2..Str'Length);
    else
      return Str(1..Str'Length);
    end if;
  end;
  
  function Digit(UnString : SU.Unbounded_String; Number : Positive) return Natural is
  begin
    if Number in 1..Length(UnString) then
      return To_Integer(Element(UnString, Length(UnString) - Number + 1));
    else
      return 0;
    end if;
  end Digit;
  
  function "*"(UnString : Unbounded_String; Number : Natural) return SU.Unbounded_String is
    ReturnString : SU.Unbounded_String;
    Carry : Natural := 0;
    Value : Natural;
  begin
    for OneDigit in 1..Length(UnString) loop
      Value := Carry + Digit(UnString, OneDigit) * Number;
      ReturnString := To_String(Value mod 10) & ReturnString;
      Carry := Value / 10;
    end loop;
    if Carry > 0 then
      ReturnString := To_String(Carry) & ReturnString;
    end if;
    return ReturnString;
  end "*";
  
  --Variable Declarations
  Answer : Natural := 0;

  StartString : SU.Unbounded_String := SU.To_Unbounded_String("1");
  
begin
  
  for I in 2 .. 100 loop
    StartString := StartString * I;
  end loop;
  for I in 1 ..Length(StartString) loop
    Answer := Answer + Digit(StartString, I);
  end loop;
  
  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler20;