--Project Euler #43
--d2d3d4=406 is divisible by 2
--d3d4d5=063 is divisible by 3
--d4d5d6=635 is divisible by 5
--d5d6d7=357 is divisible by 7
--d6d7d8=572 is divisible by 11
--d7d8d9=728 is divisible by 13
--d8d9d10=289 is divisible by 17

---Find the sum of all 0 to 9 pandigital numbers with this property.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use ada.Strings.Unbounded.Text_IO;

procedure Euler43 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  I : Long_Long_Integer := 1000357289;
  J : Long_Long_Integer := 1000952867;
  BoolArray : array(0..9) of Boolean := (0..9 => False);
  CheckString : SU.Unbounded_String := SU.To_Unbounded_String("");

begin

  <<FakeLoop>>
  for K in 0..9 loop
    BoolArray(K) := False;
  end loop;
  CheckString := SU.To_Unbounded_String(Long_Long_Integer'Image(I));
  CheckString := SU.To_Unbounded_String(SU.To_String(CheckString)(2..Length(CheckString)));
  for K in 1..10 loop
    BoolArray(Integer'Value(SU.To_String(CheckString)(K..K))) := True;
  end loop;
  for K in 0..9 loop
    if BoolArray(K) = False then
      goto NextLoop;
    end if;
  end loop;
  if Integer'Value(SU.To_String(CheckString)(2..4)) mod 2 = 0 then
    if Integer'Value(SU.To_String(CheckString)(3..5)) mod 3 = 0 then
      if Integer'Value(SU.To_String(CheckString)(4..6)) mod 5 = 0 then
        Answer := Answer + I;
      end if;
    end if;
  end if;
  <<NextLoop>>
  I := I + 1000000;
  if I < 9999357289 then
    goto FakeLoop;
  end if;

  <<SecondFakeLoop>>
  for K in 0..9 loop
    BoolArray(K) := False;
  end loop;
  CheckString := SU.To_Unbounded_String(Long_Long_Integer'Image(J));
  CheckString := SU.To_Unbounded_String(SU.To_String(CheckString)(2..Length(CheckString)));
  for K in 1..10 loop
    BoolArray(Integer'Value(SU.To_String(CheckString)(K..K))) := True;
  end loop;
  for K in 0..9 loop
    if BoolArray(K) = False then
      goto SecondNextLoop;
    end if;
  end loop;
  if Integer'Value(SU.To_String(CheckString)(2..4)) mod 2 = 0 then
    if Integer'Value(SU.To_String(CheckString)(3..5)) mod 3 = 0 then
      if Integer'Value(SU.To_String(CheckString)(4..6)) mod 5 = 0 then
        Answer := Answer + J;
      end if;
    end if;
  end if;
  <<SecondNextLoop>>
  J := J + 1000000;
  if J < 9999952867 then
    goto SecondFakeLoop;
  end if;

  IO.Put_Line("The answer is: "&Long_Long_Integer'Image(Answer));

end Euler43;