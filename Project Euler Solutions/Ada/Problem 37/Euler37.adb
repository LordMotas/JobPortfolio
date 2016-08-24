--Project Euler #37
--The number 3797 has an interesting property. Being prime itself, 
--it is possible to continuously remove digits from left to right, 
--and remain prime at each stage: 3797, 797, 97, and 7. 
--Similarly we can work from right to left: 3797, 379, 37, and 3.
--Find the sum of the only eleven primes that are both truncatable.
--NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler37 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;
  package Math renames Ada.Numerics.Elementary_Functions;

  function isPrime(N : Integer) return Boolean is
  begin
    if N < 2 then
      return False;
    end if;
    for I in 2..Integer(Math.Sqrt(Float(N))) loop
      if N mod I = 0 then
        return False;
      end if;
    end loop;
    return True;
  end isPrime;

  --Variable Declarations
  Answer : Integer := 0;
  S1, S2 : SU.Unbounded_String;
  NumPrimes : Integer := 0;
  FirstOne : Boolean := False;
  
begin

  for I in 9..739397 loop
    if isPrime(I) then
      S1 := SU.To_Unbounded_String(Integer'Image(I));
      S2 := SU.To_Unbounded_String(Integer'Image(I));
      for J in 1..Length(SU.To_Unbounded_String(Integer'Image(I)))-1 loop
        S1 := SU.To_Unbounded_String(SU.To_String(S1)(2..Length(S1)));
        if isPrime(Integer'Value(SU.To_String(S1))) = True then
          if J = Length(SU.To_Unbounded_String(Integer'Image(I)))-1 then
            FirstOne := True;
          end if;
        else
          goto nextLoop;
        end if;
      end loop;
        S2 := SU.To_Unbounded_String(SU.To_String(S2)(2..Length(S2)));
      for J in 1..Length(SU.To_Unbounded_String(Integer'Image(I)))-2 loop
        S2 := SU.To_Unbounded_String(SU.To_String(S2)(1..Length(S2)-1));
        if isPrime(Integer'Value(SU.To_String(S2))) = True then
          if J = Length(SU.To_Unbounded_String(Integer'Image(I)))-2 then 
            if FirstOne = True then
              Answer := Answer + I;
              NumPrimes := NumPrimes + 1;
            end if;
          end if;
        else 
          goto nextLoop;
        end if;
      end loop;
    end if;
    <<nextLoop>>
    FirstOne := False;
    if NumPrimes = 11 then
      goto endProgram;
    end if;
  end loop;
 
  <<endProgram>>
  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler37;