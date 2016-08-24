--Project Euler #35
--197 is a circular prime since all rotations of the digits:
--917, 971, 719 are themselves prime
--Circular primes below 100: 2,3,5,7,11,13,17,31,37,71,73,79
--How many circular primes are there below one million

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler35 is

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

  procedure rotateNumber(S : in out SU.Unbounded_String) is
    TempStr : SU.Unbounded_String := S;
  begin
    Replace_Element(S, 2, Element(S, Length(S)));
    for J in 3..Length(S) loop
      Replace_Element(S, J, Element(TempStr, (J-1)));
    end loop;
  end rotateNumber;

  --Variable Declarations
  Answer : Integer := 0;
  Str : SU.Unbounded_String := SU.To_Unbounded_String("");
  TempStr : SU.Unbounded_String := SU.To_Unbounded_String("");
  NumPrimes : Integer := 0;
  Test : Integer := 0;
  
begin

  for I in 1..1000000 loop
    NumPrimes := 0;
    Str := SU.To_Unbounded_String(Integer'Image(I));
    for J in 1..Length(Str)-1 loop
      rotateNumber(Str);
      Test := Integer'Value(SU.To_String(Str));
      if isPrime(Test) then
        NumPrimes := NumPrimes + 1;
      end if;
    end loop;
    if NumPrimes = Length(Str)-1 then
      Answer := Answer + 1;
    end if;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler35;