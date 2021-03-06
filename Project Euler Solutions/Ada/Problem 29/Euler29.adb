--Project Euler #29
--How many distinct terms are in the sequence generated by a^b for 2 <= a <= 100 and 2 <= b <= 100?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler29 is

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
  
  function "+"(UnString : Unbounded_String; SecondUnString : Unbounded_String) return SU.Unbounded_String is
    ReturnString : SU.Unbounded_String;
    Carry : Natural := 0;
    Value : Natural;
  begin
    for OneDigit in 1..Length(UnString) loop
      Value := Carry + Digit(UnString, OneDigit) + Digit(SecondUnString, OneDigit);
      ReturnString := To_String(Value mod 10) & ReturnString;
      Carry := Value / 10;
    end loop;
    if Carry > 0 then
      ReturnString := To_String(Carry) & ReturnString;
    end if;
    return ReturnString;
  end "+";
  
  --Variable Declarations
  StartString : SU.Unbounded_String := SU.To_Unbounded_String("1");
  type StrArray is array (Positive range 1..100000) of SU.Unbounded_String;
  DistinctArray : StrArray := (1 => SU.To_Unbounded_String("0"), others => SU.To_Unbounded_String("0"));
  Answer : Integer;
  InArray : Boolean;
  Count : Integer := 1;
  
begin

  for A in 2..100 loop
    for B in 2..100 loop
      InArray := False;
      for K in 1..B loop
	    StartString := StartString * A;
      end loop;
      for I in DistinctArray'Range loop
        if DistinctArray(I) = StartString then
          InArray := True;
        end if;
      end loop;
      if InArray = False then
        DistinctArray(Count) := StartString;
        Count := Count + 1;
      end if;
      StartString := SU.To_Unbounded_String("1");
    end loop;
  end loop;

  Answer := Count - 1;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler29;