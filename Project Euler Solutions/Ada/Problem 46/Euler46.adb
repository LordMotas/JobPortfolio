--Project Euler #46
--What is the smallest odd composite that 
--cannot be written as the sum of a prime and twice a square?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler46 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  function isPrime(N : Integer) return Boolean is
  begin
    if N <= 1 then
      return False;
    end if;
    if N = 2 then
      return True;
    end if;
    if N mod 2 = 0 then
      return False;
    end if;
    for I in 3..N-1 loop
      if N mod I = 0 then
        return False;
      end if;
    end loop;
    return True;
  end isPrime;

  function isTwiceSquare(N : Integer) return Boolean is
    SquareTest : Float := Sqrt(Float(N)/2.0);
    TestInt : Integer := Integer(SquareTest);
  begin
    return SquareTest = Float(TestInt);
  end isTwiceSquare;

  --Variable Declarations
  Answer : Integer := 0;
  Result, I : Integer := 1;
  NotFound : Boolean := True;
  Primes : array(0..100000) of Integer;
  Count : Integer := 0;

begin

  for I in 1..100000 loop
    if isPrime(I) then
      --Put_Line(Integer'Image(I));
      Primes(Count) := I;
      Count := Count + 1;
    end if;
  end loop;
  while NotFound = True loop
    Result := Result + 2;
    declare
      J : Integer := 0;
    begin
      NotFound := False;
      while Result >= Primes(J) loop
        if isTwiceSquare(Result - Primes(J)) then
          NotFound := True;
          exit;
        end if;
        J := J + 1;
      end loop;
    end;
  end loop;
  
  Put_Line("The answer is: "&Integer'Image(Result));

end Euler46;