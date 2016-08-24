--Project Euler #41
--n-digit number is pandigital if it uses all digits 1 to n one time
--what is the largest n-digit pandigital prime that exists?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler41 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function isPrime(N : Integer) return Boolean is
  begin
    if N < 2 then
      return False;
    end if;
    for I in 2..Integer(Sqrt(Float(N))) loop
      if N mod I = 0 then
        return False;
      end if;
    end loop;
    return True;
  end isPrime;

  --Variable Declarations
  Answer : Integer := 0;
  TestString : SU.Unbounded_String := SU.To_Unbounded_String("");
  BoolArray : array(0..9) of Boolean := (0..9 => False);

begin

  for I in reverse 1234567..7654321 loop
    for J in 1..7 loop
      BoolArray(J) := False;
    end loop;
    if isPrime(I) then
      TestString := SU.To_Unbounded_String(Integer'Image(I));
      TestString := SU.To_Unbounded_String(Slice(TestString, 2, 8));
      for J in 1..7 loop
        BoolArray(Character'Pos(SU.To_String(TestString)(J))-48) := True;
      end loop;
      for J in 1..7 loop
        if BoolArray(J) = False then
          goto nextLoop;
        end if;
      end loop;
      Answer := I;
      goto endProgram;
    end if;
    <<nextLoop>>
  end loop;

  <<endProgram>>

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler41;