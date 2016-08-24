--Project Euler #32
--We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once;
--Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
--HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;

procedure Euler32 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;
  package FIX renames Ada.Strings.Fixed;

  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  AllString : SU.Unbounded_String;
  type StrArray is array(Positive range <>) of SU.Unbounded_String;
  PandigitalArray : StrArray := (1..9 => SU.To_Unbounded_String("0"));
  InArray : Boolean := False;
  Count : Integer := 1;
  type BooleanArray is array(Positive range 1..9) of Boolean;
  Char : Character;

  function isPandigital(S : SU.Unbounded_String) return Boolean is
    N : Long_Long_Integer := Long_Long_Integer'Value(FIX.Trim(SU.To_String(S),Both));
    BoolArray : BooleanArray := (1..9 => False);
  begin
    for I in 1..Length(S) loop
      Char := SU.To_String(S)(I);
      case Char is
        when '1' => BoolArray(1) := True;
        when '2' => BoolArray(2) := True;
        when '3' => BoolArray(3) := True;
        when '4' => BoolArray(4) := True;
        when '5' => BoolArray(5) := True;
        when '6' => BoolArray(6) := True;
        when '7' => BoolArray(7) := True;
        when '8' => BoolArray(8) := True;
        when '9' => BoolArray(9) := True;
        when others => Return False;
      end case;
    end loop;
    for I in BoolArray'Range loop
      if BoolArray(I) = False then
        return False;
      end if;
    end loop;
    return True;
  end isPandigital;

begin
  for I in 1..100 loop
    declare
      NBegin : Integer;
      NEnd  : Integer := 10000 / I + 1;
    begin
      if I > 9 then
        NBegin := 123;
      else
        NBegin := 1234;
      end if;
      for J in NBegin..NEnd loop
        AllString := SU.To_Unbounded_String(Trim(Integer'Image(I), Both)&Trim(Integer'Image(J), Both)&Trim(Integer'Image(I*J), Both));
        --account for the beginning character
        if Length(AllString) >= 9 and then Length(AllString) < 10 then
          if isPandigital(AllString) then
            for K in PandigitalArray'Range loop
              if PandigitalArray(K) = SU.To_String(AllString)(6..9) then
                InArray := True;
              end if;
            end loop;
            if InArray = False then
              PandigitalArray(Count) := SU.To_Unbounded_String(SU.To_String(AllString)(6..9));
              Count := Count + 1;
              --Slice just from 6..9
              Answer := Answer + Long_Long_Integer'Value(FIX.Trim(SU.To_String(AllString)(6..9),Both));
            end if;
            InArray := False;
          end if;
        end if;
      end loop;
    end;
  end loop;

  IO.Put_Line("The answer is: "&Long_Long_Integer'Image(Answer));

end Euler32;